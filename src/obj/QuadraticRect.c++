#ifndef _HAVE_QUADRATICRECT_CPP
#define _HAVE_QUADRATICRECT_CPP
#include "obj/LinearRect.c++"
#include "math.h"

struct QuadraticRect : LinearRect {
	Vec2<Acceleration> _acc;
	virtual Vec2<Acceleration> acc () { return _acc; }
	virtual Vec2<Velocity> vel () { return _vel + _acc * (now-_time); }
	virtual Vec2<Distance> pos () { return _pos + _vel * (now-_time) + _acc * (now-_time)*(now-_time) / 2; }
	virtual void update () { _pos = pos(); _vel = vel(); _time = now; }
	QuadraticRect () : LinearRect () { }
	QuadraticRect (Vec2<Distance> pos_) : LinearRect(pos_) { }
	QuadraticRect (Vec2<Distance> pos_, Vec2<Velocity> vel_) : LinearRect(pos_, vel_) { }
	QuadraticRect (Vec2<Distance> pos_, Vec2<Velocity> vel_, Vec2<Acceleration> acc_) : LinearRect(pos_, vel_), _acc(acc_) { }
};


Time estimate_quadratic (Time t, Distance p, Velocity v, Acceleration a) {
	 // Newton's method, much more stable than quadratic formula.
	if (v*v < 4*a*p) { return NAN*T; }
	Distance d = p + v*t + a*t*t/2;
	while (d > 0.000001*D || d < -0.000001*D) {
		t = t - d/(v + a*t);
		d = p + v*t + a*t*t/2;
	}
	return t;
}




Time on_collision (QuadraticRect* a, QuadraticRect* b) {
	auto acc = a->acc() - b->acc();
	auto v = a->vel() - b->vel();
	Time rta, rtb, dta, dtb, lta, ltb, uta, utb;
	auto rp = a->right() - b->left();
	rta = estimate_quadratic(now, rp, v.x, acc.x);
	rtb = -rta - v.x/acc.x;
	if (rta > rtb) { SWAP(rta, rtb); }
	auto dp = a->bottom() - b->top();
	dta = estimate_quadratic(now, dp, v.y, acc.y);
	dtb = -dta - v.y/acc.y;
	if (dta > dtb) { SWAP(dta, dtb); }
	auto lp = a->left() - b->right();
	lta = estimate_quadratic(now, lp, v.x, acc.x);
	ltb = -lta - v.x/acc.x;
	if (lta > ltb) { SWAP(lta, ltb); }
	auto up = a->top() - b->bottom();
	uta = estimate_quadratic(now, up, v.y, acc.y);
	utb = -uta - v.y/acc.y;
	if (uta > utb) { SWAP(uta, utb); }
	Time ht1, ht2, ht3, ht4, vt1, vt2, vt3, vt4;
	if (acc.x > 0*D/T/T) {
		ht1 = lta; ht2 = rta;
		ht3 = rtb; ht4 = ltb;
	}
	else {
		ht1 = rta; ht2 = lta;
		ht3 = ltb; ht4 = rtb;
	}
	if (acc.y > 0*D/T/T) {
		vt1 = uta; vt2 = dta;
		vt3 = dtb; vt4 = utb;
	}
	else {
		vt1 = dta; vt2 = uta;
		vt3 = utb; vt4 = dtb;
	}
	if (ht1 != ht1 || vt1 != vt1) return NAN*T;  // Not even close
	if (ht1 < vt1) {
		if (vt1 < 0*T) goto secondpass;
		if (ht2 != ht2) {
			if (vt1 < ht4) return now + vt1;
			else return NAN*T;
		}
		else {
			if (vt1 < ht2) return now + vt1;
		}
	}
	else {
		if (ht1 < 0*T) goto secondpass;
		if (vt2 != vt2) {
			if (ht1 < vt4) return now + ht1;
			else return NAN*T;
		}
		else {
			if (ht1 < vt2) return now + ht1;
		}
	}
	secondpass:
	if (ht1 < vt1) {
		if (ht3 < vt1) {
			if (vt1 < 0*T) goto thirdpass;
			if (vt1 < ht4) return now + vt1;
			else return NAN*T;
		}
		else {
			if (ht3 < 0*T) goto thirdpass;
			if (vt2 != vt2) {
				if (ht3 < vt4) return now + ht3;
				else return NAN*T;
			}
			else {
				if (ht3 < vt2) return now + ht3;
			}
		}
	}
	else {
		if (vt3 < ht1) {
			if (ht1 < 0*T) goto thirdpass;
			if (ht1 < vt4) return now + ht1;
			else return NAN*T;
		}
		else {
			if (vt3 < 0*T) goto thirdpass;
			if (ht2 != ht2) {
				if (vt3 < ht4) return now + vt3;
				else return NAN*T;
			}
			else {
				if (vt3 < ht2) return now + vt3;
			}
		}
	}
	thirdpass:
	if (ht3 < 0*T && vt3 < 0*T) return NAN*T;
	if (ht3 < vt3) {
		if (vt3 < ht4) return now + vt3;
		else return NAN*T;
	}
	else {
		if (ht3 < vt4) return now + ht3;
		else return NAN*T;
	}
}











#endif
