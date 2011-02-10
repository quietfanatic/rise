#ifndef _HAVE_GLOBALS_H
#define _HAVE_GLOBALS_H


 // TO BE REPLACED by attributes of Room
Color background_color = 0x000000;
Vec2<Distance> game_size = {640*D, 480*D};
Frequency game_fps = 30/T;



 // Global time counter
Time now = 0*T;

 // Event list anchor
Event* current_event = NULL;

 // Global object list
 // Currently used for all object iterations
 // Eventually will only be used for drawing
 // Other operations will go by class.
Object* first_object = NULL;



 // Required global objects
Screen* screen = NULL;
Keyboard* kbd = NULL;
Room* room = NULL;
//Camera* camera = NULL;



#endif
