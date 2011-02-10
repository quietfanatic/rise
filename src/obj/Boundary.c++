#ifndef _HAVE_BOUNDARY_CPP
#define _HAVE_BOUNDARY_CPP
#include "obj/Spatial.c++"
#include "obj/Boundary.h"



Vec2<Distance> Boundary::size (Time t) { return {320*D, 240*D}; }

inline Distance Boundary::right (Time t) { return _pos.x + size(t).x; }
inline Distance Boundary::bottom (Time t) { return _pos.y + size(t).y; }
inline Distance Boundary::left (Time t) { return _pos.x; }
inline Distance Boundary::top (Time t) { return _pos.y; }


Boundary::Boundary (Vec2<Distance> pos_) : Spatial(pos_) { }





#endif
