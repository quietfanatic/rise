


#include "obj/LinearRect.c++"

Image Ball_image = "ball.png";

struct Ball : public LinearRect {
	is_IC
	virtual void draw (Time t) {
		Ball_image.draw(pos(t));
	}
	virtual Vec2<Distance> size () {
		return {6*D, 6*D};
	}
	
	Ball (Vec2<Distance> pos_, Vec2<Velocity> vel_ = (Vec2<Velocity>){0*D/T, 0*D/T})
		: LinearRect(pos_, vel_) { }
};
add_IC(Ball)


inline void bounce_x (Ball* ball, Object* room) {
	ball->keyvel.x = -ball->keyvel.x;
}
inline void bounce_x (Ball* ball, Brick* brick) {
	ball->keyvel.x = -ball->keyvel.x;
	brick->destroy();
}
inline void bounce_y (Ball* ball, Object* room) {
	ball->keyvel.y = -ball->keyvel.y;
}
inline void bounce_y (Ball* ball, Brick* brick) {
	ball->keyvel.y = -ball->keyvel.y;
	brick->destroy();
}
inline void bounce_paddle (Ball* ball, Paddle* paddle) {
	ball->keyvel.y = -ball->keyvel.y;
	ball->keyvel.x += (ball->keypos.x - paddle->keypos.x) / (0.2*T);
	if (ball->keyvel.x > 240*D/T) ball->keyvel.x = 240*D/T;
	if (ball->keyvel.x < -240*D/T) ball->keyvel.x = -240*D/T;
}

static inline Interaction interaction(Ball* ball, Brick* brick) {
	Vec2<> dir = collision_direction(ball, brick);
	Time t = time_to_collide(ball, brick);
	if (dir.x) return interact<Ball, Brick, bounce_x>(t);
	if (dir.y) return interact<Ball, Brick, bounce_y>(t);
	return nointeraction;
}
static inline Interaction interaction(Ball* ball, Room* room) {
	Vec2<> dir = collision_direction(ball, room);
	Time t = time_to_collide(ball, room);
	if (dir.x) return interact<Ball, Object, bounce_x>(t);
	if (dir.y) return interact<Ball, Object, bounce_y>(t);
	return nointeraction;
}
static inline Interaction interaction(Ball* ball, Paddle* paddle) {
	return interact<Ball, Paddle, bounce_paddle>(time_to_collide(ball, paddle));
}

add_interaction(Ball, Brick)
add_interaction(Ball, Room)
add_interaction(Ball, Paddle)






