#include <cmath>
#include <cstdio>

typedef unsigned long long ull;

#include "timer.h"
#include "sieve_primes_up_to_limit.h"
#include "factors_of.h"

ull const N=12017639147 ;
ull const M=(N+3)/2;
// C=-M mod 3
size_t const C=size_t(3-M%3);
size_t const P=size_t(sqrt(M)+1);
factors<ull, size_t> f;


// for n=[0, M), how many n solves this congruence n=b mod m, 
ull count(ull a, ull m)
{
	return (M+m-1-a)/m;
}

ull solve(ull n=1, size_t pos=0)
{
	ull r=0;
	for(; pos<f.size(); ++pos)
	{
		ull m=n*f[pos].p;
		// n=C mod 3, n=0 mod m, (3, m)=1 -> n=s mod (3*m)
		ull s=0;
		for(size_t i=0; i<3 && s%3!=C; ++i, s+=m);
		// I/E
		r+=count(s, 3*m)- solve(m, pos+1);
	}
	return r;
}


int main()
{
	timer yo;
	sieve_primes_up_to_limit primes(P);
	f.factors_of(M, primes);
	ull r=count(C, 3)- solve()- (C==0);
	printf("N=%llu, r=%llu\n", N, r);
	return 0;
}