#ifndef _HAVE_LINEAR_CPP
#define _HAVE_LINEAR_CPP
#include "obj/Linear.h"
#include "obj/Spatial.c++"

//struct Linear : Spatial {
	Mass Linear::mass () { return 1.0*M; }
	Vec2<Acceleration> Linear::acc () { return NILVEC*D/T/T; }
	Vec2<Velocity> Linear::vel () { return _vel; }
	Vec2<Distance> Linear::pos () {
		return _pos + _vel * (now - _time);
	}

	void Linear::update () {
		_pos = pos();
		_time = now;
	}
	Linear::Linear () : Spatial(), _vel({0*D/T,0*D/T}), _time(now) { }
	Linear::Linear (Vec2<Distance> pos_) : Spatial(pos_), _vel({0*D/T,0*D/T}), _time(now) { }
	Linear::Linear (Vec2<Distance> pos_, Vec2<Velocity> vel_) : Spatial(pos_), _vel(vel_), _time(now) { }
//};





#endif
