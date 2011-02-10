#ifndef _HAVE_BOUNDARY_H
#define _HAVE_BOUNDARY_H
#include "obj/Spatial.h"



struct Boundary : public Spatial {
	virtual Vec2<Distance> size ();
	Distance right (Time t);
	Distance bottom (Time t);
	Distance left (Time t);
	Distance top (Time t);
	Boundary (Vec2<Distance>);
};










#endif
