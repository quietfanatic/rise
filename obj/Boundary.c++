#ifndef _HAVE_BOUNDARY_CPP
#define _HAVE_BOUNDARY_CPP
#include "obj/Spatial.c++"
#include "obj/Boundary.h"



Vec2<Distance> Boundary::size () { return {320*D, 240*D}; }

inline Distance Boundary::right (Time t) { return keypos.x + size().x; }
inline Distance Boundary::bottom (Time t) { return keypos.y + size().y; }
inline Distance Boundary::left (Time t) { return keypos.x; }
inline Distance Boundary::top (Time t) { return keypos.y; }


Boundary::Boundary (Vec2<Distance> pos_) : Spatial(pos_) { }





#endif
