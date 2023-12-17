#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <queue>

typedef __int64 int64;
struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};
struct xy
{
   double x,y;
   xy(double x, double y){this->x=x, this->y=y;}
   xy(const xy& r){this->x=r.x, this->y=r.y;}
};
double a=0;
double isinside(xy point)
{
   double xx=0.25-point.x; xx*=xx;
   double yy=0.5-point.y; yy*=yy;
   double rr=1.0/16;
   return xx+yy-rr; // outside if >0 or inside if <0
}
void fx(xy left, xy right, double incy)
{
   incy=incy/2;
   xy mid((left.x+right.x)/2, (left.y+right.y)/2+incy);
   //printf("(%.8f,%.8f) & (%.8f,%.8f) -> (%.8f,%.8f)\n",
   //   left.x,left.y,right.x,right.y,mid.x,mid.y);
   double ismidinside=isinside(mid);
   if (ismidinside>0)  // mid outside
   {
      fx(mid,right,incy);
   }
   else if (ismidinside<0) // mid inside
   {
      double dx=right.x-mid.x;
      double my=(right.y+mid.y)/2;
      a+=(my+incy/2)*dx;
      fx(left,mid,incy);
   }
   else // onside
   {
      double kak=(0.5-mid.y);
      double kok=(0.25-mid.x);
      double a123=(0.5-mid.x)/2;
      double a1=kok*kak/2;
      double a2=(2*asin(1)-atan(kak/kok))/32;
      double a3=a123-a1-a2;
      printf("found=%.8f\n",a-a3);
      return;
   }
}
int main(int argc, char**argv)
{
   timer t;
   fx(xy(0,0), xy(0.5,0.5),0.5);
   return 0;
}