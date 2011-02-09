#ifndef _HAVE_INTERACTIONS_H
#define _HAVE_INTERACTIONS_H


typedef void (*interaction_callback)(Object*, Object*);
 // Interaction info
struct Interaction {
	Time t;
	interaction_callback call;
};

 // Convert callbacks to generic form
template <class A, class B, void(&f)(A*, B*)>
void interact_callback_convert (Object* a, Object* b) {
	f(static_cast<A*>(a), static_cast<B*>(b));
}
 // Template to use callback converter
 // This syntax is extremely ugly and I wish it could be fixed
 // without a performance hit, but our language has...limitations.
template <class A, class B, void(&f)(A*, B*)>
static inline Interaction interact (Time t) {
	return {t, interact_callback_convert<A, B, f>};
}

#define nointeraction ((Interaction){NAN*T, NULL})
 // Type of (dynamic) interaction function
typedef Interaction (*interaction_f)(Object*, Object*);




 // Registering classes

typedef int ICID;
uint nICs = 0;
inline ICID make_icid();

#define is_IC static ICID _icid; virtual int icid ();
#define add_IC(C) ICID C::_icid = make_icid(); inline int C::icid () { return _icid; }


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
#define add_interaction(A, B) bool _add_interaction_##A##_##B = new_IC_add_op(A::_icid, B::_icid, &interaction_wrap<A, B>);
#define inherit_interactions(A, B) bool _inherit_interactions_##A##_##B = new_IC_inh_op(A::_icid, B::_icid);
#define del_interaction(A, B) bool _del_interaction_##A##_##B = new_IC_del_op(A::_icid, B::_icid);


 // Interaction matrix
interaction_f* interaction_matrix = NULL;
void init_interactions();
void dump_interaction_matrix();
#define ITX_LOOKUP(a, b) (interaction_matrix[(a)+(b)*nICs])


 // Wrapper for dynamically selected interaction
inline Interaction interaction_dyn(Object*, Object*);

 // Wrapper(s) for declared interaction
template <class A, class B>
Interaction interaction_wrap(Object* a, Object* b) {
	return interaction(static_cast<A*>(a), static_cast<B*>(b));
}

#endif
