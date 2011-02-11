#ifndef _HAVE_KEYBOARD_CPP
#define _HAVE_KAYBOARD_CPP

add_IC(Keyboard);


Time on_keypress (uint k) {
	if (kbd->last_key == k && kbd->key_pressed)
		return kbd->time;
	else return NAN*T;
}




#endif
