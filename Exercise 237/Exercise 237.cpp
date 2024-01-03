#include <cstdio>

typedef unsigned long long ull;
#include "timer.h"

ull const N=1e12;
size_t const L=1e8;
size_t const A=8;
typedef size_t matrix[A][A];


int main()
{
	timer yo;
	matrix a=
	{
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 1},
		{0, 0, 0, 1, 0, 0, 0, 0},
		{1, 1, 1, 0, 1, 0, 1, 0},
		{0, 0, 0, 1, 0, 1, 0, 0},
		{0, 0, 0, 1, 0, 1, 0, 0},
		{1, 1, 0, 0, 1, 0, 1, 0},
		{0, 0, 0, 1, 0, 0, 0, 1},
	};
	matrix o={0};
	for(size_t i=0; i<A; ++i)
		o[i][i]=1;
	ull exp=N;
	while(exp)
	{
		matrix t;
		if(exp%2==1)
		{
			for(size_t i=0; i<A; ++i)
				for(size_t j=0; j<A; ++j)
				{
					ull s=0;
					for(size_t k=0; k<A; ++k)
						s+=ull(o[i][k])*a[k][j];
					t[i][j]=s%L;
				}
			for(size_t i=0; i<A; ++i)
				for(size_t j=0; j<A; ++j)
					o[i][j]=t[i][j];
		}
		if(exp/=2)
		{
			for(size_t i=0; i<A; ++i)
				for(size_t j=0; j<A; ++j)
				{
					ull s=0;
					for(size_t k=0; k<A; ++k)
						s+=ull(a[i][k])*a[k][j];
					t[i][j]=s%L;
				}
			for(size_t i=0; i<A; ++i)
				for(size_t j=0; j<A; ++j)
					a[i][j]=t[i][j];
		}
	}

	size_t r=o[3][0];
	printf("N=%g, r=%zu\n", double(N), r);
	return 0;
}