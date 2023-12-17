#include <stdio.h>
#include <stdlib.h>


#define lim 2000000000

int main()  {
    
	int a,a2,b,i,j,n,si=lim/8,ct;
	unsigned int *A,Bit[32],x;
	A=(unsigned int*)(malloc)(si*sizeof(unsigned int));
	
	Bit[0]=1;
	for(n=1;n<32;n++)  Bit[n]=2*Bit[n-1];
	for(i=0;i<si;i++)  A[i]=0;
	
	for(a=1;2*a*a<lim;a++)  {
	    a2=a*a;
		for(b=a;a2+b*b<lim;b++)  {
		    n=a2+b*b;
		    A[n>>3]|=Bit[(n&7)<<2];
		}
	}
	for(a=1;a*a<lim;a++)  {
	    a2=a*a;
		for(b=1;a2+2*b*b<lim;b++)  {
		    n=a2+2*b*b;
		    A[n>>3]|=Bit[1+((n&7)<<2)];
		}
	}
	for(a=1;a*a<lim;a++)  {
	    a2=a*a;
		for(b=1;a2+3*b*b<lim;b++)  {
		    n=a2+3*b*b;
		    A[n>>3]|=Bit[2+((n&7)<<2)];
		}
	}
	for(a=1;a*a<lim;a++)  {
	    a2=a*a;
		for(b=1;a2+7*b*b<lim;b++)  {
		    n=a2+7*b*b;
		    A[n>>3]|=Bit[3+((n&7)<<2)];
		}
	}
	
	ct=0;
	for(i=0;i<si;i++)  {
		x=A[i];
		for(j=0;j<8;j++)  {
		    if((x&15)==15)  ct++;
			x>>=4;
		}
	}
	printf("%d\n",ct);
	return 0;
}