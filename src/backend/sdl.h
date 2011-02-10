#ifndef _HAVE_BACKEND_SDL_H
#define _HAVE_BACKEND_SDL_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>



 // Initialization
bool backend_init ();

 // Graphics

SDL_Surface* _sdl_window;

 // Image type
struct Image : gc {
	SDL_Surface* surf;
//	Image() { };
	Image (SDL_Surface* surf_);
	Image (const char* filename);
	~Image();
	void draw (Vec<Distance> at);
	bool defined ();
};
#define NO_IMAGE Image((SDL_Surface*)NULL)

 // Color type
struct Color : gc {
#if SDL_BYTEORDER == SDL_BIGENDIAN
	union {
		struct {
			uint8 r;
			uint8 g;
			uint8 b;
			uint8 a;
		};
		uint32 repr;
	};
#else
	union {
		struct {
			uint8 b;
			uint8 g;
			uint8 r;
			uint8 a;
		};
		uint32 repr;
	};
#endif
	Color ();
	Color (uint32 hex);
	Color (uint8 r_, uint8 g_, uint8 b_);
	Color (uint8 r_, uint8 g_, uint8 b_, uint8 a_);
	operator uint32 ();

	void draw (Vec<Distance> at, Vec<Distance> size);
};
#define NO_COLOR Color(0, 0, 0, 0)



 // Window functions
void start_render ();
void finish_render ();
void set_video (Vec<Distance> size);
void quit_backend ();


 // Timing
void delay (Time t);

uint start_ticks;
void start_timer();


void delay_to (Time t);

 // Input
void get_input ();



#endif
