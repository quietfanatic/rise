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

 // Backend (There's only one for now)
#include "backend/sdl.h"

struct Object;
struct Interaction;
struct Event;


 // Our stuff
#include "interactions.h"
#include "events.h"
#include "obj/Object.h"











#endif
