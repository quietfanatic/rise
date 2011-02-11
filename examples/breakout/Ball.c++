


#include "obj/LinearRect.c++"

Image Ball_image = "ball.png";

struct Ball : public LinearRect {
	is_IC
	bool alive;
	virtual void draw () {
		Ball_image.draw(pos() + offset());
	}
	virtual Vec2<Distance> pos () {
		if (!alive)
			return paddle->pos() - (Vec2<Distance>){0*D, 7*D};
		else return Linear::pos();
	}
	virtual Vec2<Velocity> vel () {
		if (!alive)
			return paddle->vel();
		else return Linear::vel();
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
	ball->_vel.x = -ball->_vel.x;
}
void bounce_y (Ball* ball, Object* room) {
	ball->_vel.y = -ball->_vel.y;
}
void hit_brick (Ball* ball, Brick* brick) {
	Vec2<> dir = collision_direction(ball, brick);
	if (dir.x) ball->_vel.x = -ball->_vel.x;
	if (dir.y) ball->_vel.y = -ball->_vel.y;
	brick->destroy();
}

void bounce_paddle (Ball* ball, Paddle* paddle) {
	ball->_vel.y = -ball->_vel.y;
	ball->_vel.x += (ball->_pos.x - paddle->_pos.x) / (0.2*T);
	if (ball->_vel.x > 240*D/T) ball->_vel.x = 240*D/T;
	if (ball->_vel.x < -240*D/T) ball->_vel.x = -240*D/T;
}

void kill_ball (Ball* ball, Room* room) {
	ball->alive = false;
}
void start_ball (Ball* ball, Room* room) {
	ball->alive = true;
	ball->_vel = {90*D/T, -90*D/T};
}

interaction(Ball, Brick, {
	if (a->alive) {
		return on_collision(a, b) >> hit_brick;
	}
	return nointeraction;
})

interaction(Ball, Room, {
	if (a->alive) {
		Vec2<> dir = collision_direction(a, b);
		Time t = on_collision(a, b);
		if (dir.x) return t >> bounce_x;
		if (dir.y < 0) return t >> bounce_y;
		if (dir.y > 0) return t+(6*D/a->_vel.y) >> kill_ball;
	}
	return nointeraction;
})


interaction(Ball, Paddle, {
	if (a->alive)
		return on_collision(a, b) >> bounce_paddle;
	else return nointeraction;
})

interaction(Ball, Keyboard, {
	if (!a->alive)
			return on_keypress(SDLK_UP) >> start_ball;
	return nointeraction;
})


