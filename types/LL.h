





template <class C, int i = 0>
struct LL {
	C* next;
	C* prev;
	C* realthis () { return static_cast<C*>(this); }
	void link_before (C* other) {
		next = other;
		prev = other->prev;
		if (other->prev) other->prev->next = realthis();
		other->prev = realthis();
	}
	void replace_before (C*& other) {
		if (other) link_before(other);
		other = realthis();
	}
	void link_after (C* other) {
		prev = other;
		next = other->next;
		if (other->next) other->next->prev = realthis();
		other->next = realthis();
	}
	void replace_after (C*& other) {
		if (other) link_after(other);
		other = realthis();
	}
	void replace_sort_forward (C*& other, bool (&cmp)(C*, C*)) {
		if (!other) { other = realthis(); return; }
		if (cmp(realthis(), other)) {
			link_before(other);
			other = realthis(); 
			return;
		}
		C* o;
		for (o = other; o->next; o = o->next) {
			if (cmp(realthis(), o->next)) {
				link_before(o->next);
				return;
			}
		}
		prev = o;
		o->next = realthis();
	}
	void replace_sort_backward (C*& other, bool (&cmp)(C*, C*)) {
		if (!other) { other = realthis(); return; }
		if (cmp(realthis(), other)) {
			link_after(other);
			other = realthis(); 
			return;
		}
		C* o;
		for (o = other; o->prev; o = o->prev) {
			if (cmp(realthis(), o->prev)) {
				link_after(o->next);
				return;
			}
		}
		next = o;
		o->prev = realthis();
	}
	void unlink () {
		if (next) next->prev = prev;
		if (prev) prev->next = next;
	}
	void unlink_forward (C*& other) {
		unlink();
		if (other == realthis()) other = prev;
	}
	void unlink_backward (C*& other) {
		unlink();
		if (other == realthis()) other = next;
	}
};




