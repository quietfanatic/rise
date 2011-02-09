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
	if (background_color.a != 0)
		background_color.draw({0*D, 0*D}, game_size);
	for (Object* o = first_object; o; o = o->next) {
		o->draw(now);
	}
	update_window();
	screen->next_render = now + 1/screen->fps;
}

static inline Interaction interaction(Screen* a, Screen* b) {
	if (a != b) {
		printf("Warning: Multiple screens have been defined!\n");
		return nointeraction;
	}
	return interact<Screen, Screen, render>(a->next_render <= now ? now : a->next_render);
}
add_interaction(Screen, Screen)


#endif
