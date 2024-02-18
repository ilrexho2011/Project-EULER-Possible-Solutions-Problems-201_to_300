#include <iostream>
using namespace std;

int gcd(int a, int b) {
	int c=a%b;
	while (c>0) a=b,b=c,c=a%b;
	return b;
}

int main () {
	int N=1e8;
	long long tot=0;

	for (long long q=2; q*q<N; q++) {
		for (long long p= (q%2)+1; 2*p<q; p+=2)  if(3*p>q) if (gcd(q,p)==1) {
			long long perim = q*(q+p);
			if (perim > N) break;
			tot+= N/ perim;
			
		}
	}

	for (long long q=2; q/2*q<N; q+=2) {
		for (long long p=1; 2*p<q; p++) if(4*p>q)  if( (p-q)%3 != 0) if(gcd(q,p)==1) {
			long long perim= q/2 * (q+2*p);
			if (perim> N) break;
			tot+=N/perim;
		}
	}

	for (long long q=1; q*q<N; q+=2) {
		for (long long p=1; 2*p<q; p++) if(4*p>q)  if( (p-q)%3 != 0) if(gcd(q,p)==1) {
			long long perim= q * (q+2*p);
			if (perim> N) break;
			tot+=N/perim;
		}
	}

	cout<<tot+N/3<<endl;

	return 0;
}