#ifndef _HAVE_OBJECT_CPP
#define _HAVE_OBJECT_CPP






//struct Object : LL<Object> {
	ICID Object::icid () { return -1; }
	 // Draw object on screen
	void Object::draw () { }
	 // Depth of object
	float Object::depth () { return 0; }
	static bool cmp_objects (Object* a, Object* b) { return a->depth() > b->depth(); }
	 // Add object to list(s)
	void Object::create () {
		replace_sort_forward(first_object, &cmp_objects);
		check_interactions(this);
	}
	 // Remove object
	void Object::destroy () {
		unlink_backward(first_object);
	}
	 // Called automatically to update object before events
	void Object::update () { }


	Object::Object () { }  // hate constructors HATE
//};








#endif
