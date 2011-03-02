//#define DEBUG
#include "rise.c++"
#include "Bouncer.c++"


int main () {
	printf("%f\n", estimate_quadratic(1.471220*T, 881.603255*D, -345.624513*D/T, 65.189079*D/T/T).repr);
	rise_init();
	//for (uint i=0; i < 23; i++)
	//	rand();
	for (uint i=0; i < 100; i++)
		(new Bouncer)->create();
	(screen = new Screen)->create();
	screen->fps = 60/T;
	room = new Room;
	room->_size = {900*D, 900*D};
	room->create();
	//room->background_color = Color(0, 0, 0, 0);
	main_loop();
}
	




