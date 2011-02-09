#include "obj/Boundary.c++"

struct Room : public Boundary {
	is_IC
	virtual Vec2<Distance> size () {
		return {320*D, 240*D};
	}

	Room () : Boundary({0*D, 0*D}) { }
};
add_IC(Room);





