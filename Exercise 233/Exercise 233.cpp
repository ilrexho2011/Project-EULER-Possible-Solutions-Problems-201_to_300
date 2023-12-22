#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
#include <list>
using namespace std;
const uint64_t MAXPRIME=5000000;
const uint64_t CP=2235;
const uint64_t MAXN=100000000000;
const uint64_t LOG_MAXN=11;
bitset<MAXPRIME> sieve;
bitset<MAXPRIME> cvalues;
vector<uint64_t> pyth;
// Pythagorean primes congruent to 1 (mod 4)

uint64_t myPow(uint64_t base,uint64_t exp)
{
    uint64_t x;
    if(exp==0) return 1;
    if(exp==1)return base;
    x=myPow(base,exp/2);
    if(exp%2==1) return x*x*base;
    return x*x;
}

list<list<uint64_t> > genOrdFact(vector<uint64_t> factors) // generate ordered factorizations
{
    list<list<uint64_t> > ll1,ll2;
    if(factors.empty()) return ll1;  //  Shouldn't happen, but will return an empty list if there are no factors
    list<uint64_t>::iterator lit;
    list<list<uint64_t> >::iterator llit;
    list<uint64_t> l(1,factors.front());
    int i,j;
    ll1.push_back(l);
    for(i=1;i<factors.size();i++)
    {
        j=factors[i];
        for(llit=ll1.begin();llit!=ll1.end();llit++)
        {
            l.assign(llit->begin(),llit->end());
            l.push_back(j);
            ll2.push_back(l);
            l.pop_back();
            for(lit=l.begin();lit!=l.end();lit++)
            {
                l.insert(lit,j);
                ll2.push_back(l);
                lit--;
                lit=l.erase(lit);
                *lit*=j;
                ll2.push_back(l);
                *lit/=j;
            }
        }
        ll1.assign(ll2.begin(),ll2.end());
        ll2.clear();
    }
    return ll1;
}

uint64_t sumFactorization(vector<uint64_t> f)
{
    vector<long> index;
    long active,i;
    long double logb;
    uint64_t a,b,c,maxc,result;
    for(i=0;i<f.size();i++) index.push_back(i);
    active=0;
    result=0;
    while(index.back()<pyth.size())
    {
        logb=0;
        for(i=0;i<index.size();i++) logb+=f[i]*log10(pyth[index[i]]);
        while(logb>LOG_MAXN)
        {
            if(active==0) return result;
            active--;
            index[active]++;
            for(i=1;i<index.size()-active;i++) index[active+i]=index[active]+i;
            logb=0;
            for(i=0;i<index.size();i++) logb+=f[i]*log10(pyth[index[i]]);
        }
        b=1;
        for(i=0;i<index.size();i++) b*=myPow(pyth[index[i]],f[i]);
        maxc=MAXN/b;
        for(c=1;c<=maxc;c+=2)
        {
            if(!cvalues[c]) continue;
            a=floor(log10(maxc/c)/log10(2));
            result+=b*c*(myPow(2,a+1)-1);
        }
        active=index.size()-1;
        index[active]++;
    }
    index[index.size()-1]--;
    cout << "Ran out of pythagorean primes" << endl;
    cout << "b=";
    for(i=0;i<index.size();i++) cout << pyth[index[i]] << '^' << f[i] << '*';
    cout << endl;
    return 0;
}

int main()
{
    uint64_t i,j,sum;
    uint64_t pf[]={3,5,7};
    vector<uint64_t> pfv(pf,pf+sizeof(pf)/sizeof(uint64_t));
    vector<uint64_t> v;
    list<list<uint64_t> > factorizations=genOrdFact(pfv);
    list<list<uint64_t> >::iterator llit;
    list<uint64_t>::iterator lit;
    sieve.set();
    for(i=4;i<MAXPRIME;i+=2) sieve[i]=false;
    for(i=3;i<=CP;i+=2) if(sieve[i])
    {
        if(i%4==1) pyth.push_back(i);
        for(j=i*i;j<MAXPRIME;j+=i+i) sieve[j]=false;
    }
    for(i=CP+2;i<MAXPRIME;i+=2) if(sieve[i])
    {
        if(i%4==1) pyth.push_back(i);
    }
    cvalues.set();
    for(i=0;i<pyth.size();i++) for(j=pyth[i];j<MAXPRIME;j+=2*pyth[i]) cvalues[j]=false;
    sum=0;
    for(llit=factorizations.begin();llit!=factorizations.end();llit++)
    {
        v.clear();
        for(lit=llit->begin();lit!=llit->end();lit++) v.push_back(*lit/2);
        // Integer division, the numbers are necessarily odd.  Equivalent to (*lit-1)/2
        sum+=sumFactorization(v);
    }
    cout << sum << endl;
    return 0;
}