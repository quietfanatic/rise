#ifndef _HAVE_INTERACTIONS_H
#define _HAVE_INTERACTIONS_H


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
inline Interaction interaction_dyn(Object*, Object*);

 // Wrapper(s) for declared interaction
//template <class A, class B>
//Interaction interaction_wrap(Object* a, Object* b) {
//	return interaction(static_cast<A*>(a), static_cast<B*>(b));
//}

#endif
