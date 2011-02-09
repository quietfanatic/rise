


#include "obj/LinearRect.c++"

Image Ball_image = "ball.png";

struct Ball : public LinearRect {
	is_IC
	virtual void draw (Time t) {
		Ball_image.draw(pos(t) + offset());
	}
	virtual Vec2<Distance> size () {
		return {6*D, 6*D};
	}
	virtual Vec2<Distance> offset () {
		return {-3*D, -3*D};
	}
	
	Ball (Vec2<Distance> pos_, Vec2<Velocity> vel_ = (Vec2<Velocity>){0*D/T, 0*D/T})
		: LinearRect(pos_, vel_) { }
};
add_IC(Ball)


void bounce_x (Ball* ball, Object* room) {
	ball->keyvel.x = -ball->keyvel.x;
}
void destroy_x (Ball* ball, Brick* brick) {
	ball->keyvel.x = -ball->keyvel.x;
	brick->destroy();
}
void bounce_y (Ball* ball, Object* room) {
	ball->keyvel.y = -ball->keyvel.y;
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

interaction(Ball, Brick, {
	Vec2<> dir = collision_direction(a, b);
	Time t = time_to_collide(a, b);
	if (dir.x) return t >> &destroy_x;
	if (dir.y) return t >> &destroy_y;
	return nointeraction;
})

interaction(Ball, Room, {
	Vec2<> dir = collision_direction(a, b);
	Time t = time_to_collide(a, b);
	if (dir.x) return t >> &bounce_x;
	if (dir.y) return t >> &bounce_y;
	return nointeraction;
})

interaction(Ball, Paddle, {
	return time_to_collide(a, b) >> &bounce_paddle;
})







