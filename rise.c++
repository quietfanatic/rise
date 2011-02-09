#ifndef _HAVE_RISE_CPP
#define _HAVE_RISE_CPP

#include "rise.h"

#ifdef RISE_USE_OPENGL
#include "backend/sdl-opengl.c++"
#else
#include "backend/sdl.c++"
#endif
#include "interactions.c++"
#include "obj/Object.c++"
#include "obj/Screen.c++"
#include "obj/Keyboard.c++"
#include "events.c++"






#endif
