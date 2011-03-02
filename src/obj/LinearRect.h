#ifndef _HAVE_LINEARRECT_H
#define _HAVE_LINEARRECT_H
#include "obj/Linear.h"

struct LinearRect : Linear {
	virtual Vec2<Distance> size ();
	virtual Vec2<Distance> offset ();
	Distance right ();
	Distance bottom ();
	Distance left ();
	Distance top ();
	LinearRect ();
	LinearRect (Vec2<Distance> pos_);
	LinearRect (Vec2<Distance> pos_, Vec2<Velocity> vel_);
};






Vec2<double> collision_direction (LinearRect* a, LinearRect* b);

Time on_collision (LinearRect* a, LinearRect* b);


void bounce (LinearRect* a, LinearRect* b, double elasticity = 1.0);





#endif
