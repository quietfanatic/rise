


struct Paddle : LinearRect {
	is_IC
	virtual Vec2<Distance> size () {
		return {40*D, 4*D};
	}
	virtual Vec2<Distance> offset () {
		return {-20*D, -2*D};
	}
	virtual void draw () {
		Color(0xff, 0xff, 0xff, 0xff).draw(pos() + offset(), size());
	}

	Paddle () :LinearRect({160*D, 220*D}) { }
};
add_IC(Paddle)


void move_paddle_left(Paddle* a, Keyboard* kbd) {
	a->_vel.x = -120*D/T;
}

void move_paddle_right(Paddle* a, Keyboard* kbd) {
	a->_vel.x = +120*D/T;
}

void stop_paddle(Paddle* a, Object* b) {
	a->_vel.x = 0*D/T;
}


interaction(Paddle, Keyboard, {
	return on_keypress(SDLK_RIGHT) >> move_paddle_right
	     | on_keypress(SDLK_LEFT) >> move_paddle_left
	     | on_keyrelease(SDLK_RIGHT) >> stop_paddle
	     | on_keyrelease(SDLK_LEFT) >> stop_paddle;
})


interaction(Paddle, Boundary, {
	return on_collision(a, b) >> stop_paddle;
})


