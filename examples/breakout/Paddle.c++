


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


inline void move_paddle_left(Paddle* a, Keyboard* kbd) {
	a->keyvel.x = -120*D/T;
}

inline void move_paddle_right(Paddle* a, Keyboard* kbd) {
	a->keyvel.x = 120*D/T;
}

inline void stop_paddle(Paddle* a, Object* b) {
	a->keyvel.x = 0*D/T;
}

static inline Interaction interaction(Paddle* a, Keyboard* kbd) {
	if (kbd->key_pressed) {
		if (kbd->last_key == SDLK_RIGHT)
			return interact<Paddle, Keyboard, move_paddle_right>(kbd->time);
		else if (kbd->last_key == SDLK_LEFT)
			return interact<Paddle, Keyboard, move_paddle_left>(kbd->time);
		else return nointeraction;
	}
	else {
		if (kbd->last_key == SDLK_LEFT || kbd->last_key == SDLK_RIGHT)
			return interact<Paddle, Object, stop_paddle>(kbd->time);
	}
	return nointeraction;
}

add_interaction(Paddle, Keyboard)

static inline Interaction interaction(Paddle* a, Room* room) {
	return interact<Paddle, Object, stop_paddle>(time_to_collide(a, room));
}

add_interaction(Paddle, Room)
