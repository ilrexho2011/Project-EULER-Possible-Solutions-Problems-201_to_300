#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#define N 30

const long long int MOD = 100000000;

vector<long long int> v(N+2,1);
vector< vector <long long int> > c1(N+2,v);


void initc(){
  for(int n=3;n<=2*N+2;n++){
    for(int i1=1; i1<n; i1++) {
      int i2=n-i1;
      if (i1>N+1 || i2>N+1 || i1==1 || i2==1) continue;
      c1[i1][i2]=(c1[i1-1][i2]+c1[i1][i2-1])%MOD;
    }
  }
}

int main(int argc, char *argv[])
{
  initc();

  long long int nr = 0;
  
//4x - 2 corner lines, next to each other, going into the opposite wall
{
  long long int lnr = 0;
  for(int i1=1;i1<=N-1;i1++) for(int i2=i1;i2<=N-1;i2++){
    long long int l1 = c1[N][i1];
    long long int l2 = c1[i2-i1+1][N-1];
    long long int l3 = c1[N][N-i2];
//cout<<i1<<","<<i2<<": ";
//cout<<l1<<","<<l2<<","<<l3<<endl;    
    lnr=(lnr+((l1*l2)%MOD*l3)%MOD)%MOD;
  }
  nr=(nr+lnr*4)%MOD;
cout<<"p1: 4x"<<lnr<<"="<<4*lnr<<endl;
}

//4x - 2 corner lines, opposite
{
  long long int lnr = 0;
  for(int i1=1;i1<=N-1;i1++) for(int i2=1;i2<=N-1;i2++){
    long long int l1 = c1[N][i1];
    long long int l2 = c1[N-i1][N-i2]; 
    long long int l3 = c1[N][i2];
    lnr=(lnr+((l1*l2)%MOD*l3)%MOD)%MOD;
  }
  nr=(nr+lnr*4)%MOD;
cout<<"p2: 4x"<<lnr<<"="<<4*lnr<<endl;
}

//2x - 2 corners 1 line
{
  long long int lnr = c1[N][N]*c1[N][N];
  nr=(nr+lnr*2)%MOD;
cout<<"p3: 2x"<<lnr<<"="<<2*lnr<<endl;
}

//8x - 1 corner line, non-symmetrical
{
  long long int lnr = 0;
  for(int i1=1;i1<=N-1;i1++) for(int i2=i1;i2<=N-1;i2++)
  for(int i3=1;i3<=N-1;i3++) for(int i4=1;i4<=N-1;i4++) {
    long long int l1 = c1[N][i1];
    long long int l2 = c1[N-i2][N-i3];
    long long int l3 = c1[N-i4][i3];
    long long int l4 = c1[i2-i1+1][i4];
    lnr=(lnr+(((l1*l2)%MOD*l3)%MOD*l4)%MOD)%MOD;
  }
  nr=(nr+lnr*8)%MOD;
cout<<"p4: 8x"<<lnr<<"="<<8*lnr<<endl;
}

//4x - 1 corner line, symmetrical
{
  long long int lnr = 0;
  for(int i1=1;i1<=N-1;i1++) for(int i2=1;i2<=N-1;i2++) {
    long long int l1 = c1[N][i1];
    long long int l2 = c1[N-i1][N-i2];
    long long int l3 = c1[N][i2];
    lnr=(lnr+((l1*l2)%MOD*l3)%MOD)%MOD;
  }
  nr=(nr+lnr*4)%MOD;
cout<<"p5: 4x"<<lnr<<"="<<4*lnr<<endl;
}

//2x - 0 corner line
{
  long long int lnr = 0;
  for(int i1=1;i1<=N-1;i1++) {
//cout<<i1<<endl;
    for(int i2=i1;i2<=N-1;i2++) {
//cout<<"  "<<i2<<endl;
      for(int i3=1;i3<=N-1;i3++) {
        for(int i5=1;i5<=N-1;i5++) {
          for(int i4=i5;i4<=N-1;i4++) {
            for(int i6=1;i6<=N-1;i6++) {
              long long int l1 = c1[N-i2][i3];
              long long int l2 = c1[N-i3][N-i4];
              long long int l3 = c1[i1][i6];
              long long int l4 = c1[i5][N-i6];
              long long int l5 = c1[i2-i1+1][i4-i5+1];
              lnr=(lnr+((((l1*l2)%MOD*l3)%MOD*l4)%MOD*l5)%MOD)%MOD;
  }}}}}}
  nr=(nr+lnr*2)%MOD;
cout<<"p6: 2x"<<lnr<<"="<<2*lnr<<endl;
}


  cout<<"Res.:"<<nr<<endl;

  system("PAUSE");
  return EXIT_SUCCESS;
}