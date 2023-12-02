#include <stdio.h>
#include <math.h>
void findit(long long int summ,int numbers,int prevnum);
int array[200];
int isthere;
int main()
{
  long long int i,summ;
  summ=0;
  for(i=42925;i<=300000;i++)
    {    
      isthere=0;
      findit(i,50,0);
      if(isthere==1)
	summ+=i;
    }
printf("=%lld\n",summ);
}

void findit(long long int summ,int numbers,int prevnum)
{
  if(isthere>1)
    return;
  if(prevnum+numbers>100)
    return;
  long long int headsum=((prevnum+numbers)*(prevnum+numbers+1)*(2*prevnum+2*numbers+1))/6-(prevnum*(prevnum+1)*(2*prevnum+1))/6;

  if(headsum>summ)
    return;
  //highest is 101-numbers to 100
  long long int tailsum=338350-((100-numbers)*(101-numbers)*(201-2*numbers))/6;

  if(tailsum<summ)
    return;
  
  if(numbers==0)
    {
      if(summ==0)
	  isthere++;
      return;
    }

  for(int h=prevnum+1;j<=100;j++)
    {
      array[51-numbers]=j;
      findit(summ-j*j,numbers-1,j);
    }
}