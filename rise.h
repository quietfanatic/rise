#ifndef _HAVE_RISE_H
#define _HAVE_RISE_H

#include <stdio.h>
#include <gc/gc.h>
#include <gc/gc_cpp.h>



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

struct Object;
struct Interaction;
struct Event;

Color background_color = 0x000000;
Vec2<Distance> game_size = {640*D, 480*D};
Frequency game_fps = 30/T;



 // Our stuff
#include "interactions.h"
#include "syntax.h"
#include "obj/Object.h"
#include "obj/Screen.h"
#include "obj/Keyboard.h"
#include "obj/Room.h"
#include "events.h"


Event* current_event = NULL;
Object* first_object = NULL;
Screen* screen = NULL;
Keyboard* kbd = NULL;
Time now = 0*T;












#endif
