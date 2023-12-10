#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ll long long

ll isqrt(ll a1) {
	// Check if sqrt function has given the exact answer. If not, adjust the answer
	ll N1=sqrt(a1);
	ll N2=N1*N1;
	if (N2==a1) return N1;
	if (N2<a1) while (1) { N1++; N2=N1*N1; if (N2==a1) return N1; if(N2>a1) return N1-1;}
	while (N1*N1>a1) N1--;
	return N1;
}

ll p210(ll R1) {
	ll R0,R00,R01,sm0=0,cn1=0,n1,N1;
	R0=R1/8;R00=R1*R1/32;R01=isqrt(R00); 
	for(n1=1;n1<R01+1;n1++) sm0+=isqrt(R00-n1*n1);
	sm0*=4;
	while (R00 && (R00%5==0)) {R00/=5;cn1++;}
	sm0+=2+4*R01-4*(cn1+1)-2*R0; if(R1%8 != 0) sm0+=2;
	return sm0+(R1/2)*3*R1;
}

int main()	{
	ll	cn1, R1= 1000000000;
	clock_t	sttm;

	sttm=clock();
	cn1=p210(R1);
	printf("\nThe count is  %lld\n",cn1);
	printf("\nTime taken %.4f seconds\n",(float)((clock()-sttm)/1000.0));

}