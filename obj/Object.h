#ifndef _HAVE_OBJECT_H
#define _HAVE_OBJECT_H






struct Object : LL<Object> {
	Event* future;

	virtual ICID icid ();
	virtual void draw (Time t);
	virtual void create ();
	virtual void destroy ();

	Object ();  // hate constructors HATE
};








#endif
