#ifndef _HAVE_SYNTAX_H
#define _HAVE_SYNTAX_H


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

#define nointeraction ((Interaction){NAN*T, NULL, NULL})


 // Syntax for interaction checking routines
#define interaction(A, B, ...) static inline Interaction itx_##A##_##B (Object* a_, Object* b_) { __attribute__((__unused__)) A* a = static_cast<A*>(a_); __attribute__((__unused__)) B* b = static_cast<B*>(b_); __VA_ARGS__ } add_interaction(A, B)


#endif
