#include "obj/QuadraticRect.c++"



struct Bouncer : QuadraticRect {
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
		width(rand()*1.0*rand()/RAND_MAX/RAND_MAX * 60*D + 4*D) {
		_pos = {rand()*1.0/RAND_MAX * 900*D - width,
		        rand()*1.0/RAND_MAX * 900*D - width};
		_vel = {rand()*1.0/RAND_MAX * 600*D/T - 300*D/T,
		        rand()*1.0/RAND_MAX * 600*D/T - 300*D/T};
		_acc = {rand()*1.0/RAND_MAX * 300*D/T/T - 150*D/T/T,
		        rand()*1.0/RAND_MAX * 300*D/T/T - 150*D/T/T};
		printf("Object %p is %08x; %f,%f\n", this, color.repr, _acc.x.repr, _acc.y.repr);
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
	auto r = on_collision(a, b) >> bouncer_bounce;
	//if (r.t == r.t) printf("Time between %p & %p: %f\n", a, b, r.t.repr);
	return r;
})
interaction(Bouncer, Boundary, {
	auto r = on_collision(a, b) >> bouncer_edgebounce;
	//if (r.t == r.t) printf("Time between %p & %p: %f\n", a, b, r.t.repr);
	return r;
})





