#ifndef _HAVE_LINEAR_CPP
#define _HAVE_LINEAR_CPP
#include "obj/Spatial.c++"

struct Linear : Spatial {
	Time _time;
	Vec2<Velocity> _vel;
	virtual Mass mass () { return 1.0*M; }
	virtual Vec2<Acceleration> acc () { return NILVEC*D/T/T; }
	virtual Vec2<Velocity> vel () { return _vel; }
	virtual Vec2<Distance> pos () {
		return _pos + _vel * (now - _time);
	}

	virtual void update () {
		_pos = pos();
		_time = now;
	}
	Linear () : Spatial(), _vel({0*D/T,0*D/T}), _time(now) { }
	Linear (Vec2<Distance> pos_) : Spatial(pos_), _vel({0*D/T,0*D/T}), _time(now) { }
	Linear (Vec2<Distance> pos_, Vec2<Velocity> vel_) : Spatial(pos_), _vel(vel_), _time(now) { }
};





#endif
