#include <math.h>
#include <vector>
#include <map>
#include <iostream>

typedef unsigned int		u32;
typedef __int64			s64;
typedef unsigned __int64	u64;
#define	DEL			(0.0000001)
using namespace std;

struct Exp { u64 b;	u64 e; };// Exponent notation
struct Twin { u64 x; u64 y; };

u64 pow(u64 base, u64 exp)
{
	u64 ret = 1;
	for (u64 i = 0; i < exp; i ++) ret *= base;
	return ret;
}

//	Return sqrt(n). Ex:10->3
u64 Sqrt(u64 n)
{
	return (u64)( sqrt((double)n + DEL) );
}

//	Return (a|n).
//	(a|n) = 0  if a = 0 (mod p)
//		  = +1 if x^2 = a (mod p) for some x
//		  = -1 if there is no such x
s64 Jacobi(u64 a, u64 n)
{
	s64 t = 1;
	while (a != 0) {
		while (a % 2 == 0) {
			a = a / 2;
			if (n % 8 == 3 || n % 8 == 5) t = -t;
		}
		s64 tmp = a;	a = n;	n = tmp;
		if (a % 4 == 3 && n % 4 == 3) t = -t;
		a = a % n;
	}
	if (n == 1) return t;
	return 0;
}

u64 ExtGcd( u64 a, u64 b, u64& x, u64& y ) {
	if ( b == 0 ) {
		x = 1; y = 0; return a;
	}
	u64 g = ExtGcd( b, a % b, y, x );
	y -= a / b * x;
	return g;
}


//	Find x who satisfies x*n=1 (mod p).
u64 InvMod(u64 n, u64 p) {
	u64 x, y;
	return ExtGcd ( n, p, x, y ) == 1 ? ( x + p ) % p : 0;
}

//	Return a^n (mod p)
u64 PowMod(u64 a, u64 n, u64 p) {
	if (n == 0) return 1;
	if (n % 2 == 0) return PowMod( a * a % p, n / 2, p);
	return a * PowMod( a, n - 1, p ) % p;
}

//	Return sqrt n (mod p).
u64 SqrtMod(u64 n, u64 p) {
	u64 w = 2, s = 0, q = p - 1, m = InvMod( n, p );
	while ( Jacobi ( w, p ) != -1 ) w++;
	while ( q % 2 == 0 ) q /= 2, s++;
	u64 v = PowMod( w, q, p );
	u64 r = PowMod( n, (q + 1) / 2, p );
	do {
		u64 i = 0, u = (u64) r * r * m % p;
		while ( u % p != 1 ) u = (u64) u * u % p, i++;
		if ( i == 0 ) return r;
		r = r * PowMod (v, 1 << (s - i - 1), p) % p;
	} while ( true );
}

//	Find x who satisfies x*x=n (mod p). p is prime.	
u64 Residue(u64 p, u64 n)
{
	u64 w = 2;
	for (; w <= p / 2; w ++) {
		if (Jacobi(w, p) == -1) break;
	}
	if (w > p / 2) return 0;
	u64 q = p - 1;
	u64 s = 0;
	while (q % 2 == 0) {
		s ++;
		q /= 2;
	}
	u64 r = PowMod(n, (q+1)/2, p);
	u64 v = PowMod(w, q, p);
	while (true) {
		u64 tmp = (r * r * InvMod(n, p)) % p;
		u64 i = 0;
		for (; i <= s - 1; i ++) {
			if (tmp % p == 1) break;
			tmp = (tmp * tmp) % p;
		}
		if (i == 0) break;
		r = (r * PowMod( v, pow(2LL, s-i-1), p )) % p;
	}
	r %= p;
	if (r > p / 2) r = p - r;
	return r;
}

class SquareSum {
	map<u64, Twin> cache;
	bool Serret(u64 p, Twin &t);
	bool Expand(u64 a, u64 b, u64 c, u64 d, vector<Twin> *u);
public:
	SquareSum() {};
	~SquareSum() {};
	bool Find(vector<Exp> &v, vector<Twin> &u);
};


