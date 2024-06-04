# include <stdio.h>
# include <math.h>
# include <stdlib.h>

const int N(10);


typedef struct bigint//big integer
{
	int a[N];
	char n;
} BI;

void BIadd(BI i,BI j, BI *r)
{
	int k,m;
	if(i.n>j.n)
	{
		k=j.n;
		r->n=i.n;
		for(m=k;m<i.n;m++)
			r->a[m]=i.a[m];
	}
	else
	{
		k=i.n;
		r->n=j.n;
		for(m=k;m<j.n;m++)
			r->a[m]=j.a[m];
	}
	for(m=0;m<k;m++)
		r->a[m]=i.a[m]+j.a[m];
	for(k=0;k<r->n-1;k++)
	{
		if(r->a[k]>=10000)
		{
			r->a[k+1]+=r->a[k]/10000;
			r->a[k]%=10000;
		}
	}
	if(r->a[r->n-1]>=10000 && r->n>0)
	{
		r->a[r->n]=r->a[r->n-1]/10000;
		r->a[r->n-1]%=10000;
		r->n+=1;
	}
}

void BIsubt(BI i,BI j,BI *r)
{
	int k,m;
	for(k=0;k<j.n;k++)
	{
		if(i.a[k]>=j.a[k])
			i.a[k]-=j.a[k];
		else
		{
			i.a[k]+=10000-j.a[k];
			for(m=k+1;m<i.n;m++)
			{
				if(i.a[m]-1>=0)
				{
					i.a[m]-=1;
					break;
				}
				else
					i.a[m]=9999;
			}
			if(m==i.n-1 && i.a[m]==0)
				i.n-=1;
		}
	}
	for(k=0;k<i.n;k++)
		r->a[k]=i.a[k];
	r->n=i.n;
}


void BImult(BI i, int j, BI *r)
{
	int k;
	if(j==0)
	{
		r->a[0]=0;
		r->n=0;
		return;
	}
	for(k=0;k<i.n;k++)
		i.a[k]*=j;
	for(k=0;k<i.n-1;k++)
	{
		if(i.a[k]>=10000)
		{
			i.a[k+1]+=i.a[k]/10000;
			i.a[k]%=10000;
		}
	}
	if(i.a[i.n-1]>=10000 && i.n>0)
	{
		i.a[i.n]=i.a[i.n-1]/10000;
		i.a[i.n-1]%=10000;
		i.n+=1;
	}
	for(k=0;k<i.n;k++)
		r->a[k]=i.a[k];
	r->n=i.n;
}

void BIpow(BI *a, int n, BI *b)
{
	int i,j,k;
	BI c,d;
	if(n<0)
		return;
	if(n==0)
	{
		b->a[0]=1;
		b->n=1;
		return;
	}
	for(i=0;i<a->n;i++)
		c.a[i]=a->a[i];
	c.n=a->n;
	for(i=0;i<N;i++)
		d.a[i]=0;
	d.n=0;
	for(i=1;i<n;i++)
	{
		for(j=0;j<a->n;j++)
		{
			for(k=0;k<c.n;k++)
				d.a[k+j]+=c.a[k]*a->a[j];
			if(k+j>d.n)
				d.n=k+j;
			for(k=0;k<d.n-1;k++)
			{
				if(d.a[k]>=10000)
				{
					d.a[k+1]+=d.a[k]/10000;
					d.a[k]%=10000;
				}
			}
			if(d.a[d.n-1]>=10000)
			{
				d.a[d.n]=d.a[d.n-1]/10000;
				d.a[d.n-1]%=10000;
				d.n+=1;
			}
		}
		for(j=0;j<d.n;j++)
		{
			c.a[j]=d.a[j];
			d.a[j]=0;
		}
		c.n=d.n;
		d.n=0;
	}
	for(i=0;i<c.n;i++)
		b->a[i]=c.a[i];
	b->n=c.n;
}

int BImod(BI i, int j)
{
	int k,r=0;
	for(k=i.n-1;k>=0;k--)
	{
		r=(r*10000+i.a[k])%j;
	}
	return r;
}

