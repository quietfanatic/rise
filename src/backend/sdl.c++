#ifndef _RISE_BACKEND_SDL_CPP
#define _RISE_BACKEND_SDL_CPP


#include "backend/sdl.h"



 // Initialization
bool backend_init () {
	SDL_Init(SDL_INIT_VIDEO);
	return true;
};

 // Graphics

//SDL_Surface* _sdl_window;

 // Image type
//struct Image : gc {
//	SDL_Surface* surf;
	Image::Image (SDL_Surface* surf_)
		: surf(surf_) { }
	Image::Image (const char* filename)
		: surf(IMG_Load(filename)) { }
	Image::~Image() {
		SDL_FreeSurface(surf);
	}
	void Image::draw (Vec<Distance> at) {
		SDL_Rect draw_rect = {at.x/D, at.y/D, 0, 0};
		SDL_BlitSurface(
			surf, NULL,
			_sdl_window, &draw_rect
		);
	}
	bool Image::defined () { return surf != NULL; }
//};
//#define NO_IMAGE Image((SDL_Surface*)NULL)

 // Color type
//struct Color : gc {
//#if SDL_BYTEORDER == SDL_BIGENDIAN
//	union {
//		struct {
//			uint8 r;
//			uint8 g;
//			uint8 b;
//			uint8 a;
//		};
//		uint32 repr;
//	};
//#else
//	union {
//		struct {
//			uint8 b;
//			uint8 g;
//			uint8 r;
//			uint8 a;
//		};
//		uint32 repr;
//	};
//#endif
	Color::Color (uint32 hex)
		:r(hex / 65536 % 255), g(hex / 255 % 255), b(hex % 255), a(255) { }
	Color::Color (uint8 r_, uint8 g_, uint8 b_)
		:r(r_), g(g_), b(b_), a(0xff) { }
	Color::Color (uint8 r_, uint8 g_, uint8 b_, uint8 a_)
		:r(r_), g(g_), b(b_), a(a_) { }
	Color::Color () :repr(0xffffffff) { }
	Color::operator uint32 () { return repr; }

	void Color::draw (Vec<Distance> at, Vec<Distance> size) {
		SDL_Rect draw_rect = {at.x/D, at.y/D, size.x/D, size.y/D};
		SDL_FillRect(_sdl_window, &draw_rect, *this);
	}
//};
//#define NO_COLOR Color(0, 0, 0, 0)



 // Window functions
void start_render () { }
void finish_render () {
	SDL_Flip(_sdl_window);
}
void set_video (Vec<Distance> size) {
	if (!(_sdl_window = SDL_SetVideoMode(size.x/D, size.y/D, 32, SDL_SWSURFACE|SDL_ASYNCBLIT|SDL_DOUBLEBUF))) {
		printf("Error: Could not set video mode: %s\n", SDL_GetError());
	}
}
void quit_backend () {
	SDL_Quit();
}


 // Timing
void delay (Time t) {
	if (t < 0*T) {
		//printf("Cannot go back in time!\n");
		return;
	}
	SDL_Delay(t*1000/T);
}

void start_timer() {
	start_ticks = SDL_GetTicks();
}


void delay_to (Time t) {
	uint ticks = SDL_GetTicks();
	delay(t - (ticks - start_ticks)*T/1000.0);
}

 // Input
void get_input () {
	SDL_Event input;
	while (SDL_PollEvent(&input)) {
		switch (input.type) {
			case SDL_QUIT: {
				exit(0);
			}
			case SDL_KEYDOWN: {
				if (input.key.keysym.sym == SDLK_ESCAPE)
					exit(0);
				else if (input.key.keysym.sym == SDLK_INSERT)
					dump_event_list();
				else if (input.key.keysym.sym < 400) {
					kbd->key_pressed = true;
					kbd->last_key = input.key.keysym.sym;
					kbd->time = now;
					kbd->key[input.key.keysym.sym] = true;
					check_interactions(kbd);
				}
				break;
			}
			case SDL_KEYUP: {
				if (input.key.keysym.sym < 400) {
					kbd->key_pressed = false;
					kbd->last_key = input.key.keysym.sym;
					kbd->time = now;
					kbd->key[input.key.keysym.sym] = false;
					check_interactions(kbd);
				}
				break;
			}
		}
	}
}



#endif
