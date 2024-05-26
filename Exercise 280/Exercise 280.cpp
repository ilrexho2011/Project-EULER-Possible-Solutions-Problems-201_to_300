#include <cassert>
#include <cstdio>

#include "timer.h"

size_t const N=5;
size_t const M=N/2;
size_t const R=2*N;
size_t const S=2000;


struct cached_move
{
	bool valid;
	double e[N];
	double a[N];
	double p[N];
};
cached_move cache[N][1<<N]={0};
cached_move cache0={0};


double solve(size_t round=0, size_t pos=M, int seed=(1<<N)-1, int depo=(1<<N)-1)
{
	if(round==R)
		return 0.0;
	bool carrying=round%2==1;
	int trap=carrying?depo:seed;
	cached_move &c= (round==0)?cache0:cache[pos][trap];
	if(!c.valid)
	{
		c.valid=true;
		double a[N][N]={0};
		a[round==0?M:N-1][pos]=1.0;
		for(size_t n=1; n<=S; ++n)
		{
			double b[N][N]={0};
			// 4 corners
			b[1][0]+= a[0][0]/2.0;
			b[0][1]+= a[0][0]/2.0;
			b[N-2][0]+= a[N-1][0]/2.0;
			b[N-1][1]+= a[N-1][0]/2.0;
			b[N-2][N-1]+= a[N-1][N-1]/2.0;
			b[N-1][N-2]+= a[N-1][N-1]/2.0;
			b[1][N-1]+= a[0][N-1]/2.0;
			b[0][N-2]+= a[0][N-1]/2.0;

			// sides between corders
			for(size_t i=1; i<N-1; ++i)
			{
				b[0][i-1]+= a[0][i]/3.0;
				b[0][i+1]+= a[0][i]/3.0;
				b[1][i]  += a[0][i]/3.0;

				b[N-1][i-1]+= a[N-1][i]/3.0;
				b[N-1][i+1]+= a[N-1][i]/3.0;
				b[N-2][i]  += a[N-1][i]/3.0;

				b[i-1][0]+= a[i][0]/3.0;
				b[i+1][0]+= a[i][0]/3.0;
				b[i]  [1]+= a[i][0]/3.0;

				b[i-1][N-1]+= a[i][N-1]/3.0;
				b[i+1][N-1]+= a[i][N-1]/3.0;
				b[i]  [N-2]+= a[i][N-1]/3.0;
			}

			// inside
			for(size_t i=1; i<N-1; ++i)
				for(size_t j=1; j<N-1; ++j)
				{
					b[i-1][j]  += a[i][j]/4.0;
					b[i]  [j-1]+= a[i][j]/4.0;
					b[i+1][j]  += a[i][j]/4.0;
					b[i]  [j+1]+= a[i][j]/4.0;
				}

			for(size_t i=0; i<N; ++i)
				for(size_t j=0; j<N; ++j)
					a[i][j]=b[i][j];

			// check traps
			for(size_t i=0; i<N; ++i)
				if(trap&(1<<i))
				{
					c.e[i]+=n*a[0][i];
					c.p[i]+=a[0][i];
					a[0][i]=0.0;
				}
		}
		for(size_t i=0; i<N; ++i)
			if(trap&(1<<i))
				c.e[i]/=c.p[i];
	}

	double r=0;
	for(size_t i=0; i<N; ++i)
		if(trap&(1<<i))
		{
			int next_depo= carrying?depo-(1<<i):depo;
			int next_seed= carrying?seed:seed-(1<<i);
			r+=c.p[i]*(c.e[i]+ solve(round+1, i, next_seed, next_depo));
		}
	return r;
}


int main()
{
	timer yo;
	double r=solve();
	printf("r=%.6f\n", r);
	return 0;
}
