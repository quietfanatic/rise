#ifndef _HAVE_EVENT_H
#define _HAVE_EVENT_H


struct Event : gc, LL<Event>, Interaction {
	Object* a;
	Object* b;
	void happen ();
	void cancel ();
};




void main_loop ();












#endif
