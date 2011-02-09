
#include "rise.c++"



struct TestObject : Object {
	is_IC
	virtual void draw (Time t) {
		Color(0xff, 0xff, 0xff, 0xff).draw({32*D, 32*D}, {64*D, 64*D});
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

