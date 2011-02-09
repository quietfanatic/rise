


#include "obj/LinearRect.c++"

Image Ball_image = "ball.png";

struct Ball : public LinearRect {
	is_IC
	bool alive;
	virtual void draw (Time t) {
		Ball_image.draw(pos(t) + offset());
	}
	virtual Vec2<Distance> pos (Time t) {
		if (!alive)
			return paddle->pos(t) - (Vec2<Distance>){0*D, 7*D};
		else return Linear::pos(t);
	}
	virtual Vec2<Velocity> vel (Time t) {
		if (!alive)
			return paddle->vel(t);
		else return Linear::vel(t);
	}
	virtual Vec2<Distance> size () {
		return {6*D, 6*D};
	}
	virtual Vec2<Distance> offset () {
		return {-3*D, -3*D};
	}
	
	Ball () : LinearRect(), alive(false) { }
};
add_IC(Ball)


void bounce_x (Ball* ball, Object* room) {
	ball->keyvel.x = -ball->keyvel.x;
}
void bounce_y (Ball* ball, Object* room) {
	ball->keyvel.y = -ball->keyvel.y;
}
void destroy_x (Ball* ball, Brick* brick) {
	ball->keyvel.x = -ball->keyvel.x;
	brick->destroy();
}
void destroy_y (Ball* ball, Brick* brick) {
	ball->keyvel.y = -ball->keyvel.y;
	brick->destroy();
}

void bounce_paddle (Ball* ball, Paddle* paddle) {
	ball->keyvel.y = -ball->keyvel.y;
	ball->keyvel.x += (ball->keypos.x - paddle->keypos.x) / (0.2*T);
	if (ball->keyvel.x > 240*D/T) ball->keyvel.x = 240*D/T;
	if (ball->keyvel.x < -240*D/T) ball->keyvel.x = -240*D/T;
}

void kill_ball (Ball* ball, Room* room) {
	ball->alive = false;
}
void start_ball (Ball* ball, Room* room) {
	ball->alive = true;
	ball->keyvel = {90*D/T, -90*D/T};
}

interaction(Ball, Brick, {
	if (a->alive) {
		Vec2<> dir = collision_direction(a, b);
		Time t = time_to_collide(a, b);
		if (dir.x) return t >> destroy_x;
		if (dir.y) return t >> destroy_y;
	}
	return nointeraction;
})

interaction(Ball, Room, {
	if (a->alive) {
		Vec2<> dir = collision_direction(a, b);
		Time t = time_to_collide(a, b);
		if (dir.x) return t >> bounce_x;
		if (dir.y < 0) return t >> bounce_y;
		if (dir.y > 0) return t+(6*D/a->keyvel.y) >> kill_ball;
	}
	return nointeraction;
})


interaction(Ball, Paddle, {
	if (a->alive)
		return time_to_collide(a, b) >> bounce_paddle;
	else return nointeraction;
})

interaction(Ball, Keyboard, {
	if (!a->alive)
		if (b->last_key == SDLK_UP)
			return b->time >> start_ball;
	return nointeraction;
})


