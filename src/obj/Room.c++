#ifndef _HAVE_OBJ_ROOM_CPP
#define _HAVE_OBJ_ROOM_CPP

#include "obj/Room.h"
#include "obj/Boundary.c++"

add_IC(Room);
//struct Room : public LinearRect {
	Vec2<Distance> Room::size () {
		return _size;
	}
	
	float Room::depth () { return -INF; }
	void Room::draw () {
	//	background_color.draw({0*D, 0*D}, _size);
	}
	
	void Room::init () { }

	void Room::create () {
		Object::create();
		Boundary* b;
		b = new Boundary_left; b->_size.y = _size.y; b->_size.x = 0*D; b->create();
		//printf("Boundary left: %p\n", b);
		b = new Boundary_top; b->_size.x = _size.x; b->_size.y = 0*D; b->_pos = NILVEC*D; b->create();
		//printf("Boundary top: %p\n", b);
		b = new Boundary_right; b->_size.y = _size.y; b->_pos.x = _size.x; b->create();
		//printf("Boundary right: %p\n", b);
		b = new Boundary_bottom; b->_size.x = _size.x; b->_pos.y = _size.y; b->create();
		//printf("Boundary bottom: %p\n", b);
		init();
	}
	void Room::destroy () {
		for (Object* o = first_object; o; o = first_object) {
			o->destroy();
		}
		Object::destroy();
	}

	Room::Room () :
		_size({640*D, 480*D}),
		background_color(Color(0x000000)) { }
//};




#endif
