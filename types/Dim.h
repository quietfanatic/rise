#ifndef _HAVE_TYPES_DIM_H
#define _HAVE_TYPES_DIM_H

template <int D, int T, int M>
struct Dim_conv;

template <int D, int T, int M>
struct Dim {
	double repr;
	//Dim () { }
};

template <>
struct Dim<0, 0, 0> {
	double repr;
	//Dim () { }
	operator double () { return repr; }
};

template <int D, int T, int M>
static inline Dim<D, T, M> operator - (Dim<D, T, M> a) {
	return {-a.repr};
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator + (Dim<D, T, M> a, Dim<D, T, M> b) {
	Dim<D, T, M> r; r.repr = a.repr + b.repr; return r;
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator - (Dim<D, T, M> a, Dim<D, T, M> b) {
	Dim<D, T, M> r; r.repr = a.repr - b.repr; return r;
}
template <int Da, int Ta, int Ma, int Db, int Tb, int Mb>
static inline Dim<Da+Db, Ta+Tb, Ma+Mb> operator * (Dim<Da, Ta, Ma> a, Dim<Db, Tb, Mb> b) {
	Dim<Da+Db, Ta+Tb, Ma+Mb> r; r.repr = a.repr * b.repr; return r;
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator * (Dim<D, T, M> a, double b) {
	Dim<D, T, M> r; r.repr = a.repr * b; return r;
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator * (double a, Dim<D, T, M> b) {
	Dim<D, T, M> r; r.repr = a * b.repr; return r;
}
template <int Da, int Ta, int Ma, int Db, int Tb, int Mb>
static inline Dim<Da-Db, Ta-Tb, Ma-Mb> operator / (Dim<Da, Ta, Ma> a, Dim<Db, Tb, Mb> b) {
	Dim<Da-Db, Ta-Tb, Ma-Mb> r; r.repr = a.repr / b.repr; return r;
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator / (Dim<D, T, M> a, double b) {
	Dim<D, T, M> r; r.repr = a.repr / b; return r;
}
template <int D, int T, int M>
static inline Dim<-D, -T, -M> operator / (double a, Dim<D, T, M> b) {
	Dim<-D, -T, -M> r; r.repr = a / b.repr; return r;
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator % (Dim<D, T, M> a, Dim<D, T, M> b) {
	Dim<D, T, M> r; r.repr = b.repr * (double)(int64_t)(a.repr / b.repr); return r;
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator += (Dim<D, T, M>& a, Dim<D, T, M> b) {
	a.repr += b.repr; return a;
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator -= (Dim<D, T, M>& a, Dim<D, T, M> b) {
	a.repr -= b.repr; return a;
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator *= (Dim<D, T, M>& a, double b) {
	a.repr *= b; return a;
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator /= (Dim<D, T, M>& a, double b) {
	a.repr /= b; return a;
}
template <int D, int T, int M>
static inline Dim<D, T, M> operator %= (Dim<D, T, M>& a, Dim<D, T, M> b) {
	return a = a % b;
}
template <int D, int T, int M>
static inline bool operator == (Dim<D, T, M> a, Dim<D, T, M> b) {
	return a.repr == b.repr;
}
template <int D, int T, int M>
static inline bool operator != (Dim<D, T, M> a, Dim<D, T, M> b) {
	return a.repr != b.repr;
}
template <int D, int T, int M>
static inline bool operator >= (Dim<D, T, M> a, Dim<D, T, M> b) {
	return a.repr >= b.repr;
}
template <int D, int T, int M>
static inline bool operator <= (Dim<D, T, M> a, Dim<D, T, M> b) {
	return a.repr <= b.repr;
}
template <int D, int T, int M>
static inline bool operator > (Dim<D, T, M> a, Dim<D, T, M> b) {
	return a.repr > b.repr;
}
template <int D, int T, int M>
static inline bool operator < (Dim<D, T, M> a, Dim<D, T, M> b) {
	return a.repr < b.repr;
}

template <int D, int T, int M>
const static inline Dim<D, T, M> Dim_unit () { Dim<D, T, M> r; r.repr = 1; return r; }


typedef Dim<1, 0, 0> Distance;
typedef Dim<0, 1, 0> Time;
typedef Dim<0, 0, 1> Mass;
typedef Dim<2, 0, 0> Distance2;
typedef Dim<0, 2, 0> Time2;
typedef Dim<0, 0, 2> Mass2;
typedef Dim<0, -1, 0> Frequency;
typedef Dim<1, -1, 0> Velocity;
typedef Dim<1, -2, 0> Acceleration;
typedef Dim<1, -1, 1> Momentum;
typedef Dim<1, -2, 1> Force;
typedef Dim<2, -2, 1> Energy;


const Distance D = Dim_unit<1, 0, 0>();
const Time T = Dim_unit<0, 1, 0>();
const Mass M = Dim_unit<0, 0, 1>();






#define INF (1.0/0.0)
#define NAN (0.0/0.0)



#endif
