


struct Paddle : LinearRect {
	is_IC
	virtual Vec2<Distance> size () {
		return {40*D, 4*D};
	}
	virtual Vec2<Distance> offset () {
		return {-20*D, -2*D};
	}
	virtual void draw (Time t) {
		Color(0xff, 0xff, 0xff, 0xff).draw(pos(t) + offset(), size());
	}

	Paddle () :LinearRect({160*D, 220*D}) { }
};
add_IC(Paddle)


void move_paddle_left(Paddle* a, Keyboard* kbd) {
	a->keyvel.x = -120*D/T;
}

void move_paddle_right(Paddle* a, Keyboard* kbd) {
	a->keyvel.x = +120*D/T;
}

void stop_paddle(Paddle* a, Object* b) {
	a->keyvel.x = 0*D/T;
}


interaction(Paddle, Keyboard, {
	if (kbd->key[SDLK_RIGHT]) {
		if (kbd->key[SDLK_LEFT])
			return kbd->time >> move_paddle_left;
		else return kbd->time >> move_paddle_right;
	}
	if (kbd->key[SDLK_LEFT])
		return kbd->time >> move_paddle_left;
	return kbd->time >> stop_paddle;
})


interaction(Paddle, Room, {
	return time_to_collide(a, b) >> &stop_paddle;
})


