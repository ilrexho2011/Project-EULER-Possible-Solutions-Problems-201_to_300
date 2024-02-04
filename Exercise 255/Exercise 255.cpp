#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <vector> 
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
long long int tenpow(int x)
{
	long long retval=1;
	for(int i=1;i<=x;i++)
		retval*=10;
	return retval;
}
long long int min(long long a,long long b){return a<b?a:b;}

int main()
{
	int n=14;
	long long int start;
	if(n&1)
	{
		start=2*tenpow((n-1)/2);
	}
	else
		start=7*tenpow((n-2)/2);
	
	long long int low=tenpow(n-1);
	long long int up=tenpow(n);
	long long int kval[100];
		
	long long count=0;
	long long int N;
	int iters;


	N=low;

	
	
	
	
	
	kval[0]=start;
	iters=1;
	count=0;
	while(1)
	{
		long long ceilval=(kval[iters-1]+((N%kval[iters-1]==0)?N/kval[iters-1]:N/kval[iters-1]+1))>>1;
		kval[iters]=ceilval;
		iters++;
		if(kval[iters-1]==kval[iters-2])
		{
			break;
		}
	}
	
	count=0;
	while(1)
	{
		long long minN=10000000000000000ll;
		for(int i=0;i<iters;i++)
		{
			long long modval=N%kval[i];
			if(modval==0)
			{
				
				minN=min(minN,N+1);
			}
			else
				minN=min(minN,N+kval[i]-modval);
				
				
		}
		
		if(minN>=up)
		{
			count+=(up-N)*(iters-1);
			break;
		}
		else
		{
			count+=(minN-N)*(iters-1);
			N=minN;
			kval[0]=start;
			iters=1;
			while(1)
			{
				long long ceilval=(kval[iters-1]+((N%kval[iters-1]==0)?N/kval[iters-1]:N/kval[iters-1]+1))>>1;
				kval[iters]=ceilval;
				iters++;
				if(kval[iters-1]==kval[iters-2])
				{
					break;
				}
				
				
				
			}
			
		}

	}
	printf("%lld\n",count);

}