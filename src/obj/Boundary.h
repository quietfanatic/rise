#ifndef _HAVE_BOUNDARY_H
#define _HAVE_BOUNDARY_H
#include "obj/QuadraticRect.h"



struct Boundary : public QuadraticRect {
	is_IC
	Vec2<Distance> _size;
	virtual Vec2<Distance> size ();
	virtual Mass mass ();
};

struct Boundary_left : public Boundary {
	is_IC
};

struct Boundary_top : public Boundary {
	is_IC
};

struct Boundary_right : public Boundary {
	is_IC
};

struct Boundary_bottom : public Boundary {
	is_IC
};








#endif
