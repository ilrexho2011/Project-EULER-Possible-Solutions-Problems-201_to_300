#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
bool isprime[50000];
vector <int> primes;
long long MAXX;

vector <int> admissible;


long long modpow(long long a,long long d,long long n)
{
	if(d==1)
		return a;
	if(d==0)
		return 1;
	long long tmp=modpow(a,d/2,n);
	if(d&1)
	{
		return (a*((tmp*tmp)%n))%n;
	}
	else
		return (tmp*tmp)%n;
}

bool millerrabiner(long long n)
{
	
	int k=25;
	
	
	if(n<10)
	{
		if(n==2 || n==3|| n==5 || n==7)
			return 1;
		else
			return 0;
	}
	
	long long d=n-1;int s=0;
	while(!(d&1))
	{
		d>>=1;
		s++;
	}
	for(int iters=1;iters<=k;iters++)
	{
		long long a1=rand()%100000000;
		long long a2=rand()%100000000;
		long long a=(a1*a2)%(n-3)+2;
		long long x=modpow(a,d,n);
		//printf("%lld %lld %lld -> %lld\n",a,d,n,x);
		if(x==1 || x==n-1)
			continue;
		bool primeind=0;
		for(int r=1;r<=s-1;r++)
		{
			x=modpow(x,2,n);
			if(x==1)
			{
				//printf("x is one\n");
				return 0;
			}
			if(x==n-1)
			{
				primeind=1;
				break;
			}
		}
		if(primeind)
			continue;
		//printf("iters is %d and a is %lld\n",iters,a);
		return 0;
		
	}
	return 1;
	
}




void findit(int PP,int prev,long long prod)
{
	
	if(prod>=MAXX)
		return;
	if(prev!=-1 && !(prod&1))
		admissible.push_back(prod);

	findit(PP,prev,prod*primes[PP]);
	findit(PP+1,PP,prod*primes[PP+1]);
	
}

int main()
{
	MAXX=1000000000;
	//MAXX=49;
	isprime[1]=0;
	
	for(int i=2;i<=40000;i++)
		isprime[i]=1;
	for(int i=2;i<=40000;i++)
	{
		if(isprime[i])
			for(int j=i;j*i<=40000;j++)
				isprime[j*i]=0;
	}
	for(int i=2;i<=40000;i++)
		if(isprime[i])
			primes.push_back(i);
	
	
	for(int i=0;i<primes.size()-1;i++)
		findit(i,-1,primes[i]);

	long long prod=1;
	for(int i=1;;i++)
	{
		prod=prod*2;
		if(prod>=MAXX)
			break;
		admissible.push_back((int)prod);
	}
	sort(admissible.begin(),admissible.end());
	
	bool occ[1000];
	for(int i=0;i<1000;i++)
		occ[i]=0;
	int mmax=-1;
	for(int i=0;i<admissible.size();i++)
	{
		int n=admissible[i];
		//printf("%d\n",n);
		for(int m=2;;m++)
		{
			if(millerrabiner(n+m))
			{
				occ[m]=1;
				mmax=(m>mmax?m:mmax);
				break;
			}
		}
	}
	int answer=0;
	for(int i=0;i<=mmax;i++)
		if(occ[i])
			answer+=i;
	
	printf("%d\n",answer);
		
}