void BImod(BI i, BI j, BI *r)
{
	int k,m;
	for(;;)
	{
		if(i.a[i.n-1]==0)
			i.n-=1;
		else
			break;
	}
	for(;;)
	{
		if(i.n>j.n)
		{
			for(k=0;k<j.n;k++)
			{
				if(i.a[k+i.n-1-j.n]>=j.a[k])
					i.a[k+i.n-1-j.n]-=j.a[k];
				else
				{
					i.a[k+i.n-1-j.n]+=10000-j.a[k];
					for(m=k+1;m+i.n-1-j.n<i.n;m++)
					{
						if(i.a[m+i.n-1-j.n]-1>=0)
						{
							i.a[m+i.n-1-j.n]-=1;
							break;
						}
						else
							i.a[m+i.n-1-j.n]=9999;
					}
				}
			}
			for(;;)
			{
				if(i.a[i.n-1]==0)
					i.n-=1;
				else
					break;
			}
			// Sorry I changed my mind
			/*for(k=0;k<j.n;k++)
			{
				if(i.a[k]>=j.a[k])
					i.a[k]-=j.a[k];
				else
				{
					i.a[k]+=10000-j.a[k];
					for(m=k+1;m<i.n;m++)
					{
						if(i.a[m]-1>=0)
						{
							i.a[m]-=1;
							break;
						}
						else
							i.a[m]=9999;
					}
					if(m==i.n-1 && i.a[m]==0)
						i.n-=1;
				}
			}*/
		}
		else
		{
			if(i.n==j.n)
			{
				for(k=i.n-1;k>=0;k--)
					if(i.a[k]!=j.a[k])
						break;
				if(i.a[k]<j.a[k])
					break;
				else
				{
					i.n=k+1;
					for(k=0;k<i.n;k++)
					{
						if(i.a[k]>=j.a[k])
							i.a[k]-=j.a[k];
						else
						{
							i.a[k]+=10000-j.a[k];
							for(m=k+1;m<i.n;m++)
							{
								if(i.a[m]-1>=0)
								{
									i.a[m]-=1;
									break;
								}
								else
									i.a[m]=9999;
							}
						}
						if(m==i.n-1 && i.a[m]==0)
							i.n-=1;
					}
				}
			}
			else
				break;
		}
	}
	for(k=0;k<i.n;k++)
		r->a[k]=i.a[k];
	r->n=i.n;
}

void BIeval(BI *r, BI i)
{
	int k;
	for(k=0;k<i.n;k++)
		r->a[k]=i.a[k];
	r->n=i.n;
}

void BIprintf(BI *a)
{
	int i;
	if(a->n==0)
	{
		printf("zore\n");
		return;
	}
	printf("%d",a->a[a->n-1]);
	for(i=a->n-2;i>=0;i--)
		printf("%04d",a->a[i]);
	printf("\n");
}

int main()
{
	int i,j,k,p=61,m=10,n=10000000,*tn;
	BI s0,sn,sd,pm,r,r1,r2,zero,*pn;
	while((tn=(int *)malloc(sizeof(int)*m))==NULL);
	while((pn=(BI *)malloc(sizeof(BI)*m))==NULL);
	zero.a[0]=0;
	zero.n=0;
	BIeval(&r,zero);
	BIeval(&r1,zero);
	s0.a[0]=797;
	s0.a[1]=29;
	s0.n=2;
	sd.a[0]=5093;
	sd.a[1]=5051;
	sd.n=2;
	for(i=0,j=p;j!=0;i++)
	{
		pm.a[i]=j%10000;
		j/=10000;
	}
	pm.n=i;
	for(i=0;i<m;i++)
	{
		BIpow(&pm,i,pn+i);
		BIprintf(pn+i);
	}
	BIpow(&pm,m,&pm);
	printf("%f\n",pow(p,m));
	BIprintf(&pm);
	tn[0]=BImod(s0,p);
	for(i=1;i<m;i++)
	{
		BIpow(&s0,2,&s0);
		BIprintf(&s0);
		BImod(s0,sd,&sn);
		BIprintf(&sn);
		tn[i]=BImod(sn,p);
		BIeval(&s0,sn);
		//BIprintf(&s0);
		printf("%d\n",tn[i]);
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<m-1;j++)
		{
			tn[j]=tn[j+1];
			//printf("- %d\n",tn[j]);
		}
		BIpow(&s0,2,&s0);
		BImod(s0,sd,&sn);
		tn[m-1]=BImod(sn,p);
		BIeval(&s0,sn);
		BIeval(&r1,zero);
		for(j=0;j<m;j++)
		{
			if(i+j>=n)
				break;
			BImult(pn[j],tn[j],&r2);
			//printf("*%d \n",tn[j]);
			//BIprintf(pn+j);
			//BIprintf(&r2);
			//BIprintf(&r1);
			BIadd(r1,r2,&r1);
			//BIprintf(&r1);
			BImod(r1,pm,&r1);
			//BIprintf(&r1);
		}
		BIadd(r,r1,&r);
		//BIprintf(&r);
		BImod(r,pm,&r);
		if((i+1)%10000==0)
		{
			printf("%5d ",i+1);
			BIprintf(&r);
		}
	}
	BIprintf(&r);
	return 0;
}