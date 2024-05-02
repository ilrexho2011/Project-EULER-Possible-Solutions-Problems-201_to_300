#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

typedef __int64 int64;
typedef unsigned char uint8;
struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};

const int NH=21;
int primes[NH+NH]=
{
   2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,
   61,67,71,73,79,83,89,97,101,103,107,109,113,127,
   131,137,139,149,151,157,163,167,173,179,181
};
struct oran
{
   uint8 a[NH+1], b[NH+1];
   double f;
   oran(){}
   oran(int p)
   { this->a[this->a[0]=1]=p, this->b[0]=0, this->f=p; }
   oran(const oran& r)
   { memcpy(this, &r, sizeof(*this)); }
   oran operator *= (const int p)
   {
      this->a[++this->a[0]]=p;
      this->f*=p;
      return *this;
   }
   oran operator /= (const int p)
   {
      this->b[++this->b[0]]=p;
      this->f/=p;
      return *this;
   }
   operator double() const
   {
      return this->f>1? this->f:1/this->f;
   }
};
struct lessByOran : public std::binary_function<oran*, oran*, bool> 
{
   lessByOran() {}
   bool operator()(const oran* p1, const oran* p2) const
   {
      return (double)(*p1) < (double)(*p2);
   }
};

void f266()
{
   std::vector<oran> v1, v2;
   v1.reserve(1<<(NH-1));
   int i=-1;
   v1.push_back( oran(primes[++i]) );
   while (++i<NH)
   {
      int nt=v1.size();
      int j=-1;
      while (++j<nt)
      {
         v1.push_back( oran(v1[j])/=primes[i] );
         v1[j]*=primes[i];
      }
   }
   v2.reserve(1<<(NH-1));
   i=NH-1;
   v2.push_back( oran(primes[i+NH]) );
   while (--i>=0)
   {
      int nt=v2.size();
      int j=-1;
      while (++j<nt)
      {
         v2.push_back( oran(v2[j])/=primes[i+NH] );
         v2[j]*=primes[i+NH];
      }
   }
   int nt=v1.size()+v2.size();
   std::vector<oran*> pp;
   pp.reserve(nt);
   oran* pv1=&v1.front();
   oran* pv2=&v2.front();
   i=-1, nt=v1.size();
   while (++i<nt)
   {
      if (pv1[i].a[0]<9 || pv1[i].a[0]>NH-9)
         continue;
      pp.push_back(pv1+i);
   }
   i=-1, nt=v2.size();
   while (++i<nt)
   {
      if (pv2[i].a[0]<9 || pv2[i].a[0]>NH-9)
         continue;
      pp.push_back(pv2+i);
   }
   oran** ppp=&pp.front();
   nt=pp.size();
   std::sort(ppp, ppp+nt,lessByOran());
   double f_min=(*ppp[0]);
   oran* bestp1=0;
   oran* bestp2=0;
   i=-1;
   double d1=(*ppp[++i]),d2;
   while (++i, d2=d1, i<nt)
   {
      d1=(*ppp[i]);
      double d=d1>d2?d1/d2:d2/d1;
      if (d<f_min)
      {
         if ((ppp[i]>=pv1&&ppp[i-1]<pv2) ||
             (ppp[i]<pv2&&ppp[i-1]>=pv2)
            )
            f_min=d, bestp1=ppp[i], bestp2=ppp[i-1];
      }
   }
   {
      const int64 M=10000000000000000;
      int64 n=1;
      int j=0;
      while (++j<=bestp1->a[0])
      {
         printf("%d ", bestp1->a[j]);
         n=(n*bestp1->a[j])%M;
      }
      j=0;
      while (++j<=bestp2->b[0])
      {
         printf("%d ", bestp2->b[j]);
         n=(n*bestp2->b[j])%M;
      }
      printf("\nn1=%I64d\n",n);
      n=1;
      j=0;
      while (++j<=bestp1->b[0])
      {
         printf("%d ", bestp1->b[j]);
         n=(n*bestp1->b[j])%M;
      }
      j=0;
      while (++j<=bestp2->a[0])
      {
         printf("%d ", bestp2->a[j]);
         n=(n*bestp2->a[j])%M;
      }
      printf("\nn2=%I64d\n",n);
   }
}
int main(int argc, char**argv)
{
   timer t;
   f266();
   return 0;
}