#ifndef _HAVE_OBJ_ROOM_H
#define _HAVE_OBJ_ROOM_H

#include "obj/Boundary.h"

struct Room : public Boundary {
	is_IC
	Color background_color;
	Vec2<Distance> _size;
	virtual Vec2<Distance> size (Time t);
//	virtual Vec2<Distance> offset ();

	virtual float depth ();
	virtual void draw ();

	virtual void init ();

	virtual void create ();
	virtual void destroy ();

	Room ();
};




#endif
