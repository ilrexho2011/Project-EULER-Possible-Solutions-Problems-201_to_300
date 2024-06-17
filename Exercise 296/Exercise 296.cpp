#include <iostream>
using namespace std;

int gcd(int a, int b) {
	int c=a%b;
	while (c>0) a=b,b=c,c=a%b;
	return b;
}

int min (int a, int b) { if (a<b) return a; else return b; }

//returns ceiling(a/b)
int ceil(int a, int b) { return (a-1)/b +1 }; 

int main () {
	int N= 1e5;

	int temp;
	long long tot=0;
	for (int A = 1; 2*A+1 <=N/5; A++) for (int B=A+1; A+B <= N/5; B++) if(gcd(B,A)==1) {
		for (int e = ceil(b,a);; e++) {
			temp= N/(A+B) - 2*e;
			if (temp<1) break;
			else tot+= min(temp,(e*A)/B);
		}
	}

	for (int e = 1;; e++) {
		temp=N/2 - 2*e;
		if (temp<1) break;
		else tot+=min(temp, e);
	}

	cout<<tot<<endl;
	return 0;
}