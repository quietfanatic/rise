#ifndef _HAVE_BOUNDARY_CPP
#define _HAVE_BOUNDARY_CPP
#include "obj/Spatial.c++"
#include "obj/Boundary.h"



Vec2<Distance> Boundary::size () { return {320*D, 240*D}; }

inline Distance Boundary::right () { return _pos.x + size().x; }
inline Distance Boundary::bottom () { return _pos.y + size().y; }
inline Distance Boundary::left () { return _pos.x; }
inline Distance Boundary::top () { return _pos.y; }


Boundary::Boundary (Vec2<Distance> pos_) : Spatial(pos_) { }





#endif
