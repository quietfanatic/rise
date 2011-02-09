
#include "rise.c++"


struct A : Object {
	is_IC
};
add_IC(A)

void printAA (A* a, A* b) { printf("A+A\n"); }

Interaction interaction(A* a, A* b) {
	return interact<A, A, printAA>(now);
}
add_interaction(A, A)

struct B : Object {
	is_IC
};
add_IC(B)

void printAB (A* a, B* b) { printf("A+B\n"); }
Interaction interaction(A* a, B* b) {
	return interact<A, B, printAB>(now);
}
add_interaction(A, B)



int main () {
	init_interactions();
	dump_interaction_matrix();
	Object* a = new A;
	Object* b = new B;
	(*interaction_dyn(a, a).call)(a, a);
	(*interaction_dyn(a, b).call)(a, b);
	return 0;
}



