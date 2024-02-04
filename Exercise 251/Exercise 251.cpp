#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <string.h>

typedef unsigned long long ULL;

int PRIMES[78498];
int Af[40];
int *T1;

main()
{
	buildPrimesArray();
	int HTL = 18333333 * 16;
	T1 = calloc(HTL, 4);
	if (T1 == 0)
	{
		printf("calloc fail!");
		return 0;
	}
	sieveFactorise();
	printf("cpt: %d\n", e_251());
	free(T1);
}

e_251()
{
	int l = 110000000;
	int a = -1, u = -16, v = -3;
	long long k1 = 0;
	int i, j, k;
	int mx0, mx1, mx;
	int cpt = -1;
	long long lminusa;
	double bbc;
	int am, as, is;
	int Am[80], Is[100];
	long long As[2000];
	As[0] = 1;

	while (1)
	{
		a += 3;
		if (a > (l >> 1) || k1 == 16224166)
			return cpt;

		++k1;
		v += 8;

		// factorise b*b*c=((a+1)^2 * (8a-1))/27
		// which is (k+1)^2 * (8k+5) for k=0 1 2 ...n
		// square the factorization of k+1
		u += 16, i = u;
		while (1)
		{
			if (T1[i] == 0 || i == (u + 16))
				break;
			T1[i + 1] <<= 1, i += 2;
		}

		// factorize 8k+5
		k = factors(v);

		// merge the 2 factorizations
		i = u, j = 0, am = 0;
		while (1)
		{
			if ((T1[i] == 0) || (i == (u + 16)))
			{
				while (Af[j] != 0)
					Am[am++] = Af[j++];
				break;
			}
			else if (Af[j] == 0)
			{
				while ((T1[i] != 0) && (i < (u + 16)))
					Am[am++] = T1[i++];
				break;
			}
			else if (T1[i] == Af[j])
			{
				Am[am++] = T1[i++];
				Am[am++] = T1[i++] + Af[++j];
				++j;
			}
			else if (T1[i] < Af[j])
			{
				Am[am++] = T1[i++];
				Am[am++] = T1[i++];
			}
			else
			{
				Am[am++] = Af[j++];
				Am[am++] = Af[j++];
			}
		}

		long long kl, jl;
		// get the squares
		for (i = 1, as = 1, is = 0; i < am; i += 2)
		{
			jl = Am[i] >> 1;
			if (jl)
			{
				Is[is++] = as;
				kl = Am[i - 1];
				As[as++] = kl;
				while (--jl)
				{
					As[as] = As[as - 1] * kl;
					++as;
				}
			}
		}
		Is[is] = as;
		mx0 = 1, mx1 = is, mx = is + 1;

		while (--is)
		{
			for (i = 0; i < is; i++)
			{
				for (j = Is[i]; j < Is[i + 1]; j++)
				{
					for (k = Is[mx0]; k < Is[mx1]; k++)
					{
						As[as++] = As[j] * As[k];
					}
				}
				++mx0;
				Is[mx++] = as;
			}
			++mx0;
			mx1 = mx - 1;
		}

		// count the triplets
		bbc = 2 * log((double)k1) + log((double)v);
		lminusa = (long long)(l - a);

		while (--as >= 0)
		{
			if (lminusa - As[as] <= 0)
				continue;

			double d1 = bbc - (2 * log((double)As[as]));
			double d2 = log((double)(lminusa - As[as]));

			if (d1 < d2 || fabs(d1 - d2) < 0.000000002)
				++cpt;
		}
	}
}

sieveFactorise()
{
	ULL l = 18333333, sl = sqrt(l), lastIdx;
	ULL i, j, k;
	ULL p, np, npi, mnp;
	for (i = 0, j = 1; j <= l; i += 16, j++)
		T1[i] = j;
	lastIdx = i - 16, T1[1] = 1;
	for (i = 16, p = 0; i <= lastIdx; i += 16)
	{
		if (p < T1[i])
		{
			p = T1[i], T1[i + 1] = 1;
			for (j = 2, np = 0;; j++)
			{
				np = p * j;
				if (np > l)
					break;
				npi = (np - 1) << 4;
				if (T1[npi] == np)
				{
					T1[npi] = p, T1[npi + 1] = 1;
				}
				else
				{
					for (k = npi + 16; npi <= k; npi += 2)
					{
						if (T1[npi] == p)
						{
							++T1[npi + 1];
							break;
						}
						else if (T1[npi] == 0)
						{
							T1[npi] = p, T1[npi + 1] = 1;
							break;
						}
					}
				}
			}
			if (p <= sl)
			{
				for (np = p * p; np <= l; np *= p)
				{
					for (j = 1, mnp = 0;; j++)
					{
						mnp = np * j;
						if (mnp > l)
							break;
						npi = (mnp - 1) << 4;
						for (k = npi + 16; npi <= k; npi += 2)
						{
							if (T1[npi] == p)
							{
								++T1[npi + 1];
								break;
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

factors(int n)
{
	int s = sqrt(n);
	int i, p, pi;
	int k = 0;
	for (i = 0, p = PRIMES[0]; p <= s; p = PRIMES[++i])
	{
		if (n % p == 0)
		{
			pi = 0;
			while (n % p == 0)
			{
				++pi;
				n /= p;
			}
			Af[k++] = p;
			Af[k++] = pi;
		}
		if (n == 1)
		{
			Af[k] = 0;
			return k;
		}
	}
	Af[k++] = n;
	Af[k++] = 1;
	Af[k] = 0;
	return k;
}

buildPrimesArray()
{
	int limit = 1000000;
	int i, j, k, l, s;
	l = (limit / 2) + 1;
	int *a = malloc(sizeof(int) * l);
	if (a == 0)
	{
		printf("build:malloc fail!");
		return 0;
	}
	for (j = 0, i = 3; i < limit; i += 2)
	{
		a[j++] = i;
	}
	s = sqrt(limit);
	for (i = 0; i <= s; i++)
	{
		if (a[i])
		{
			j = (a[i] * (i + 1)) + i;
			while (j < l)
			{
				a[j] = 0;
				j += a[i];
			}
		}
	}
	PRIMES[0] = 2;
	for (i = 0, j = 1; i < l; i++)
	{
		if (a[i])
		{
			PRIMES[j++] = a[i];
		}
	}
	free(a);
}
