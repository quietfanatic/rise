#ifndef _HAVE_QUADRATICRECT_CPP
#define _HAVE_QUADRATICRECT_CPP
#include "obj/QuadraticRect.h"
#include "obj/LinearRect.c++"

//struct QuadraticRect : LinearRect {
	Vec2<Acceleration> QuadraticRect::acc () { return _acc; }
	Vec2<Velocity> QuadraticRect::vel () { return _vel + _acc * (now-_time); }
	Vec2<Distance> QuadraticRect::pos () { return _pos + _vel * (now-_time) + _acc * (now-_time)*(now-_time) / 2; }
	void QuadraticRect::update () { _pos = pos(); _vel = vel(); _time = now; }
	QuadraticRect::QuadraticRect () : LinearRect () { }
	QuadraticRect::QuadraticRect (Vec2<Distance> pos_) : LinearRect(pos_) { }
	QuadraticRect::QuadraticRect (Vec2<Distance> pos_, Vec2<Velocity> vel_) : LinearRect(pos_, vel_) { }
	QuadraticRect::QuadraticRect (Vec2<Distance> pos_, Vec2<Velocity> vel_, Vec2<Acceleration> acc_) : LinearRect(pos_, vel_), _acc(acc_) { }
//};


Time estimate_quadratic (Time t, Distance p, Velocity v, Acceleration a) {
	 // Newton's method, much more stable than quadratic formula.
	if (v*v < 2*a*p) { return NAN*T; }
	if (v + a*t < 0.00001*D/T) t += 1*T;
	Distance d = p + v*t + a*t*t/2;
	//printf("%f -> %f (%f)\n", t.repr, d.repr, (v + a*t).repr);
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
	rtb = -rta - 2*v.x/acc.x;
	if (rta > rtb) { SWAP(rta, rtb); }
	auto dp = a->bottom() - b->top();
	dta = estimate_quadratic(now, dp, v.y, acc.y);
	dtb = -dta - 2*v.y/acc.y;
	if (dta > dtb) { SWAP(dta, dtb); }
	auto lp = a->left() - b->right();
	lta = estimate_quadratic(now, lp, v.x, acc.x);
	ltb = -lta - 2*v.x/acc.x;
	if (lta > ltb) { SWAP(lta, ltb); }
	auto up = a->top() - b->bottom();
	uta = estimate_quadratic(now, up, v.y, acc.y);
	utb = -uta - 2*v.y/acc.y;
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
	/*
	printf("===stats for %p and %p===\n", a, b);
	printf("pos: %f,%f & %f,%f\n", a->pos().x.repr, a->pos().y.repr, b->pos().x.repr, b->pos().y.repr);
	printf("vel: %f,%f & %f,%f\n", a->vel().x.repr, a->vel().y.repr, b->vel().x.repr, b->vel().y.repr);
	printf("acc: %f,%f & %f,%f\n", a->acc().x.repr, a->acc().y.repr, b->acc().x.repr, b->acc().y.repr);
	printf("ht1: %f\n", ht1.repr);
	printf("ht2: %f\n", ht2.repr);
	printf("ht3: %f\n", ht3.repr);
	printf("ht4: %f\n", ht4.repr);
	printf("vt1: %f\n", vt1.repr);
	printf("vt2: %f\n", vt2.repr);
	printf("vt3: %f\n", vt3.repr);
	printf("vt4: %f\n", vt4.repr);
	*/
	if (ht1 != ht1 || vt1 != vt1) return NAN*T;
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
	if (ht3 != ht3 || ht3 < vt3) {
		if (vt3 < ht4) return now + vt3;
		else return NAN*T;
	}
	else {
		if (ht3 < vt4) return now + ht3;
		else return NAN*T;
	}
}











#endif
