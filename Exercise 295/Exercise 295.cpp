#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
using namespace std;

#define granica 10000000000ll
#define lint __int64

vector<lint> mat[150][500], pom;
lint niz[1304][3], g=0;

inline int gcd (int a, int b) { return (!b)? a: gcd(b, a%b); }

void init(){
    for (int p=1; p<150; p+=2)
        for (int q=p; q<500; q+=2){
            bool upis=0;
            if (gcd(p, q)!=1) continue;
            lint n=0, x=q*n+(q-p)/2, y=p*n+(q+p)/2, r=x*x+y*y;
            while(1){
                x=q*n+(q-p)/2, y=p*n+(q+p)/2, r=x*x+y*y;
                if (r>granica) break;
                bool b=1;
                for (int i=1; i<q; i++){
                    long double pp=(long double)p/q;
                    pp*=i;
                    int dx=(int)pp+1;
                    if ((x+dx)*(x+dx)+(y-i)*(y-i)<r) {b=0; break;}
                }
                if (r<=granica&&b&&y>=q) {
                    mat[p][q].push_back(r);
                    niz[g][0]=p, niz[g++][1]=q, upis=1;
                }
                if (upis){
                    while (r<=granica) {
                        n++;
                        x=q*n+(q-p)/2, y=p*n+(q+p)/2, r=x*x+y*y;
                        if (r>granica) break;
                        mat[p][q].push_back(r);
                    }
                    break;
                }
                n++;
            }
        }
    for (int p=0; p<g; p++) niz[p][2]=0;
}

int main() {
    init();
    lint suma=0;
    int prvi=0;
    for (int q=0;q<10000000;q++){
        if (q%10000==0) cout<<q<<" "<<suma<<endl;
        vector<int> pom, indeksi;
        lint min=10000000001ll;
        for (int p=0; p<g; p++) {
            if (niz[p][2]>=0){
                lint x=mat[niz[p][0]][niz[p][1]][niz[p][2]];
                if (min>x) min=x;
            }
        }
        if (min==10000000001ll) break;
        for (int p=0; p<g; p++) {
            if (niz[p][2]>=0){
                if (mat[niz[p][0]][niz[p][1]][niz[p][2]]==min) {
                    pom.push_back(p); indeksi.push_back(niz[p][2]);
                }
            }
        }

        if (pom.size()==1){
            lint x=mat[niz[pom[0]][0]][niz[pom[0]][1]].size();
            suma+=x-niz[pom[0]][2];
            if (++niz[pom[0]][2]==x) niz[pom[0]][2]=-1;
        }


        else{
            while(1){
                lint mini=10000000001ll;
                for (int i=0;i<pom.size();i++){
                    if (indeksi[i]>=0){
                        lint x=mat[niz[pom[i]][0]][niz[pom[i]][1]][indeksi[i]];
                        if (mini>x) mini=x;
                    }
                }
                if (mini==10000000001ll) break;
                suma++;
                for (int i=0;i<pom.size();i++){
                    if (indeksi[i]>=0&&mini==mat[niz[pom[i]][0]][niz[pom[i]][1]][indeksi[i]]){
                        lint x=mat[niz[pom[i]][0]][niz[pom[i]][1]].size();
                        if (++indeksi[i]==x) indeksi[i]=-1;
                    }
                }
            }
            for (int i=0;i<pom.size();i++){
                lint x=mat[niz[pom[i]][0]][niz[pom[i]][1]].size();
                if (++niz[pom[i]][2]==x) niz[pom[i]][2]=-1;
            }
        }
    }
    cout<<suma<<endl;
    return 0;
}
