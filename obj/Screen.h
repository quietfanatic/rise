#ifndef _HAVE_SCREEN_H
#define _HAVE_SCREEN_H

 // This is seperate from Camera because their interactions are
 // entirely independent from one another.

struct Screen : Object {
	is_IC;
	Time next_render;
	Frequency fps;
	Screen ();
};



#endif
