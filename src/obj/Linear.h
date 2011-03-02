#ifndef _HAVE_LINEAR_H
#define _HAVE_LINEAR_H
#include "obj/Spatial.h"

struct Linear : Spatial {
	Time _time;
	Vec2<Velocity> _vel;
	virtual Mass mass ();
	virtual Vec2<Acceleration> acc ();
	virtual Vec2<Velocity> vel ();
	virtual Vec2<Distance> pos ();

	virtual void update ();
	Linear ();
	Linear (Vec2<Distance> pos_);
	Linear (Vec2<Distance> pos_, Vec2<Velocity> vel_);
};





#endif
