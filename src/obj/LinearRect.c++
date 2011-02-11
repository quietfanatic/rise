#ifndef _HAVE_LINEARRECT_CPP
#define _HAVE_LINEARRECT_CPP
#include "obj/Linear.c++"
#include "obj/Boundary.c++"

struct LinearRect : Linear {
	virtual Vec2<Distance> size () { return {32*D, 32*D}; }
	virtual Vec2<Distance> offset () { return {0*D, 0*D}; }
	Distance right () { return pos().x + size().x + offset().x; }
	Distance bottom () { return pos().y + size().y + offset().y; }
	Distance left () { return pos().x + offset().x; }
	Distance top () { return pos().y + offset().y; }
	LinearRect () : Linear() { }
	LinearRect (Vec2<Distance> pos_) : Linear(pos_) { }
	LinearRect (Vec2<Distance> pos_, Vec2<Velocity> vel_) : Linear(pos_, vel_) { }
};






Vec2<double> collision_direction (LinearRect* a, LinearRect* b) {
	Vec2<Velocity> rv = relvel(a, b);
	Distance r, d, l, u;
	r = b->left() - a->right();
	if (r<0*D) r=-r;
	d = b->top() - a->bottom();
	if (d<0*D) d=-d;
	l = a->left() - b->right();
	if (l<0*D) l=-l;
	u = a->top() - b->bottom();
	if (u<0*D) u=-u;
	return
	rv.x>0*D/T ? rv.y>0*D/T ? r<d ? RIGHT : DOWN
 	                        : r<u ? RIGHT : UP
	           : rv.y>0*D/T ? l<d ? LEFT  : DOWN
	                        : l<u ? LEFT  : UP;
}

Vec2<> collision_direction (LinearRect* a, Boundary* b) {
	Vec2<Velocity> rv = relvel(a, b);
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
	r = (b->right() - a->right())   / rv.x;
	d = (b->bottom() - a->bottom()) / rv.y;
	l = (b->left() - a->left())     / rv.x;
	u = (b->top() - a->top())       / rv.y;
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
	Vec2<Velocity> rv = relvel(a, b);
	if (rv.x == 0*D/T) {
		if (!(a->bottom() > b->top() && b->bottom() > a->top()))
			return NAN*T;
		if (rv.y > 0*D/T)
			return (b->top() - a->bottom()) / rv.y;
		if (rv.y < 0*D/T)
			return (b->bottom() - a->top()) / rv.y;
		return NAN*T;
	}
	if (rv.y == 0*D/T) {
		if (!(a->right() > b->left() && b->right() > a->left()))
			return NAN*T;
		if (rv.x > 0*D/T)
			return (b->left() - a->right()) / rv.x;
		if (rv.x < 0*D/T)
			return (b->right() - a->left()) / rv.x;
		return NAN*T;
	}
	Distance rd = b->left() - a->right();
	Distance ld = b->right() - a->left();
	if (rv.x > 0*D/T) {
		if (ld < 0*D) return NAN*T;
		Distance dd = b->top() - a->bottom();
		Distance ud = b->bottom() - a->top();
		if (rv.y > 0*D/T) {
			if (ud < 0*D) return NAN*T;
			if (rd*rv.y < dd*rv.x) {
				if (dd*rv.x < ld*rv.y)
					return now + dd/rv.y;
				else return NAN*T;
			}
			else {
				if (rd*rv.y < ud*rv.x)
					return now + rd/rv.x;
				else return NAN*T;
			}
		}
		else {  // rv.y < 0*D/T
			if (dd > 0*D) return NAN*T;
			if (rd*rv.y > ud*rv.x) {
				if (ud*rv.x > ld*rv.y)
					return now + ud/rv.y;
				else return NAN*T;
			}
			else {
				if (rd*rv.y > dd*rv.x)
					return now + rd/rv.x;
				else return NAN*T;
			}
		}
	}
	else { // rv.x < 0*D/T
		if (rd > 0*D) return NAN*T;
		Distance dd = b->top() - a->bottom();
		Distance ud = b->bottom() - a->top();
		if (rv.y > 0*D/T) {
			if (ud < 0*D) return NAN*T;
			if (ld*rv.y > dd*rv.x) {
				if (dd*rv.x > rd*rv.y)
					return now + dd/rv.y;
				else return NAN*T;
			}
			else {
				if (ld*rv.y > ud*rv.x)
					return now + ld/rv.x;
				else return NAN*T;
			}
		}
		else {  // rv.y < 0*D/T
			if (dd > 0*D) return NAN*T;
			if (ld*rv.y < ud*rv.x) {
				if (ud*rv.x < rd*rv.y)
					return now + ud/rv.y;
				else return NAN*T;
			}
			else {
				if (ld*rv.y < dd*rv.x)
					return now + ld/rv.x;
				else return NAN*T;
			}
		}
	}
	/*
	Time r, d, l, u;
	r = (b->left() - a->right()) / rv.x;
	d = (b->top() - a->bottom()) / rv.y;
	l = (b->right() - a->left()) / rv.x;
	u = (b->bottom() - a->top()) / rv.y;
	return now + (
	rv.x>0*D/T ? rv.y>0*D/T ? r<d ? d<l ? d : NAN*T
	                              : r<u ? r : NAN*T
 	                        : r<u ? u<l ? u : NAN*T
	                              : r<d ? r : NAN*T
	           : rv.y>0*D/T ? l<d ? d<r ? d : NAN*T
	                              : l<u ? l : NAN*T
	                        : l<u ? u<r ? u : NAN*T
	                              : l<d ? l : NAN*T
	);*/
}

Time on_collision (LinearRect* a, Boundary* b) {
	Vec2<> dir = collision_direction(a, b);
	if (dir.x > 0)
		return now + (b->right() - a->right()) / a->_vel.x;
	if (dir.y > 0)
		return now + (b->bottom() - a->bottom()) / a->_vel.y;
	if (dir.x < 0)
		return now + (b->left() - a->left()) / a->_vel.x;
	if (dir.y < 0)
		return now + (b->top() - a->top()) / a->_vel.y;
	else return NAN*T;
}
static inline Time on_collision (Boundary* a, LinearRect* b) {
	return on_collision(b, a);
}


void bounce (LinearRect* a, LinearRect* b, double elasticity = 1.0) {
	Vec2<> dir = collision_direction(a, b);
	if (dir.x) {
		Velocity tv = (a->_vel.x * a->mass() + b->_vel.x * b->mass())
		            / (a->mass() + b->mass());
		a->_vel.x = tv - (a->_vel.x - tv)*elasticity;
		b->_vel.x = tv - (b->_vel.x - tv)*elasticity;
	}
	if (dir.y) {
		Velocity tv = (a->_vel.y * a->mass() + b->_vel.y * b->mass())
		            / (a->mass() + b->mass());
		a->_vel.y = tv - (a->_vel.y - tv)*elasticity;
		b->_vel.y = tv - (b->_vel.y - tv)*elasticity;
	}
}





#endif
