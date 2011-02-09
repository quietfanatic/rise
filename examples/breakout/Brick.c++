

#include "obj/LinearRect.c++"



Image Brick_image = "brick.png";

struct Brick : public LinearRect {
	is_IC
	Color color;
	virtual Vec2<Distance> size () {
		return {32*D, 12*D};
	}
	virtual void draw (Time t) {
		color.draw(pos(t), size());
		Brick_image.draw(pos(t));
	}
	Brick (Vec2<Distance> pos_)
		: LinearRect(pos_, {0*D/T, 0*D/T}), color(rand()) { }
};
add_IC(Brick)


