
#include "rise.c++"
#include "Bouncer.c++"



int main () {
	rise_init();
	for (uint i=0; i < 100; i++)
		(new Bouncer)->create();
	(screen = new Screen)->create();
	screen->fps = 60/T;
	main_loop();
}
	




