#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

enum{LO=15000000,HI=20000000};
//enum{LO=15,HI=20};
typedef __int64 int64;
struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};
void fx()
{
   int* p=new int[HI+1];
   int i=-1;
   const int Low=HI-LO;
   while (++i<=Low)
      p[i]=i;
   --i;
   while (++i<=LO)
      p[i]=1;
   --i;
   while (++i<=HI)
      p[i]=i;
   bool* f = new bool [HI+1];
   f[0]=f[1]=0;
   i=1;
   while (++i<=HI)
      f[i]=1;

   int64 sum=0;
   i=1;
   while (++i<=HI)
   {
      if(f[i]==1)
      {
         int q=0;
         int j=i;
         if (p[j]>1)
            q+=j<=Low?-1:1, p[j]=1;
         while ((j+=i)<=HI)
         {
            f[j]=0;
            while (p[j]>1 && !(p[j]%i))
            {
               q+=j<=Low?-1:1;
               p[j]/=i;
            }
         }
         sum+=q*i;
      }
   }
   delete [] f;
   delete [] p;
   printf("sum=%I64d\n",sum);
}
int main(int argc, char**argv)
{
   timer t;
   fx();
   return 0;
}