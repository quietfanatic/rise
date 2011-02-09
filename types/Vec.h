

#define Vec Vec2
template <class C = double>
struct Vec2 {
	C x;
	C y;
//	C magnitude ();
};


 // negate
template <class C> static inline
auto operator - (Vec2<C> a)->Vec2<decltype(-a.x)>
                                 { return {-a.x, -a.y}; }
 // addition with vector
template <class A, class B> static inline
auto operator + (Vec2<A> a, Vec2<B> b)->Vec2<decltype(a.x + b.x)>
                                            { return {a.x + b.x, a.y + b.y}; }
template <class A, class B> static inline
auto operator - (Vec2<A> a, Vec2<B> b)->Vec2<decltype(a.x - b.x)>
                                            { return {a.x - b.x, a.y - b.y}; }
 // multiplication with scalar
template <class A, class B> static inline
auto operator * (Vec2<A> a, B b)->Vec2<decltype(a.x * b)>
                                      { return {a.x * b, a.y * b}; }
template <class A, class B> static inline
auto operator * (A a, Vec2<B> b)->Vec2<decltype(a * b.x)>
                                      { return {a * b.x, a * b.y}; }
template <class A, class B> static inline
auto operator / (Vec2<A> a, B b)->Vec2<decltype(a.x / b)>
                                      { return {a.x / b, a.y / b}; }
 // in-place
template <class A, class B> static inline
Vec2<A>& operator += (Vec2<A>& a, Vec2<B> b) { a.x += b.x; a.y += b.y; return a; }
template <class A, class B> static inline
Vec2<A>& operator -= (Vec2<A>& a, Vec2<B> b) { a.x -= b.x; a.y -= b.y; return a; }
template <class A, class B> static inline
Vec2<A>& operator *= (Vec2<A>& a, B b)       { a.x *= b; a.y *= b; return a; }
template <class A, class B> static inline
Vec2<A>& operator /= (Vec2<A>& a, B b)       { a.x /= b; a.y /= b; return a; }
 // dot product
template <class A, class B> static inline
auto dot (Vec2<A> a, Vec2<B> b)->decltype(a.x*b.x + a.y*b.y)
                                 { return a.x*b.x + a.y*b.y; }

 // Equality  (Doesn't actually make sense for doubles...)
template <class A, class B> static inline
bool operator == (Vec2<A> a, Vec2<B> b) { return a.x == b.x && a.y == b.y; }
template <class A, class B> static inline
bool operator != (Vec2<A> a, Vec2<B> b) { return a.x != b.x || a.y != b.y; }


 // Some nice preset vectors
#define RIGHT ((Vec2<>){+1,0})
#define DOWN ((Vec2<>){0,+1})
#define LEFT ((Vec2<>){-1,0})
#define UP ((Vec2<>){0,-1})
#define NILVEC ((Vec2<>){0, 0})
