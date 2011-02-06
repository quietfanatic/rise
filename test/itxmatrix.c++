
#include "rise.h"
#include "interactions.c++"
#include "obj/Object.c++"


struct A : Object {
	is_IC
};
add_IC(A)

Interaction interaction(A* a, A* b) {
	printf("A+A\n");
	return nointeraction;
}
add_interaction(A, A)

struct B : Object {
	is_IC
};
add_IC(B)

Interaction interaction(A* a, B* b) {
	printf("A+B\n");
	return nointeraction;
}
add_interaction(A, B)



int main () {
	init_interactions();
	dump_interaction_matrix();
	Object* a = new A;
	Object* b = new B;
	interaction_dyn(a, a);
	interaction_dyn(a, b);
	return 0;
}



