#ifndef _HAVE_LINEARRECT_CPP
#define _HAVE_LINEARRECT_CPP
#include "obj/Linear.c++"
#include "obj/Boundary.c++"

struct LinearRect : Linear {
	virtual Vec2<Distance> size () { return {32*D, 32*D}; }
	virtual Vec2<Distance> offset () { return {0*D, 0*D}; }
	Distance right (Time t) { return pos(t).x + size().x + offset().x; }
	Distance bottom (Time t) { return pos(t).y + size().y + offset().y; }
	Distance left (Time t) { return pos(t).x + offset().x; }
	Distance top (Time t) { return pos(t).y + offset().y; }
	LinearRect () : Linear() { }
	LinearRect (Vec2<Distance> pos_) : Linear(pos_) { }
	LinearRect (Vec2<Distance> pos_, Vec2<Velocity> vel_) : Linear(pos_, vel_) { }
};






Vec2<double> collision_direction (LinearRect* a, LinearRect* b) {
	Vec2<Velocity> rv = relvel(a, b, now);
	if (rv.x == 0*D/T) {
		if (!(a->bottom(now) > b->top(now) && b->bottom(now) > a->top(now)))
			return NILVEC;
		if (rv.y > 0*D/T)
			return DOWN;
		if (rv.y < 0*D/T)
			return UP;
		return NILVEC;
	}
	if (rv.y == 0*D/T) {
		if (!(a->right(now) > b->left(now) && b->right(now) > a->left(now)))
			return NILVEC;
		if (rv.x > 0*D/T)
			return RIGHT;
		if (rv.x < 0*D/T)
			return LEFT;
		return NILVEC;
	}
	Dim<0, 1, 0> r, d, l, u;
	r = (b->left(now) - a->right(now)) / rv.x;
	d = (b->top(now) - a->bottom(now)) / rv.y;
	l = (b->right(now) - a->left(now)) / rv.x;
	u = (b->bottom(now) - a->top(now)) / rv.y;
	return
	rv.x>0*D/T ? rv.y>0*D/T ? r<d ? d<l ? DOWN  : NILVEC
	                              : r<u ? RIGHT : NILVEC
 	                        : r<u ? u<l ? UP    : NILVEC
	                              : r<d ? RIGHT : NILVEC
	           : rv.y>0*D/T ? l<d ? d<r ? DOWN  : NILVEC
	                              : l<u ? LEFT  : NILVEC
	                        : l<u ? u<r ? UP    : NILVEC
	                              : l<d ? LEFT  : NILVEC;
}

Vec2<> collision_direction (LinearRect* a, Boundary* b) {
	Vec2<Velocity> rv = relvel(a, b, now);
	if (rv.x == 0*D/T) {
		if (rv.y > 0*D/T)
			return DOWN;
		else if (rv.y < 0*D/T)
			return UP;
		else return NILVEC;
	}
	if (rv.y == 0*D/T) {
		if (rv.x > 0*D/T)
			return RIGHT;
		else if (rv.x < 0*D/T)
			return LEFT;
		else return NILVEC;
	}
	Dim<0, 1, 0> r, d, l, u;
	r = (b->right(now) - a->right(now))   / rv.x;
	d = (b->bottom(now) - a->bottom(now)) / rv.y;
	l = (b->left(now) - a->left(now))     / rv.x;
	u = (b->top(now) - a->top(now))       / rv.y;
	return
	rv.x>0*D/T ? rv.y>0*D/T ? r<d ? u<r ? RIGHT : NILVEC
	                              : l<d ? DOWN  : NILVEC
 	                        : r<u ? d<r ? RIGHT : NILVEC
	                              : l<u ? UP    : NILVEC
	           : rv.y>0*D/T ? l<d ? u<l ? LEFT  : NILVEC
	                              : r<d ? DOWN  : NILVEC
	                        : l<u ? d<l ? LEFT  : NILVEC
	                              : r<u ? UP    : NILVEC;
}
static inline Vec2<> collision_direction (Boundary* a, LinearRect* b) {
	return -collision_direction(b, a);
}

Time on_collision (LinearRect* a, LinearRect* b) {
	Vec2<> dir = collision_direction(a, b);
	if (dir.x > 0)
		return now + (b->left(now) - a->right(now)) / (a->keyvel.x - b->keyvel.x);
	if (dir.y > 0)
		return now + (b->top(now) - a->bottom(now)) / (a->keyvel.y - b->keyvel.y);
	if (dir.x < 0)
		return now + (b->right(now) - a->left(now)) / (a->keyvel.x - b->keyvel.x);
	if (dir.y < 0)
		return now + (b->bottom(now) - a->top(now)) / (a->keyvel.y - b->keyvel.y);
	else return NAN*T;
}

Time on_collision (LinearRect* a, Boundary* b) {
	Vec2<> dir = collision_direction(a, b);
	if (dir.x > 0)
		return now + (b->right(now) - a->right(now)) / a->keyvel.x;
	if (dir.y > 0)
		return now + (b->bottom(now) - a->bottom(now)) / a->keyvel.y;
	if (dir.x < 0)
		return now + (b->left(now) - a->left(now)) / a->keyvel.x;
	if (dir.y < 0)
		return now + (b->top(now) - a->top(now)) / a->keyvel.y;
	else return NAN*T;
}
static inline Time on_collision (Boundary* a, LinearRect* b) {
	return on_collision(b, a);
}


void bounce (LinearRect* a, LinearRect* b, double elasticity = 1.0) {
	Vec2<> dir = collision_direction(a, b);
	if (dir.x) {
		Velocity tv = (a->keyvel.x * a->mass() + b->keyvel.x * b->mass())
		            / (a->mass() + b->mass());
		a->keyvel.x = tv - (a->keyvel.x - tv)*elasticity;
		b->keyvel.x = tv - (b->keyvel.x - tv)*elasticity;
	}
	if (dir.y) {
		Velocity tv = (a->keyvel.y * a->mass() + b->keyvel.y * b->mass())
		            / (a->mass() + b->mass());
		a->keyvel.y = tv - (a->keyvel.y - tv)*elasticity;
		b->keyvel.y = tv - (b->keyvel.y - tv)*elasticity;
	}
}





#endif
