#ifndef _HAVE_EVENTS_CPP
#define _HAVE_EVENTS_CPP
#include "obj/Screen.c++"

//struct Event : gc, LL<Event>, Interaction {
//	Object* a;
//	Object* b;

	void Event::happen () {
		a->update();
		b->update();
		(*call)(a, b);
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
	Event* newfuture = new Event;
	newfuture->t = INF*T;
	for (Object* b = first_object; b; b = b->next) {
		Time time_limit = newfuture->t;
		if (b->future && b->future->t < time_limit)
			time_limit = b->future->t;
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
		Event* of = picked->future;

		a->future = newfuture;
		picked->future = newfuture;
		newfuture->schedule();

		if (of != NULL) {
			 // Cancel the other object's future.
			 // And recalculate other futures if needed.
			of->unschedule();
			if (of->a != a && of->a != picked) {
				of->a->future = NULL;
				return check_interactions(of->a);
			}
			if (of->b != a && of->b != picked) {
				of->b->future = NULL;
				return check_interactions(of->b);
			}
		}
	}
}


void main_loop () {
	now = 0*T;
	set_video({320*D, 240*D});
	get_input();  // This is not accurate
	if (!screen) screen = new Screen();
	screen->create();
	if (!kbd) kbd = new Keyboard();
	kbd->create();
	while (Event* e = current_event) {
		 // Drop past events if unneeded
		if (e->t - now > EVENT_REPEAT_INTERVAL)
			e->prev = NULL;
		now = e->t;
		delay_to(now);
		get_input();  // This is not accurate
		current_event = e->next;
		e->happen();
	}
}


void dump_event_list () {
	for (Event* e = current_event; e; e = e->next) {
		printf("At %lf do 0x%08x on 0x%08x & 0x%08x\n",
			(double)(e->t/T), (uint)(void*)e->call,
			(uint)(void*)e->a, (uint)(void*)e->b);
	}
}






#endif
