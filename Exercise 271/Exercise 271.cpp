#include<stdio.h>
#include<math.h>

long long int factors[100];
long long int remainders[14];

int factor(long long int i)
{
long long int j;
for (j=0;j<100;j++)
	{
	factors[j] = 1;
	}
j=0;
while (i%2 == 0)
	{
	factors[j] = factors[j]*2;
	i=i/2;
	}
if (factors[j]>1)
	{
	j++;
	}
long long int k;
for (k=3;k<=sqrt(i);k+=2)
	{
	if (i%k == 0)
	{
	while (i%k == 0)
	{
	factors[j] = factors[j]*k;
	i = i/k;
	}
	j++;
	}
	}
factors[j] = factors[j]*i;
return j;
}

long long int inverse(long long int i, long long int j)
{
long long int ii = i%j;
long long int l = 1;
while ((l*ii)%j != 1)
	{
	l = (l*ii)%j;
	}
return l;
}

long long int power(long long int j, long long int k)
{
long long int s = 1;
long long int l;
for (l=0;l<k;l++)
	{
	s = s*j;
	}
return s;
}

long long int product(long long int i, long long int j, long long int k)
{
long long int s = 0;
long long int l;
long long int d;
long long int p;
while (j>0)
	{
	p = i%k;
	d = 1;
	while (power(2,d) <= j)
		{
		p = (2*p)%k;
		d++;
		}
	j = j - power(2,d-1);
	s = (s+p)%k;
	}
return s;
}

long long int CRT(int i)
{
long long int j;
long long int r;
j = factors[0];
r = remainders[0];
int k;
for (k=1;k<i;k++)
	{
	//printf("%lld \n",inverse(factors[k],j));
	r = product(product(r,inverse(factors[k],j),factors[k]*j),factors[k],factors[k]*j) + product(product(remainders[k],inverse(j,factors[k]),factors[k]*j),j,factors[k]*j);
	j = j*factors[k];
	r = r%j;
	}
return r;
}

long long int order(long long int j, long long int k)
{
long long int s = 1;
long long int r = j;
while (r%k != 1)
	{
	r = (r*j)%k;
	s++;
	}
return s;
}

long long int primitiveroot(long long int p)
{
long long int l = 1;
while (order(l,p) < p-1)
	{
	l++;
	}
return l;
}

long long int powermod(long long int k, long long int j, long long int m)
{
long long int s = 1;
long long int i;
for (i=0;i<j;i++)
	{
	s = (s*k)%m;
	}
return s;
}

int main()
{
long long int kk;
long long int p;
long long int iii;
long long int s=0;
int indicies[6] = {3,5,7,10,11,13};
long long int l;
scanf("%lld",&l);
int k = factor(l);
long long int i;
for (i=0;i<=k;i++)
	{
	printf("%lld %lld \n",factors[i],primitiveroot(factors[i]));
	}
for (i=0;i<=k;i++)
	{
	remainders[i] = 1;
	}
for (i=0;i<729;i++)
{
long long int ii = i;
long long int index;
while (ii>0)
	{
	index = 1;
	while (power(3,index) <= ii)
		{
		index++;
		}
	p = factors[indicies[index-1]];
	kk = 0;
	while (ii>=power(3,index - 1))
		{
		ii = ii - power(3,index - 1);
		kk++;
		}
	remainders[indicies[index-1]] = powermod(primitiveroot(p),((p-1)*kk)/3,p);
	//printf("%lld %lld %lld \n",primitiveroot(p),kk,p);
	}
/*for (iii=0;iii<=k;iii++)
{
printf("%lld %lld \n",remainders[iii],factors[iii]);
}*/
printf("%lld %lld \n",i,CRT(k+1));
s = s+CRT(k+1);
for (iii=0;iii<=k;iii++)
	{
	remainders[iii] = 1;
	}
}
printf("%lld \n",s);
return 0;
}