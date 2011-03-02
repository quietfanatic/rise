#ifndef _HAVE_QUADRATICRECT_H
#define _HAVE_QUADRATICRECT_H
#include "obj/LinearRect.h"

struct QuadraticRect : LinearRect {
	Vec2<Acceleration> _acc;
	virtual Vec2<Acceleration> acc ();
	virtual Vec2<Velocity> vel ();
	virtual Vec2<Distance> pos ();
	virtual void update ();
	QuadraticRect ();
	QuadraticRect (Vec2<Distance> pos_);
	QuadraticRect (Vec2<Distance> pos_, Vec2<Velocity> vel_);
	QuadraticRect (Vec2<Distance> pos_, Vec2<Velocity> vel_, Vec2<Acceleration> acc_);
};


Time estimate_quadratic (Time t, Distance p, Velocity v, Acceleration a);

Time on_collision (QuadraticRect* a, QuadraticRect* b);






#endif
