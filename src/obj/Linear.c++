#ifndef _HAVE_LINEAR_CPP
#define _HAVE_LINEAR_CPP
#include "obj/Spatial.c++"

struct Linear : Spatial {
	Time keytime;
	Vec2<Velocity> keyvel;
	virtual Mass mass () { return 1.0*M; }
	virtual Vec2<Velocity> vel (Time t) { return keyvel; }
	virtual Vec2<Distance> pos (Time t) {
		return keypos + keyvel * (t - keytime);
	}

	virtual void update () {
		keypos = pos(now);
		keytime = now;
	}
	Linear () : Spatial(), keyvel({0*D/T,0*D/T}), keytime(now) { }
	Linear (Vec2<Distance> pos_) : Spatial(pos_), keyvel({0*D/T,0*D/T}), keytime(now) { }
	Linear (Vec2<Distance> pos_, Vec2<Velocity> vel_) : Spatial(pos_), keyvel(vel_), keytime(now) { }
};





#endif
