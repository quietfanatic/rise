
#include "rise.c++"

struct KbdTest : Object {
	is_IC
};
add_IC(KbdTest);

static inline Interaction interaction(Keyboard* kbd, KbdTest* b) {
	if (kbd->key_pressed)
		printf("Key down: %d\n", kbd->last_key);
	else
		printf("Key up: %d\n", kbd->last_key);
	return nointeraction;
}
add_interaction(Keyboard, KbdTest)


int main () {
	init_interactions();
	(new KbdTest)->create();
	main_loop();
	return 0;
}


