#ifndef _RISE_ITX_EVENT_H
#define _RISE_ITX_EVENT_H

#define EVENT_REPEAT_INTERVAL 0.000001*T
#define EVENT_BACKWARD_TOLERANCE 0.000001*T

struct Event : public gc, LL<Event>, Interaction {
	Object* a;
	Object* b;
	void happen ();
	void schedule ();
	void unschedule ();
};




void check_interactions(Object* a);

void main_loop ();

void draw_objects ();

void dump_event_list ();








#endif
