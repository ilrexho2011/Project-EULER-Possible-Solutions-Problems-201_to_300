#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main() {
    const int z = 5000;
    const unsigned long long mo = pow(10, 16);
    vector<bool> a(z+1, true);
    a[0] = a[1] = false;
    for(int k = 2; k <= floor(sqrt(z)); ++k)
        if(a[k])
            for(int s = 2; s <= z/k; ++s)
                a[k*s] = false;
    vector<int> prime;
    int ps = 0;
    for(int k = 1; k <= z; ++k)
        if(a[k]) {
            prime.push_back(k);
            ps += k;
        }
    int p, pps = 0, pi = prime.size();
    vector<unsigned long long> sum(ps+1, 0), add(ps+1, 0);
    for(int k = 0; k < pi; ++k) {
        p = prime[k];
        pps += p;
        for(int j = 1; j <= pps; ++j)
            add[j] = sum[j];
        for(int j = 1; j <= pps-p;  ++j) {
            sum[p+j] += add[j];
            if(sum[p+j] > mo)
                sum[p+j] -= mo;
        }
        sum[p]++;
    }
    vector<bool> aa(ps+1, true);
    aa[0] = aa[1] = false;
    for(int k = 0; k < pi; ++k)
        for(int s = 2; s <= ps/prime[k]; ++s)
            aa[prime[k]*s] = false;
    unsigned long long res = 0;
    for(int k = 1; k <= ps; ++k)
        if(aa[k]) {
            res += sum[k];
            if(res > mo)
                res -= mo;
        }
    cout << res << endl;
}