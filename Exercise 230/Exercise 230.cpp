#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
long long int A;
long long int B;
long long int array[1000];
long long int powsev(int x);

vector <long long int> findit(long long int A,long long int B,int id,long long int pos);
string aarr="1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
string barr="8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"; 
int main()
{
  A=100;
  B=100;
  array[1]=A;
  array[2]=B;
 
  for(int i=17;i>=0;i--)
    {
      long long finval=(127+19*i)*powsev(i);
       int ival=2;
       do
	 {
	   ival++;
	   array[ival]=array[ival-1]+array[ival-2];
	 }while(array[ival]<finval);
      vector <long long int> retval=findit(A,B,ival,finval);
      if(retval[0]==1)
	printf("%c",aarr[retval[1]-1]);
      else
	printf("%c",barr[retval[1]-1]);
    }
  printf("\n");
  
}

long long int powsev(int x)
{
  if(x==0)
    return 1;

  else
    return 7*powsev(x-1);
}

vector <long long int> findit(long long int A,long long int B,int id,long long int pos)
{
  if(id==1 || id==2)
    {
      vector <long long int> a;
      a.resize(2);
      a[0]=id;
      a[1]=pos;
      return a;
    }
  if(pos>array[id-2])
    {
      return findit(A,B,id-1,pos-array[id-2]);
    }
  else
    return findit(A,B,id-2,pos);
}
