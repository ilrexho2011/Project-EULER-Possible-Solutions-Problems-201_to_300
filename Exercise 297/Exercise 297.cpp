#include<iostream>
#include<map>
using namespace std;

long long LIM = 99999999999999999LL;
long long fib[1000001] , z = 0;

map <long long , long long> F;

long long sum(long long n)
{
    if(n == 0)
        return 0;
    if(F.count(n))
        return F[n];
    for(int i = z ; i >= 1 ; i--)
        if(fib[i] <= n)
        {
            long long num = n - fib[i] + 1;
            F[n] = sum(fib[i] - 1) + sum(num - 1) + num;
            return F[n];
        }
}

int main()
{
    F.clear();
    long long a = 1 , b = 1 , c;
    while(b <= LIM)
    {
        fib[++z] = b;
        c = b;
        b = a + b;
        a = c;
    }
    cout<<sum(LIM)<<endl;
    return 0;
}