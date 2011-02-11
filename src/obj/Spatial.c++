#ifndef _HAVE_SPATIAL_CPP
#define _HAVE_SPATIAL_CPP
#include "obj/Spatial.h"


//struct Spatial : Object {
//	Vec2<Distance> _pos;
	Vec2<Distance> Spatial::pos () { return _pos; }
	Vec2<Velocity> Spatial::vel () { return {0*D/T, 0*D/T}; }
	Vec2<Acceleration> Spatial::acc () { return {0*D/T/T, 0*D/T/T}; }
	Spatial::Spatial () :_pos({0*D, 0*D}) { }
	Spatial::Spatial (Vec2<Distance> pos_) :_pos(pos_) { }

	void Spatial::update () { }  // Position is constant, so no change
//};



Vec2<Velocity> relvel (Spatial* a, Spatial* b) {
	return a->vel() - b->vel();
}





#endif
