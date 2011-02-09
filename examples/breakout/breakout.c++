//#include "gc/gc.h"
//#include "gc/gc_cpp.h"
//bool _begin () { GC_enable_incremental(); return true; }
//bool _begun = _begin();

#include "rise.c++"
#include "Room.c++"
#include "Brick.c++"
#include "Paddle.c++"
Paddle* paddle;
#include "Ball.c++"
Ball* ball;



int main () {
	GC_enable_incremental();
	init_interactions();
	now = 0*T;
	//game_fps = 120/T; // Extra-smooth animation
	//game_fps = 0.2/T; // Test framerate-independence
	for (uint i=0; i < 10; i++)
	for (uint j=2; j < 10; j++)
		(new Brick({i*32*D, j*12*D}))->create();
	(paddle = new Paddle)->create();
	(ball = new Ball)->create();
	(new Room)->create();
	main_loop();
	return 0;
}
