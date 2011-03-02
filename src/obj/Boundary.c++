#ifndef _HAVE_BOUNDARY_CPP
#define _HAVE_BOUNDARY_CPP
#include "obj/Boundary.h"
#include "obj/QuadraticRect.c++"


//struct Boundary : public QuadraticRect {
//	is_IC
	add_IC(Boundary)
	Vec2<Distance> Boundary::size () { return _size; }
	Mass Boundary::mass () { return INF*M; }
//};

//struct Boundary_left : public Boundary {
//	is_IC
	add_IC(Boundary_left)
	inherit_interactions(Boundary_left, Boundary)
//};

//struct Boundary_top : public Boundary {
//	is_IC
	add_IC(Boundary_top)
	inherit_interactions(Boundary_top, Boundary)
//};

//struct Boundary_right : public Boundary {
//	is_IC
	add_IC(Boundary_right)
	inherit_interactions(Boundary_right, Boundary)
//};

//struct Boundary_bottom : public Boundary {
//	is_IC
	add_IC(Boundary_bottom)
	inherit_interactions(Boundary_bottom, Boundary)
//};








#endif
