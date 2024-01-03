#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

struct timer
{
   double t;
   timer() { t=clock(); }
   ~timer() { printf("runtime %.3f secs\n", get_time()); }
   double get_time() { return (clock()-t)/CLOCKS_PER_SEC; }
};
void f239()
{
   const int M=3, N=22, T=100;
   double pay=1, payda=1;
   int i = -1;
   while (++i < M)
      pay*=M+N-i, payda*=(i+1)*(T-i);
   double d=0;
   i = 0;
   while (++i <= N)
   {
      double pay=1, payda=1;
      int j = -1;
      while (++j < i)
         pay*=N-j, payda*=j+1;
      j = -1;
      while (++j < N-i)
         pay*=T-M-i-j;
      j = -1;
      while (++j < N)
         payda*=T-M-j;
      d += (i&1?1:-1)*(pay/payda);
   }
   printf("d=%.12f\n", (pay/payda)*(1-d));
}
int main(int argc, char**argv)
{
   timer t;
   f239();
   return 0;
}