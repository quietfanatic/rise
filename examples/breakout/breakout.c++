#define DEBUG
#include "rise.c++"
#include "Brick.c++"
#include "Paddle.c++"
Paddle* paddle;
#include "Ball.c++"
Ball* ball;


int main () {
	rise_init();
	now = 0*T;
	room = new Room;
	room->_size = {320*D, 240*D};
	room->create();
	(screen = new Screen)->create();
	screen->fps = 60/T; // Extra-smooth animation
	//screen->fps = 0.2/T; // Test framerate-independence
	for (uint i=0; i < 10; i++)
	for (uint j=2; j < 10; j++)
		(new Brick({i*32*D, j*12*D}))->create();
	(paddle = new Paddle)->create();
	(ball = new Ball)->create();

	main_loop();
	return 0;
}
