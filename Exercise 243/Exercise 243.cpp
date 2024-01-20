#include <stdio.h>

long long int i=6,j=2,num=2,val=6,repeats=4,count=0;
long long int prime_vec[]={5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
double small,a,b,F=1.0;

int main()
{

printf("Enter a/b:");
scanf("%lf/%lf",&a,&b);
small=a/b;

while(F >= small)
{
a=j;
b=(i-1);
F=a/b;
if(F < small) printf("%lld/%lld\n",j,i-1);	

if(repeats==0) {
			num=j;
			val=val*prime_vec[count];          
			count++;
			repeats=prime_vec[count]-1;
		}
		repeats--;
		i+=val;
             if(repeats!=0) j+=num;
}
return 0;
}