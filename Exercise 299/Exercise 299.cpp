#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
using namespace std;

int main () {
	double startt=clock();
	int N=1e8;
	
	int n=1e4;
	bool * p; p=(bool*) calloc(n,sizeof(bool));
	p[0]=1,p[1]=1;
	for (int i=4; i<n; i+=2) p[i]=1;
	for (int i=3; i*i<n; i+=2) if(!p[i]) {
		for (int j=i*i; j<n; j+=2*i) p[j]=1;
	}
	
	bool* sqf; sqf=(bool*) calloc(N/7 +1, sizeof(bool));
	for (int i=4; i<=N/7; i+=4) sqf[i]=1;
	for (int i=3; i*i<=N/7; i+=2) if(!p[i]) {
		for (int j=i*i; j<=N/7; j+=i*i) sqf[j]=1;
	}

	int* things; things=(int*) calloc(N,sizeof(int));

	int temp;
	for (int t=1; 2*t*(t+2)+1<N; t++) for (int r=1;;r++) {
		temp=2*t*t+4*t*r+r*r;
		if(temp>=N) break;
		things[temp]++;
	}
	
	for (int i=1; i<N; i++) things[i]+=things[i-1];// cout<<i<<" "<<things[i]<<endl;
		
	long long totall=0;
	
	for (int s=1; 7*s<N; s+=2) if(!sqf[s])  totall+=2*things[(N-1)/s];
	
	int* things1; things1=(int*)calloc(N,sizeof(int));
	for (int t=1; 4*t*(t+1)+2<N; t++) for (int r=1;;r++) {
		temp=2*(2*t*t+2*t*r+r*r);
		if(temp>=N) break;
		things1[temp]++;
	}
	
	for (int i=1; i<N; i++) things1[i]+=things1[i-1];
	for (int s=1; 10*s <N; s+=2) if(!sqf[s]) totall+=things1[(N-1)/s];

	cout<<totall<<endl;
	
	return 0;
}