#ifndef _HAVE_OBJ_ROOM_CPP
#define _HAVE_OBJ_ROOM_CPP

#include "obj/Room.h"
#include "obj/Boundary.c++"

add_IC(Room);
//struct Room : public Boundary {
	Vec2<Distance> Room::size () {
		return _size;
	}
	
	float Room::depth () { return -INF; }
	void Room::draw () {
		background_color.draw({0*D, 0*D}, _size);
	}
	
	void Room::init () { }

	void Room::create () {
		Object::create();
		init();
	}
	void Room::destroy () {
		for (Object* o = first_object; o; o = first_object) {
			o->destroy();
		}
		Object::destroy();
	}

	Room::Room () : Boundary({0*D, 0*D}),
	          _size({640*D, 480*D}),
	          fps(30/T),
			  background_color(Color(0x000000)) { }
//};




#endif
