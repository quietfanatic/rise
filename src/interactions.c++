#ifndef _HAVE_INTERACTIONS_CPP
#define _HAVE_INTERACTIONS_CPP


 // Registering classes
inline ICID make_icid () { return nICs++; }

 // Registering interactions

inline bool new_IC_add_op(uint a, uint b, interaction_f p) {
	if (!IC_add_ops)
		IC_add_ops = (IC_add_op*)GC_malloc((IC_m_add_ops = 64)*sizeof(IC_add_op));
	if (IC_n_add_ops == IC_m_add_ops - 1)
		IC_add_ops = (IC_add_op*)GC_realloc(IC_add_ops, (IC_m_add_ops*=2)*sizeof(IC_add_op));
	IC_add_ops[IC_n_add_ops++] = {a, b, p};
	return true;
}
inline bool new_IC_inh_op(uint a, uint b) {
	if (!IC_inh_ops)
		IC_inh_ops = (IC_op*)GC_malloc((IC_m_inh_ops = 16)*sizeof(IC_op));
	if (IC_n_inh_ops == IC_m_inh_ops - 1)
		IC_inh_ops = (IC_op*)GC_realloc(IC_inh_ops, (IC_m_inh_ops*=2)*sizeof(IC_op));
	IC_inh_ops[IC_n_inh_ops++] = {a, b};
	return true;
}
inline bool new_IC_del_op(uint a, uint b) {
	if (!IC_del_ops)
		IC_del_ops = (IC_op*)GC_malloc((IC_m_del_ops = 16)*sizeof(IC_op));
	if (IC_n_del_ops == IC_m_del_ops - 1)
		IC_del_ops = (IC_op*)GC_realloc(IC_del_ops, (IC_m_del_ops*=2)*sizeof(IC_op));
	IC_del_ops[IC_n_del_ops++] = {a, b};
	return true;
}


 // Constructing interaction matrix
void init_interactions () {
	interaction_matrix = (interaction_f*) GC_malloc(nICs*nICs*sizeof(interaction_f));
	 // GC_malloc initializes to NULLs.
	uint i;
	for (i=0; i < IC_n_add_ops; i++) {
		IC_add_op op = IC_add_ops[i];
		ITX_LOOKUP(op.a, op.b) = op.p;
	}
	GC_free(IC_add_ops);
	for (i=0; i < IC_n_inh_ops; i++) {
		IC_op op = IC_inh_ops[i];
		for (uint j = 0; j < nICs; j++) {
			 // replace only those not overridden
			if (!ITX_LOOKUP(op.a, j)
			 && !ITX_LOOKUP(j, op.a)) {
				if      (ITX_LOOKUP(op.b, j))
				         ITX_LOOKUP(op.a, j)
				       = ITX_LOOKUP(op.b, j);
				else if (ITX_LOOKUP(j, op.b))
				         ITX_LOOKUP(j, op.a)
				       = ITX_LOOKUP(j, op.b);
			}
		}
	}
	GC_free(IC_inh_ops);
	for (i=0; i < IC_n_del_ops; i++) {
		IC_op op = IC_del_ops[i];
		ITX_LOOKUP(op.a, op.b) = NULL;
		ITX_LOOKUP(op.b, op.a) = NULL;
	}
	GC_free(IC_del_ops);
	 // Phew!  Now the interaction matrix is set up.
	return;
}

 // For debugging, print matrix to terminal
void dump_interaction_matrix() {
	printf("    ");
	for (uint i=0; i < nICs; i++)
		printf(" _%02d_    ", i);
	printf("\n");
	for (uint i=0; i < nICs; i++) {
		printf("%02d: ", i);
		for (uint j=0; j < nICs; j++)
			printf("%p", (void*)ITX_LOOKUP(i, j));
		printf("\n");
	}
}



 // Wrapper for dynamically selected interaction

inline Interaction interaction_dyn(Object* a, Object* b) {
	int aid = a->icid();
	int bid = b->icid();
	if (ITX_LOOKUP(aid, bid))
		return (*ITX_LOOKUP(aid, bid))(a, b);
	if (ITX_LOOKUP(bid, aid))
		return (*ITX_LOOKUP(bid, aid))(b, a);
	return nointeraction;
}


#endif