//	Express prime p as a sum of squared two integers, based on Serret's algorithm.
//	See p.122 of "The higher arithmetic: an introduction to the theory of numbers".
bool SquareSum::Serret(u64 p, Twin &t)
{
	if (p == 2) {
		t.x = t.y = 1;
		return true;
	}
	if (p % 4 != 1) return false;
	map<u64, Twin>::iterator it = cache.find(p);
	if (it != cache.end()) {
		t = it->second;
		return true;
	}
	t.x = p;
	t.y = Residue(p, p - 1);
	vector<u64> v;
	while (t.y > 0) {
		v.push_back(t.x / t.y);
		u64 y_tmp = t.y;
		t.y = t.x - (t.x / t.y) * t.y;
		t.x = y_tmp;
	}
	t.x = v[v.size() / 2];
	t.y = 1;
	for (vector<u64>::size_type i = v.size() / 2 + 1; i < v.size(); i ++) {
		u64 x_tmp = t.x;
		t.x = v[i] * t.x + t.y;
		t.y = x_tmp;
	}
	t.y = Sqrt(p - t.x * t.x);
	if (t.y < t.x) {
		u64 tmp = t.x;
		t.x = t.y;
		t.y = tmp;
	}
	cache.insert(pair<u64, Twin>(p, t));
	return true;
}

bool SquareSum::Expand(u64 a, u64 b, u64 c, u64 d, vector<Twin> *u)
{
	Twin t;
	if (a * c >= b * d)
		t.x = a * c - b * d;
	else
		t.x = b * d - a * c;
	t.y = a * d + b * c;
	if (t.y < t.x) {
		u64 tmp = t.x;
		t.x = t.y;
		t.y = tmp;
	}
	for (vector<Twin>::size_type i = 0; i < u->size(); i ++) {
		if (u->at(i).x == t.x) return false;
	}
	u->push_back(t);
	return true;
}

//	Find all twins x>0 and y>0 which satisfy x^2+y^2=n (x<y).
//	n is the form of exponent expression.
bool SquareSum::Find(vector<Exp> &v, vector<Twin> &u)
{
	u64 n = 0;
	vector<u64> v1;
	for (vector<Exp>::size_type i = 0; i < v.size(); i ++) {
		if (v[i].b != 2 && v[i].b % 4 != 1) return false;
		for (u64 j = 0; j < v[i].e; j ++) v1.push_back(v[i].b);
		n += v[i].e;
	}
	vector<Twin> w, *u1, *u0, *u_tmp;
	if (n % 2 == 1) {
		u0 = &u;	u1 = &w;
	} else {
		u0 = &w;	u1 = &u;
	}
	Twin t1;
	if (!Serret(v1[0], t1)) return false;
	u0->push_back(t1);
	for (vector<u64>::size_type i = 1; i < v1.size(); i ++) {
		if (!Serret(v1[i], t1)) return false;
		for (vector<Twin>::size_type j = 0; j < u0->size(); j ++) {
			Expand(u0->at(j).x, u0->at(j).y, t1.x, t1.y, u1);
			Expand(u0->at(j).x, u0->at(j).y, t1.y, t1.x, u1);
		}
		u_tmp = u0;
		u0 = u1;
		u1 = u_tmp;
		u1->clear();
	}
	return true;
}

int main(int argc, char* argv[])
{
	u64 p[] = {	5, 13, 17, 29, 37, 41, 53, 61, 73, 89, 97, 101, 109, 113, 137, 149 };
	u64 sum = 0;
	SquareSum ss;
	for (u32 m = 1; m < 65536; m ++) {
		vector<Exp> v;
		u32 n = m;
		for (u32 i = 0; i < 16; i ++) {
			if (n % 2 == 1) {
				Exp e = { p[i], 1 };
				v.push_back(e);
			}
			n /= 2;
		}		
		vector<Twin> u;
		ss.Find(v, u);
		for (vector<Twin>::size_type t = 0; t < u.size(); t ++) {
			sum += u[t].x;
		}
	}
	cout << sum << endl;
}