#ifndef _HAVE_SCREEN_CPP
#define _HAVE_SCREEN_CPP

 // This is seperate from Camera because their interactions are
 // entirely independent from one another.

//struct Screen : Object {
//	is_IC;
//	Time next_render;
//	Frequency fps;
	Screen::Screen () : fps(30/T), next_render(now) { }
//};
add_IC(Screen);

inline void render (Screen* screen, Screen* b) {
	start_render();
	if (room->background_color.a != 0)
		room->background_color.draw({0*D, 0*D}, room->_size);
	for (Object* o = first_object; o; o = o->next) {
		o->draw();
	}
	finish_render();
	DEBUGLOG("[%10.6f] Render\n", now.repr);
	screen->next_render = now + 1/screen->fps;
}

interaction(Screen, Screen, {
	if (a != b) {
		printf("Warning: Multiple screens have been defined!\n");
		return nointeraction;
	}
	return (a->next_render <= now ? now : a->next_render) >> &render;
})


#endif
