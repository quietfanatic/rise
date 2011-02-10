#include "obj/LinearRect.c++"



struct Bouncer : LinearRect {
	is_IC
	Distance width;
	Color color;
	virtual Mass mass () {
		return width * width * 1*M/D/D;
	}
	virtual Vec2<Distance> size (Time t) {
		return {width, width};
	}
	virtual void draw (Time t) { color.draw(pos(t), size(t)); }

	Bouncer () :
		color(rand()),
		//color(0xff, 0xff, 0xff),
		width(rand()*1.0*rand()/RAND_MAX/RAND_MAX * 62*D + 2*D) {
		_pos = {rand()*1.0/RAND_MAX * 640*D - width,
		        rand()*1.0/RAND_MAX * 480*D - width};
		_vel = {rand()*1.0/RAND_MAX * 240*D/T - 120*D/T,
		        rand()*1.0/RAND_MAX * 240*D/T - 120*D/T};
	}
};
add_IC(Bouncer)


void bouncer_bounce (Bouncer* a, Bouncer* b) {
	bounce(a, b, 1.0);
}

void bouncer_edgebounce (Bouncer* a, Room* b) {
	Vec2<> dir = collision_direction(a, b);
	if (dir.x) {
		a->_vel.x = -a->_vel.x;
	}
	if (dir.y) {
		a->_vel.y = -a->_vel.y;
	}
}


interaction(Bouncer, Bouncer, {
	return on_collision(a, b) >> bouncer_bounce;
})
interaction(Bouncer, Room, {
	return on_collision(a, b) >> bouncer_edgebounce;
})





