#define RISE_USE_OPENGL
#include "rise.c++"



struct TestObject : Object {
	is_IC
	virtual void draw (Time t) {
		Image("testimage.png").draw({32*D, 32*D});
	}
};
add_IC(TestObject)


void testinteract(TestObject* a, TestObject* b) {
	printf("Interacting!\n");
}
interaction(TestObject, TestObject, {
	return now + 0.5*T >> &testinteract;
})


int main () {
	init_interactions();
	TestObject* x = new TestObject;
	printf("%d\n", (uint)(void*)x);
	x->create();
	main_loop();
	return 0;
}

