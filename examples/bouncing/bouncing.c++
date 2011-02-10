//#define DEBUG
#include "rise.c++"
#include "Bouncer.c++"



int main () {
	rise_init();
	rand(); rand();
	for (uint i=0; i < 200; i++)
		(new Bouncer)->create();
	(screen = new Screen)->create();
	screen->fps = 60/T;
	main_loop();
}
	




