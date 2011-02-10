#ifndef _HAVE_EVENTS_CPP
#define _HAVE_EVENTS_CPP
#include "obj/Screen.c++"

//struct Event : gc, LL<Event>, Interaction {
//	Object* a;
//	Object* b;

	void Event::happen () {
		if (a != screen)
			DEBUGLOG("[%10.6f]   ITX: %p & %p @ %10.6f\n", now.repr, a, b, t.repr);
		a->update();
		b->update();
		(*wrap)(call, a, b);
		a->future = b->future = NULL;
		check_interactions(a);
		if (a != b)
			check_interactions(b);
	}
	/*void Event::cancel (Object* froma, Object* fromb) {
		unschedule();
		if (a != froma && a != fromb) {
			a->future = NULL;
			check_interactions(a);
		}
		if (b != froma && b != fromb) {
			b->future = NULL;
			check_interactions(b);
		}
	}*/
	static bool cmp_events(Event* a, Event* b) { return a->t < b->t; }
	inline void Event::schedule () {
		replace_sort_forward(current_event, &cmp_events);
	}
	inline void Event::unschedule () {
		unlink_backward(current_event);
		next = prev = NULL;
	}
//};


void check_interactions(Object* a) {
	Object* picked = NULL;
	Event* newfuture = new (GC) Event;
	newfuture->t = INF*T;
	for (Object* b = first_object; b; b = b->next) {
		 // Skip (the first time) if we just had an interaction.
		 // When the other object checks, this object's future will be NULLed.
		if (b->future && (b->future->a == a || b->future->b == a)) {
			b->future->unschedule();
			b->future = a->future = NULL;
		}
		Time time_limit = newfuture->t;
		if (b->future && b->future->t < time_limit)
			time_limit = b->future->t;
		if (b->future && b->future->t < now) {
			printf("Warning: detected a leftover future on object %p for %10.6f\n", b, b->future->t.repr);
		}
		Interaction i;
		bool flip;  // Reverse arguments to callback?
		ICID aid = a->icid();
		ICID bid = b->icid();
		if (ITX_LOOKUP(aid, bid)) {
			i = (*ITX_LOOKUP(aid, bid))(a, b);
			flip = false;
		}
		else if (ITX_LOOKUP(bid, aid)) {
			i = (*ITX_LOOKUP(bid, aid))(b, a);
			flip = true;
		}
		else continue;
		 // Only pick if it's earlier than our time limit
		 // and (approximately) later than now.
		if (i.t >= now - EVENT_BACKWARD_TOLERANCE
		 && i.t < time_limit) {
			 // But reject it if its too soon of a repeat
			if (i.t < now+EVENT_REPEAT_INTERVAL)
				for (Event* e = current_event; e && e->t > i.t - EVENT_REPEAT_INTERVAL; e = e->prev)
					if ((e->a == a && e->b == b)
					 || (e->a == b && e->b == a))
					if (e->call == i.call)
						goto nope;
			picked = b;
			newfuture->t = i.t;
			newfuture->wrap = i.wrap;
			newfuture->call = i.call;
			if (flip) {
				newfuture->a = b;
				newfuture->b = a;
			} else {
				newfuture->a = a;
				newfuture->b = b;
			}
		}
		nope: ;
	}
	if (picked) {
		if (a != screen)
			DEBUGLOG("[%10.6f] ADD  : %p & %p @ %10.6f\n", now.repr, a, picked, newfuture->t.repr);
		Event* of = picked->future;

		a->future = newfuture;
		picked->future = newfuture;
		newfuture->schedule();

		if (of != NULL) {
			DEBUGLOG("[%10.6f]  CAN : %p & %p @ %10.6f\n", now.repr, of->a, of->b, of->t.repr);
			 // Cancel the other object's future.
			 // And recalculate other futures if needed.
			of->unschedule();
			Object* ofa = of->a;
			Object* ofb = of->b;
			delete of;
			if (ofa != a && ofa != picked) {
				ofa->future = NULL;
				return check_interactions(ofa);
			}
			if (ofb != a && ofb != picked) {
				ofb->future = NULL;
				return check_interactions(ofb);
			}
		}
	}
	else {
		if (a->future)
		printf("Object %p has a leftover future for %10.6f.\n", a, a->future->t.repr);
		a->future = NULL;
		delete newfuture;
	}
}


void main_loop () {
	now = 0*T;
	get_input();
	if (!room) (room = new Room)->create();
	if (!screen) (screen = new Screen)->create();
	if (!kbd) (kbd = new Keyboard)->create();
	set_video(room->_size);
	while (Event* e = current_event) {
		 // Drop past events if unneeded
		if (e->t - now > EVENT_REPEAT_INTERVAL) {
			Event* oldold;
			for (Event* old = e->prev; old; old = oldold) {
				oldold = old->prev;
				delete old;
			}
			e->prev = NULL;
		}
		now = e->t;
		delay_to(now);
		get_input();  // This is not accurate
		current_event = e->next;
		e->happen();
	}
}


void dump_event_list () {
	for (Event* e = current_event; e; e = e->next) {
		printf("At %f do %p on %p & %p\n",
			e->t.repr, e->call, e->a, e->b);
	}
}






#endif
