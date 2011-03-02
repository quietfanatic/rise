#include "obj/LinearRect.c++"



struct Bouncer : LinearRect {
	is_IC
	Distance width;
	Color color;
	virtual Mass mass () {
		return width * width * 1*M/D/D;
	}
	virtual Vec2<Distance> size () {
		return {width, width};
	}
	virtual void draw () { color.draw(pos(), size()); }

	Bouncer () :
		color(rand()),
		//color(0xff, 0xff, 0xff),
		width(rand()*1.0*rand()/RAND_MAX/RAND_MAX * 62*D + 2*D) {
		_pos = {rand()*1.0/RAND_MAX * 900*D - width,
		        rand()*1.0/RAND_MAX * 900*D - width};
		_vel = {rand()*1.0/RAND_MAX * 600*D/T - 300*D/T,
		        rand()*1.0/RAND_MAX * 600*D/T - 300*D/T};
	}
};
add_IC(Bouncer)


void bouncer_bounce (Bouncer* a, Bouncer* b) {
	bounce(a, b, 1.0);
}

void bouncer_edgebounce (Bouncer* a, Boundary* b) {
	bounce(a, b, 1.0);
}


interaction(Bouncer, Bouncer, {
	return on_collision(a, b) >> bouncer_bounce;
})
interaction(Bouncer, Boundary, {
	return on_collision(a, b) >> bouncer_edgebounce;
})





