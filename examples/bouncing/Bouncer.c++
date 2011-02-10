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
	virtual void draw (Time t) { color.draw(pos(t), size()); }

	Bouncer () :
		color(rand()),
		//color(0xff, 0xff, 0xff),
		width(rand()*1.0/RAND_MAX * 30*D + 2*D) {
		keypos = {rand()*1.0/RAND_MAX * 640*D - width,
		          rand()*1.0/RAND_MAX * 480*D - width};
		keyvel = {rand()*1.0/RAND_MAX * 240*D/T - 120*D/T,
		          rand()*1.0/RAND_MAX * 240*D/T - 120*D/T};
	}
};
add_IC(Bouncer)


void bouncer_bounce (Bouncer* a, Bouncer* b) {
	bounce(a, b);
}

void bouncer_edgebounce (Bouncer* a, Room* b) {
	Vec2<> dir = collision_direction(a, b);
	if (dir.x) {
		a->keyvel.x = -a->keyvel.x;
	}
	if (dir.y) {
		a->keyvel.y = -a->keyvel.y;
	}
}


interaction(Bouncer, Bouncer, {
	return time_to_collide(a, b) >> bouncer_bounce;
})
interaction(Bouncer, Room, {
	return time_to_collide(a, b) >> bouncer_edgebounce;
})





