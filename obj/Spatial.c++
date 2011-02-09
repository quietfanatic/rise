#ifndef _HAVE_SPATIAL_H
#define _HAVE_SPATIAL_H



struct Spatial : Object {
	Vec2<Distance> keypos;
	virtual Vec2<Distance> pos (Time t) { return keypos; }
	virtual Vec2<Velocity> vel (Time t) { return {0*D/T, 0*D/T}; }
	Spatial () :keypos({0*D, 0*D}) { }
	Spatial (Vec2<Distance> pos_) :keypos(pos_) { }

	virtual void update () { }  // Position is constant, so no change
};



Vec2<Velocity> relvel (Spatial* a, Spatial* b, Time t) {
	return a->vel(t) - b->vel(t);
}





#endif
