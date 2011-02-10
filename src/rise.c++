#ifndef _HAVE_RISE_CPP
#define _HAVE_RISE_CPP

#include "rise.h"

#ifdef RISE_USE_OPENGL
#include "backend/sdl-opengl.c++"
#else
#include "backend/sdl.c++"
#endif
#include "interactions.c++"
#include "events.c++"
#include "obj/Object.c++"
#include "obj/Screen.c++"
#include "obj/Keyboard.c++"
#include "obj/Room.c++"


void rise_init() {
	//GC_enable_incremental();
	backend_init();
	init_interactions();
}




#endif
