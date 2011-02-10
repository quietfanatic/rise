#ifndef _HAVE_SPATIAL_CPP
#define _HAVE_SPATIAL_CPP
#include "obj/Spatial.h"


//struct Spatial : Object {
//	Vec2<Distance> keypos;
	Vec2<Distance> Spatial::pos (Time t) { return keypos; }
	Vec2<Velocity> Spatial::vel (Time t) { return {0*D/T, 0*D/T}; }
	Spatial::Spatial () :keypos({0*D, 0*D}) { }
	Spatial::Spatial (Vec2<Distance> pos_) :keypos(pos_) { }

	void Spatial::update () { }  // Position is constant, so no change
//};



Vec2<Velocity> relvel (Spatial* a, Spatial* b, Time t) {
	return a->vel(t) - b->vel(t);
}





#endif
