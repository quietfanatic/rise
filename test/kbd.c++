
#include "rise.c++"

struct KbdTest : Object {
	is_IC
};
add_IC(KbdTest);

interaction(Keyboard, KbdTest, {
	if (a->key_pressed)
		printf("Key down: %d\n", a->last_key);
	else
		printf("Key up: %d\n", a->last_key);
	return nointeraction;
})


int main () {
	init_interactions();
	(new KbdTest)->create();
	main_loop();
	return 0;
}


