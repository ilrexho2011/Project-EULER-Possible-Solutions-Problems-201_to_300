#include <cstdio>

#include <algorithm>

const int N = 1000000000;
// const int N = 6;
long long int* table = new long long int[N + 1];

long long int F(int n, int x) {
    return table[x] - 3*x + table[n - x];
}

long long int DF(int n, int x) {
    return F(n, x + 1) - F(n, x);
}

int BinSearch(int n, int l, int r) {
    while (l < r) {
        int mid = (l + r) / 2;
        long long int midDF = DF(n, mid);
        if (midDF < 0)
            l = mid + 1;
        else if (midDF > 0)
            r = mid - 1;
        else
            return mid;
    }
    return l;
}

int main() {
    table[1] = 0;
    for (int n = 2; n <= N; ++n) {
        if (0 == n % 1000000)
            fprintf(stderr, "%d\n", n);
        int df0x = BinSearch(n, 1, n - 2);
        int l = std::max(1, df0x - 2);
        int r = std::min(n - 1, df0x + 2);
        long long int res = 1000000000000;
        for (int i = l; i <= r; ++i) {
            long long int iRes = F(n, i);
            if (iRes < res)
                res = iRes;
        }
        table[n] = res + 4*n;
    }
    printf("%lld\n", table[N] );
    return 0;
}