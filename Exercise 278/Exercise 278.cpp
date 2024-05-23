#include <stdio.h>
#include <stdlib.h>

#define N 5000
#define ISPRIME(x) (x&1?!sieve[x>>1]:x==2)

static char sieve[N/2];
int *primes;

int createPrimes() {
    int i,j,cnt;
    sieve[0]=1;
    for (i=1;i*i<=N/4;i++)
        if (!sieve[i])
            for (j=2*i*(i+1);j<N/2;j+=2*i+1)
                sieve[j]=1;
    cnt=1;
    for (i=1;i<N/2;i++) cnt+=!sieve[i];
    primes=(int *)malloc(cnt*sizeof(*primes));
    primes[0]=2;
    for (j=1,i=1;i<N/2;i++)
        if (!sieve[i]) primes[j++]=2*i+1;
    return cnt;
}

int main() {
    int i,j,k,n;
    long long sum=0,p,q,r;
    n=createPrimes();
    for (i=2;i<n;i++)
        for (r=primes[i],j=1;j<i;j++)
            for (q=primes[j],k=0;k<j;k++)
                p=primes[k],sum+=2*p*r*q-p*q-p*r-q*r;
    printf("%lli\n",sum);
    return 0;
}