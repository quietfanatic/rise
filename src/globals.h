#ifndef _RISE_GLOBALS_H
#define _RISE_GLOBALS_H





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
