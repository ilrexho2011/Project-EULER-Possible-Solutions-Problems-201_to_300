#include<iostream>
#include<cmath>

using namespace std;
int main() {
    const int mo = 250;
    unsigned long long z = pow(10, 16);
    int k, j, r;
    int a[mo] = {}, b[mo] = {};
    unsigned long long sum[250] = {}, add[250] = {};
    for(k = 1; k <= 500; ++k) {
        r = 1;
        for(j = 1; j <= k; ++j)
            r = (r * k) % mo;
        a[r]++;
        if(k <= 250)
            b[r]++;
    }
    for(k = 0; k < mo; ++k)
        a[k] *= 500;
    for(k = 0; k < mo; ++k)
        a[k] += b[k];
    for(k = 0; k < mo; ++k)
        for(j = 1; j <= a[k]; ++j) {
            for(r = 0; r < mo; ++r)
                add[(r+k) % mo] = sum[r];
            for(r = 0; r < mo; ++r) {
                sum[r] += add[r];
                if(sum[r] >= z)
                    sum[r] -= z;
            }
            sum[k]++;
        }
    cout << sum[0] << endl;
}