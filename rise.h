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

void dump_event_list();
 // Backend (There's only one for now)
#include "backend/sdl.h"

struct Object;
struct Interaction;
struct Event;

Color background_color = 0x000000;
Vec2<Distance> game_size = {640*D, 480*D};
Frequency game_fps = 30/T;



 // Our stuff
#include "interactions.h"
#include "obj/Object.h"
#include "obj/Screen.h"
#include "events.h"


Event* current_event = NULL;
Object* first_object = NULL;
Screen* screen = NULL;
Time now = 0*T;












#endif
