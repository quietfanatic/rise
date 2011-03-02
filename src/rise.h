#ifndef _RISE_RISE_H
#define _RISE_RISE_H

 // Debug control
#ifdef DEBUG
#define DEBUGLOG(...) printf(__VA_ARGS__)
#define DBG(level, ...) if (DEBUG >= level) printf(__VA_ARGS__);
#else
#define DEBUGLOG(...)
#define DBG(level, ...)
#endif

 // External
#include <stdio.h>
#include <gc/gc.h>
#include <gc/gc_cpp.h>

 // Necessary predecls
struct Object;
struct Interaction;
struct Relation;
struct Event;


#include "misc/util.h"

 // Utility types
#include "types/ints.h"
#include "types/Dim.h"
#include "types/Vec.h"
#include "types/LL.h"


 // Backend selection
#ifdef RISE_USE_OPENGL
#include "backend/sdl-opengl.h"
#else
#include "backend/sdl.h"
#endif


 // Everything else
#include "itx/interactions.h"
#include "itx/events.h"
#include "obj/Object.h"
#include "obj/Screen.h"
#include "obj/Keyboard.h"
#include "obj/Room.h"
#include "globals.h"



void rise_init ();






#endif
