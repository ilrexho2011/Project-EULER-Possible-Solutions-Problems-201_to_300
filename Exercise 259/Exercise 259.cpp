#include <iostream>
#include <cmath>
#include <set>
#include <ctime>
using namespace std;
struct frac{
	long long num;
	long long den;
	bool operator < (const frac& other) const{
		return (num*other.den-den*other.num)*den*other.den<0;
	}
};

set<frac> a[10][10];
long long res=0LL;

long long gcd(long long a,long long b){
	if(b==0){
		return a;
	}else{
		return gcd(b,a%b);
	}
}

int main(){
	clock_t tbegin=clock();
	for(int i=1;i<=9;i++){
		frac tmp;
		tmp.num=i;
		tmp.den=1;
		a[i][i].insert(tmp);
	}
	for(int len=2;len<=9;len++){
		for(int ibegin=1;ibegin+len-1<=9;ibegin++){
			int iend=ibegin+len-1;
			long long dtmp=0;
			for(int i=ibegin;i<=iend;i++){
				dtmp*=10;
				dtmp+=i;
			}
			frac tmp;
			tmp.num=dtmp;
			tmp.den=1;
			a[ibegin][iend].insert(tmp);
			for(int imid=ibegin;imid<iend;imid++){
				set<frac> s1=a[ibegin][imid];
				set<frac> s2=a[imid+1][iend];
				for(set<frac>::iterator iter1=s1.begin();iter1!=s1.end();iter1++){
					for(set<frac>::iterator iter2=s2.begin();iter2!=s2.end();iter2++){
						frac tmp;
						tmp.den=(*iter1).den*(*iter2).den;
						tmp.num=(*iter1).num*(*iter2).den+(*iter1).den*(*iter2).num;
						a[ibegin][iend].insert(tmp);
						tmp.num=(*iter1).num*(*iter2).den-(*iter1).den*(*iter2).num;
						a[ibegin][iend].insert(tmp);
						tmp.num=(*iter1).num*(*iter2).num;
						a[ibegin][iend].insert(tmp);
						tmp.num=(*iter1).num*(*iter2).den;
						tmp.den=(*iter1).den*(*iter2).num;
						if(tmp.den!=0){
							a[ibegin][iend].insert(tmp);
						}
					}
				}
			}
		}
	}
	set<frac> s=a[1][9];
	set<long long> ss;
	for(set<frac>::iterator iter=s.begin();iter!=s.end();iter++){
		if((*iter).num*(*iter).den>0){
			long long num,den;
			num=(*iter).num;
			den=(*iter).den;
			if(a<0){
				num=-num;
				den=-den;
			}
			long long d=gcd(num,den);
			if(d==den){
				ss.insert(num/d);
			}
		}
	}
	for(set<long long>::iterator iter=ss.begin();iter!=ss.end();iter++){
		res+=*iter;
	}
	cout<<res<<endl;
	cout<<"elapse time is:"<<(clock()-tbegin)/1000<<"seconds"<<endl;
	return 0;
}