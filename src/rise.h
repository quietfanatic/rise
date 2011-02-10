#ifndef _HAVE_RISE_H
#define _HAVE_RISE_H

#include <stdio.h>
#include <gc/gc.h>
#include <gc/gc_cpp.h>

 // Necessary predecls
struct Object;
struct Interaction;
struct Event;


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


 // Various stuff
#include "interactions.h"
#include "syntax.h"
#include "events.h"

 // Required object types
#include "obj/Object.h"
#include "obj/Screen.h"
#include "obj/Keyboard.h"
#include "obj/Room.h"


 // Global things
#include "globals.h"



void rise_init ();






#endif
