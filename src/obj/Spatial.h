#ifndef _HAVE_SPATIAL_H
#define _HAVE_SPATIAL_H



struct Spatial : Object {
	Vec2<Distance> keypos;
	virtual Vec2<Distance> pos (Time t);
	virtual Vec2<Velocity> vel (Time t);
	Spatial ();
	Spatial (Vec2<Distance> pos_);

	virtual void update ();
};



Vec2<Velocity> relvel (Spatial* a, Spatial* b, Time t);





#endif