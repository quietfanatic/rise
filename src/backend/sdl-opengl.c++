#ifndef _RISE_BACKEND_SDL_OPENGL_CPP
#define _RISE_BACKEND_SDL_OPENGL_CPP


#include "backend/sdl-opengl.h"



 // Initialization
bool backend_init () {
	SDL_Init(SDL_INIT_EVERYTHING);
	return true;
};

 // Graphics


GLuint make_gl_tex (SDL_Surface* surface) {
	 // This is copypasted from a tutorial.

	GLuint texture;
	GLenum texture_format;
	GLint  nOfColors;

	 // Check that the image's width is a power of 2
	if ( (surface->w & (surface->w - 1)) != 0 ) {
		printf("warning: image's width is not a power of 2\n");
	}
 
	 // Also check if the height is a power of 2
	if ( (surface->h & (surface->h - 1)) != 0 ) {
		printf("warning: image's height is not a power of 2\n");
	}
 
         // get the number of channels in the SDL surface
        nOfColors = surface->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (surface->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }
 
	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture );
 
	// Bind the texture object
	glBindTexture( GL_TEXTURE_2D, texture );
 
	// Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
 
	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );

	return texture;
}




//struct Image : gc {

	Image::Image (SDL_Surface* surf_)
		: surf(surf_) { }
	Image::Image (const char* filename)
		: surf(IMG_Load(filename)) {
		tex = make_gl_tex(surf);
	}
	Image::~Image() {
		SDL_FreeSurface(surf);
		glDeleteTextures(1, &tex);
	}
	void Image::draw (Vec<Distance> at) {
		//SDL_Rect draw_rect = {at.x/D, at.y/D, 0, 0};
		//SDL_BlitSurface(
		//	surf, NULL,
		//	_sdl_window, &draw_rect
		//);
		glBindTexture( GL_TEXTURE_2D, tex );
 		glBegin( GL_QUADS );
			//Bottom-left vertex (corner)
			glTexCoord2i( 0, 0 );
			glVertex3f( 100.f, 100.f, 0.0f );
		 
			//Bottom-right vertex (corner)
			glTexCoord2i( 1, 0 );
			glVertex3f( 228.f, 100.f, 0.f );
		 
			//Top-right vertex (corner)
			glTexCoord2i( 1, 1 );
			glVertex3f( 228.f, 228.f, 0.f );
		 
			//Top-left vertex (corner)
			glTexCoord2i( 0, 1 );
			glVertex3f( 100.f, 228.f, 0.f );
		glEnd();
	}
	bool Image::defined () { return surf != NULL; }

//};

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


void start_render () {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

 // Window functions
void finish_render () {
	SDL_GL_SwapBuffers();
}
void set_video (Vec<Distance> size) {
	if (!(_sdl_window = SDL_SetVideoMode(size.x/D, size.y/D, 32, SDL_SWSURFACE|SDL_GL_DOUBLEBUFFER|SDL_OPENGL))) {
		printf("Error: Could not set video mode: %s\n", SDL_GetError());
	}
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);
	glViewport(0, 0, size.x/D, size.y/D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, size.x/D, size.y/D, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();
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
