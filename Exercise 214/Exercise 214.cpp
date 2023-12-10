#include <stdio.h>
#define N 40000000
#define CACHESIZE 200000
#define CHAINLEN 25

static int totients[N+1];
static int totientchainlen[CACHESIZE];
static int searchcache[CACHESIZE];
static int primes[2433654] = {2};
static int numprimes = 1;

static inline int MIN(int x, int y)
{
    return (x <= y) ? x : y;
}

/* return highest idx where primes[idx] <= p */
static inline int findprime(int p)
{
    int low = 0, high = numprimes;

    if (p < 2)
        return -1;

    if (p < CACHESIZE && searchcache[p] >= 0)
        return searchcache[p];

    while (low < high)
    {
        int mid = low + ((high - low) / 2);
        if (low + 1 == high)
        {
            if (p < CACHESIZE)
                searchcache[p] = low;
            return low;
        }
        if (primes[mid] <= p)
            low = mid;
        else
            high = mid;
    }
}

static void buildtots(int i, int n, int totient)
{
    totients[n] = totient;

    if ((long long)n*primes[i] <= N)
        buildtots(i, n*primes[i], totient*primes[i]);

    for (i = (N/n <= primes[numprimes-1]) ? MIN(i-1,findprime(N/n)) : i-1; i >= 0; i--)
        buildtots(i, n*primes[i], totient*(primes[i]-1));
}

static int chainlen(int n)
{
    int l;

    if (n < CACHESIZE && totientchainlen[n])
        return totientchainlen[n];

    l = 1+chainlen(totients[n]);
    if (n < CACHESIZE)
        totientchainlen[n] = l;
    return l;
}

int main(void)
{
    int i, scanpos=3;
    long long sum=0;
    totientchainlen[1] = 1;

    for (i=0; i != CACHESIZE; i++)
        searchcache[i] = -1;

    for (i=0; i != numprimes; i++)
    {
        buildtots(i, primes[i], primes[i]-1);
        for (; scanpos <= N; scanpos += 2)
            if (!totients[scanpos])
            {
                primes[numprimes++] = scanpos;
                break;
            }
    }

    for (i=0; i != numprimes; i++)
        if (chainlen(primes[i]) == CHAINLEN)
            sum += primes[i];

    printf("%lli\n", sum);

    return 0;
}