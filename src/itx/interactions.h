#ifndef _RISE_ITX_INTERACTIONS_H
#define _RISE_ITX_INTERACTIONS_H


 // Callback types
typedef void (*interaction_callback)(Object*, Object*);
typedef void (*interaction_callback_wrapper)(void*, Object*, Object*);
 // Interaction info
struct Interaction {
	Time t;
	interaction_callback_wrapper wrap;
	void* call;
};

 // Type of (dynamic) interaction function
typedef Interaction (*interaction_f)(Object*, Object*);




 // Registering classes

typedef int ICID;
uint nICs = 0;
inline ICID make_icid();



 // Registering interactions

struct IC_add_op {
	ICID a;
	ICID b;
	interaction_f p;
};
struct IC_op {
	ICID a;
	ICID b;
};

IC_add_op* IC_add_ops;
uint IC_n_add_ops = 0;
uint IC_m_add_ops = 0;
inline bool new_IC_add_op(uint a, uint b, interaction_f p);
IC_op* IC_inh_ops;
uint IC_n_inh_ops = 0;
uint IC_m_inh_ops = 0;
inline bool new_IC_inh_op(uint a, uint b);
IC_op* IC_del_ops;
uint IC_n_del_ops = 0;
uint IC_m_del_ops = 0;
inline bool new_IC_del_op(uint a, uint b);


 // Interaction matrix
interaction_f* interaction_matrix = NULL;
void init_interactions();
void dump_interaction_matrix();
#define ITX_LOOKUP(a, b) (interaction_matrix[(a)+(b)*nICs])


 // Wrapper for dynamically selected interaction
 // Actually we're not using this
//inline Interaction interaction_dyn(Object*, Object*);

 // Wrapper(s) for declared interaction
//template <class A, class B>
//Interaction interaction_wrap(Object* a, Object* b) {
//	return interaction(static_cast<A*>(a), static_cast<B*>(b));
//}



// SYNTACTIC THINGS

 // Register classes with an ICID
#define is_IC static ICID _icid; virtual int icid ();
#define add_IC(C) ICID C::_icid = make_icid(); inline int C::icid () { return _icid; }


 // Register interactions
#define add_interaction(A, B) bool _add_interaction_##A##_##B = new_IC_add_op(A::_icid, B::_icid, &itx_##A##_##B);
#define inherit_interactions(A, B) bool _inherit_interactions_##A##_##B = new_IC_inh_op(A::_icid, B::_icid);
#define del_interaction(A, B) bool _del_interaction_##A##_##B = new_IC_del_op(A::_icid, B::_icid);

 // Callback wrapper
template <class A, class B>
static inline void itx_call_wrap (void* call, Object* a, Object* b) {
	(*(void(*)(A*, B*))(call))(static_cast<A*>(a), static_cast<B*>(b));
}

 // Syntax for defining interactions
 // Example: time_to_collide(a, b) >> &bounce_destroy
template <class A, class B>
static inline Interaction operator >> (Time t, void(*f)(A*, B*)) {
	return {t, itx_call_wrap<A, B>, (void*)f};
}
 // You can use a function-like syntax if you want.
template <class A, class B>
static inline Interaction itx (Time t, void(*f)(A*, B*)) {
	return t >> f;
}
 // Pick earliest interaction
static inline Interaction operator | (Interaction a, Interaction b) {
	if (a.t != a.t || a.t > b.t) return b;
	return a;
}

#define nointeraction ((Interaction){NAN*T, NULL, NULL})


 // Syntax for interaction checking routines
#define interaction(A, B, ...) static inline Interaction itx_##A##_##B (Object* a_, Object* b_) { __attribute__((__unused__)) A* a = static_cast<A*>(a_); __attribute__((__unused__)) B* b = static_cast<B*>(b_); __VA_ARGS__ } add_interaction(A, B)






#endif
