#include <iostream>
#include <cmath>


size_t const N=50;
size_t const S=20;
double const P=0.02;


double gen(double q)
{
	double p[N+1][S+1]={0.0};
	p[0][0]=1.0;
	for(size_t n=1; n<=N; ++n)
		p[n][0]=p[n-1][0]*double(n)/q;
	for(size_t s=1; s<=S; ++s)
	{
		for(size_t n=1; n<=N; ++n)
		{
			for(size_t k=1; k<=n; ++k)
			{
				double pk=p[k-1][s-1]*(1.0-double(k)/q);
				for(size_t i=k+1; i<=n; ++i)
					pk*=double(i)/q;
				p[n][s]+=pk;
			}
		}
	}
	return p[N][S];
}


int main()
{
	double ql=50.0;
	double qh=55.0;
	double p=0;
	double q=0;
	while(1e-11<qh-ql)
	{
		q=(ql+qh)/2.0;
		p=gen(q);
		if(p<P)
			qh=q;
		else ql=q;
	}

	std::cout.precision(10);
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::cout << p << " " << q << "\n";
	return 0;
}
