#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

const int64_t MAXPRIME=6500000;
const int64_t CP=2549;
const int64_t MAXN=100000000000LL;
//const int64_t MAXN=3000000000LL; // 3*10^9 test value.  3*10^8 was confirmed correct

bitset<MAXPRIME+1> sieve;
vector<int64_t> primes,index;

int main()
{
    int64_t i,j,prod,active,sum5,sum6,sum7,sum8,result;
    primes.push_back(9); // Not really a prime, but like all our other primes, this multiple of 9 triples solutions
    sieve.set();
    for(i=4;i<=MAXPRIME;i+=2) sieve[i]=false;
    for(i=3;i<=CP;i+=2) if(sieve[i])
    {
        if(i%6==1) primes.push_back(i);
        for(j=i*i;j<=MAXPRIME;j+=i+i) sieve[j]=false;
    }
    for(i=CP+2;i<=MAXPRIME;i+=2) if(sieve[i]) if(i%6==1) primes.push_back(i);
    // 9 is out of numerical order: swap the first 2 elements
    i=primes[0];
    primes[0]=primes[1];
    primes[1]=i;
    i=0;
    prod=1;
    while(prod<MAXN)
    {
        prod*=primes[i];
        //cout << prod << endl;
        i++;
    }
    //cout << i-1 << endl;
    sum5=0;
    for(i=0;i<5;i++) index.push_back(i);
    active=4;
    do
    {
        prod=1;
        for(j=0;j<index.size();j++) prod*=primes[index[j]];
        if(prod>MAXN) active--;
        else
        {
            j=MAXN/prod; // Number of multiples of prod
            sum5+=j*(j+1)/2*prod;  // Sum the multiples
            // sum5+=MAXN/prod;
            active=4;
        }
        if(active>=0)
        {
            index[active]++;
            for(j=1;j+active<=4;j++) index[active+j]=index[active]+j;
        }
    } while(active>=0);
    //cout << "sum5 = " << sum5 << endl;
    sum6=0;
    index.clear();
    for(i=0;i<6;i++) index.push_back(i);
    active=5;
    do
    {
        prod=1;
        for(j=0;j<index.size();j++) prod*=primes[index[j]];
        if(prod>MAXN) active--;
        else
        {
            j=MAXN/prod;
            sum6+=j*(j+1)/2*prod;
            // sum6+=MAXN/prod;
            active=5;
        }
        if(active>=0)
        {
            index[active]++;
            for(j=1;j+active<=5;j++) index[active+j]=index[active]+j;
        }
    } while(active>=0);
    //cout << "sum6 = " << sum6 << endl;
    sum7=0;
    index.clear();
    for(i=0;i<7;i++) index.push_back(i);
    active=index.size()-1;
    do
    {
        prod=1;
        for(j=0;j<index.size();j++) prod*=primes[index[j]];
        if(prod>MAXN) active--;
        else
        {
            j=MAXN/prod;
            sum7+=j*(j+1)/2*prod;
            //sum7+=MAXN/prod;
            active=index.size()-1;
        }
        if(active>=0)
        {
            index[active]++;
            for(j=1;j+active<=index.size()-1;j++) index[active+j]=index[active]+j;
        }
    } while(active>=0);
    //cout << "sum7 = " << sum7 << endl;
    sum8=0;
    index.clear();
    for(i=0;i<8;i++) index.push_back(i);
    active=index.size()-1;
    do
    {
        prod=1;
        for(j=0;j<index.size();j++) prod*=primes[index[j]];
        if(prod>MAXN) active--;
        else
        {
            j=MAXN/prod;
            sum8+=j*(j+1)/2*prod;
            //sum8+=MAXN/prod;
            active=index.size()-1;
        }
        if(active>=0)
        {
            index[active]++;
            for(j=1;j+active<=index.size()-1;j++) index[active+j]=index[active]+j;
        }
    } while(active>=0);
    //cout << "sum8 = " << sum8 << endl;
    result=sum5-6*sum6+21*sum7-56*sum8;
    cout << result << endl;
    return 0;
}