#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#define PRIME_NUM			100 		// Assume: s has factors under 100.
#define MAX				1000000000000	// Assume: Up to 10^12 search.
#define T				200
using namespace std;
typedef unsigned int		u32;
typedef unsigned __int64	u64;
struct Exp { u64 b;	u64 e; };	// Exponent notation (b:base, e:exponent).

u64 * pr = NULL;			// Array of primes.
u32 imax = 0;				// Maximum index of pr[].
u64 s_min = MAX;			// Minimum s.
vector<Exp> v;

class Sieve {
public:
	Sieve() {};
	Sieve(u32 num);
	~Sieve() {
		if (_prime != NULL) delete _prime;
		if (_array != NULL) delete _array;
	};
	u64 * Array(u32 & imax);
	bool * _prime;
	u64 * _array;
	u32 _imax;
	u64 _num;
};

Sieve::Sieve(u32 num)
	: _prime(NULL)
	, _array(NULL)
	, _imax(0)
	, _num(num)
{
	_prime = new bool [num + 1];
	for (u64 i = 0; i <= num; i ++) _prime[i] = true;
	_prime[0] = _prime[1] = false;
	u64 max = (u64)sqrt((double)num) + 1;
	{
		u64 j = 2 * 2;
		while (j <= num) {
			_prime[j] = false;
			j += 2;
		}
	}
	{
		u64 j = 2 * 3;
		while (j <= num) {
			_prime[j] = false;
			j += 3;
		}
	}
	for (u64 i = 5; i <= max; i += 6) {
		u64 j = 2 * i;
		while (j <= num) {
			_prime[j] = false;
			j += i;
		}
	}
	for (u64 i = 7; i <= max; i += 6) {
		u64 j = 2 * i;
		while (j <= num) {
			_prime[j] = false;
			j += i;
		}
	}
}

u64 * Sieve::Array(u32 & imax)
{
	size_t prmax = (size_t)(1.2 * _num / log((double)_num));
	if (_array == NULL) {
		_array = new u64 [prmax];
		imax = 0;
		for (u64 j = 2; j < _num; j ++) {
			if (_prime[j]) {
				_array[imax ++] = j;
				if (imax >= prmax) break;
			}
		}
		_imax = imax;
	}
	return _array;
}

// Whether there exists integer x such that: a/b <= x <= c/d.
bool IsIntegarExist(u64 a, u64 b, u64 c, u64 d) {
	u64 r = c / d - a / b + 1;
	if (a % b != 0) r --;
	return r > 0;
}

// Sub-routine of Divisor().
void DivisorSub(u64 n, u32 i, vector<Exp> &v, vector<u64> &u) {
	u64 tmp = n;
	if (i == v.size() - 1) {
		for (u32 j = 0; j <= v[i].e; j ++) {
			u.push_back(tmp);
			tmp *= v[i].b;
		}
	} else {
		for (u32 j = 0; j <= v[i].e; j ++) {
			DivisorSub(tmp, i + 1, v, u);
			tmp *= v[i].b;
		}
	}
}

// Convert vector of Exp to their product's divisors.
void Divisor(vector<Exp> &v, vector<u64> &u) {
	if (v.empty()) return;
	DivisorSub(1, 0, v, u);
}

// Recursive search procedure.
void Next(u32 imin, u64 s) {
	vector<u64> u;
	Divisor(v, u);
	if (u.size() >= T) {
		sort(u.begin(), u.end());
		u32 count = 0;
		for (vector<u64>::size_type t = 0; t < u.size(); t ++) {
			if (u[t] == 1) continue;
			u64 a = u[t];
			u64 b = s / u[t];
			if (a > b) break;
			if (a % 2 == 1) {
				if (!IsIntegarExist(b, a + 1, b, a - 1)) count ++;
			} else {
				if (!IsIntegarExist(b - 1, a + 1, b + 1, a - 1)) count ++;
			}
		}
		if (count == T) {
			if (s < s_min) {
				s_min = s;
			}
		}
	}
	for (u32 i = imin; i < imax; i ++) {
		u64 s_new = s * pr[i]; 
		if (s_new >= s_min) break;
		if (i == imin && !v.empty()) v.back().e ++;
		else {
			Exp ex = { pr[i], 1 };
			v.push_back(ex);
		}
		Next(i, s_new);
		if (i == imin) v.back().e --;
		else {
			v.pop_back();
		}
	}
}

int main(int argc, char* argv[])
{
	// Create an array of primes under PRIME_NUM by a sieve of Eratosthenes.
	Sieve sv(PRIME_NUM);
	// Convert sieve to array.
	pr = sv.Array(imax);
	// Start a recursive search.
	Next(0, 1);
	cout << s_min << endl;
}