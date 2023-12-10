#include <stdio.h>
#include <stdlib.h>
#define N 3329  //number of lines
#define X (A/2) //max brick number
#define M 50	//max 48
#define A 32	//wall`s width
#define L 10	//wall`s height

int sub(int curt,int total,int lay);
bool crack(int x,int y);

int n=0,a[N][X+1]={0},b[N][M+1]={0};// a-line b-relationship

void main(void)
{ 
	long i,j,k;
	extern int n,a[N][X+1],b[N][M+1];
	__int64 sum=0,c[N][10]={0};

	printf("N=%d\n",sub(0,A,0));

	for(i=1;i<N;i++)
		for(j=0;!a[i][j];j++)
			a[i][j]=a[i-1][j];

	for(i=0;i<N;i++)
	{
		for(j=1;a[i][j]&&j<X;j++)
			if(a[i][j]+a[i][j-1]<A) a[i][j]+=a[i][j-1];
			else break;
		a[i][X]=j;
		for(;j<X-1;j++)
			a[i][j]=0;
	}
	
	for(i=0;i<N;i++)
		for(j=i+1;j<N;j++)
			if(!crack(i,j))
				b[i][b[i][M]++]=j,b[j][b[j][M]++]=i;

	for(j=0;j<N;j++)
		c[j][0]=1,c[j][1]=b[j][M];
	
	for(i=2;i<10;i++)
		for(j=0;j<N;j++)
			for(k=0;k<b[j][M];k++)
				c[j][i]+=c[b[j][k]][i-1];

	for(j=0;j<N;j++)
		sum+=c[j][9];

	printf("\nsum=%I64d\n",sum);


}

bool crack(int x,int y)
{
	extern int a[N][X+1];
	int i,j;
	for(i=0;i<X-1;i++)
		for(j=0;j<X-1;j++)
			if(a[x][i]==a[y][j]&&a[x][i]) 
				return 1;
	return 0;
}

int sub(int curt,int total,int lay)
{
	extern int n,a[N][X+1];
	if(curt==total) 
	{
		n++;
		return 1;
	}
	else if(curt>total) 
		return 0;

	int t1,t2;
	a[n][lay]=3;
	t1=sub(curt+3,total,lay+1);
	a[n][lay]=2;
	t2=sub(curt+2,total,lay+1);
	return t1+t2;
}