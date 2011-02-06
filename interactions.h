#ifndef _HAVE_INTERACTIONS_H
#define _HAVE_INTERACTIONS_H


typedef void (*interaction_callback)(Object*, Object*);
 // Interaction info
struct Interaction {
	Time t;
	interaction_callback call;
};
 // Give a little syntax sugar.
template <class A, class B>
inline Interaction operator >> (Time t, void (*f)(A*, B*)) {
	return {t, reinterpret_cast<interaction_callback>(f)};
}
 // Type of (dynamic) interaction function
typedef Interaction (*interaction_f)(Object*, Object*);




 // Registering classes

typedef int ICID;
uint nICs = 0;
inline ICID make_ICID();

#define does_interactions static int _icid; virtual int icid ();
#define register_


 // Registering interactions

struct IC_op {
	ICID a;
	ICID b;
};
struct IC_add_op : IC_op {
	interaction_f* p;
};

inline bool new_IC_add_op(uint a, uint b, interaction_f* p);
inline bool new_IC_inh_op(uint a, uint b);
inline bool new_IC_del_op(uint a, uint b);
#define add_interaction(A, B) bool _add_interaction_##A##_##B = new_IC_add_op(A::_icid, B::_icid, &interaction_wrap<A, B>);
#define inherit_interactions(A, B) bool _inherit_interactions_##A##_##B = new_IC_inh_op(A::_icid, B::_icid);
#define del_interaction(A, B) bool _del_interaction_##A##_##B = new_IC_del_op(A::_icid, B::_icid


 // Wrapper for dynamically selected interaction
inline Interaction interaction_dyn(Object*, Object*);
 // Wrapper for registering interactions
     // Not needed since we are enforcing pointer compatibility.
//template <class A, class B>
//Interaction interact_wrap (Object* a, Object* b) {
//	return interaction(static_cast<A*>(a), static_cast<B*>(b));
//}


 // Interaction matrix
interaction_f** interaction_matrix = NULL;
void init_interactions();
void dump_interaction_matrix();




#endif
