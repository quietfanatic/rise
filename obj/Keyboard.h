#ifndef _HAVE_KEYBOARD_H
#define _HAVE_KEYBOARD_H

struct Keyboard : Object {
	is_IC
	bool key_pressed;
	uint last_key;
	Time time;
	bool key [400];
};






#endif
