#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <vector>

typedef __int64 int64;
typedef unsigned int uint;
struct timer
{
   double t;
   timer() { t=clock(); }
   ~timer() { printf("runtime %.3f secs\n", (clock()-t)/CLOCKS_PER_SEC); }
};

enum{A=0,B=1,C=2,D=3,E=4};
int next[]={B,C,D,E,A}, prev[]={E,A,B,C,D};
//const int NC=5; //5=25/5
const int NC=14; //14=70/5
const int64 M=(NC<<16)+(NC<<12)+(NC<<8)+(NC<<4)+NC;
const int64 M5=M*5;
int64 pcnts[M5];
int64 sum=0;
struct circle
{
   uint pA:4, pB:4, pC:4, pD:4, pE:4;
   void update(int whence)
   {
      switch (whence)
      {
      case A: ++pA; break;
      case B: ++pB; break;
      case C: ++pC; break;
      case D: ++pD; break;
      case E: ++pE; break;
      };
   }
};
void f208(int whence=A, int c=0)
{
   circle* pc=(circle*)&c;
   if (pc->pA>NC || pc->pB>NC || pc->pC>NC || pc->pD>NC || pc->pE>NC)
      return;
   if (pc->pA==NC && pc->pB==NC && pc->pC==NC && pc->pD==NC && pc->pE==NC-1)
   {
      if (whence==E)
         ++sum;
      return;
   }
   int next_p=next[whence], prev_p=prev[whence];
   pc->update(whence);
   int inx=c*5+next_p;
   if (inx<M5)
   {
      if (pcnts[inx]>0)
         sum+=pcnts[inx]-1;
      else
      {
         int64 s=sum;
         f208(next_p, c);
         pcnts[inx]=sum+1-s;
      }
   }
   inx=c*5+prev_p;
   if (inx<M5)
   {
      if (pcnts[inx]>0)
         sum+=pcnts[inx]-1;
      else
      {
         int64 s=sum;
         f208(prev_p, c);
         pcnts[inx]=sum+1-s;
      }
   }
}
int main(int argc, char**argv)
{
   timer t;
   f208();
   printf("%I64d\n",2*sum);
   return 0;
}