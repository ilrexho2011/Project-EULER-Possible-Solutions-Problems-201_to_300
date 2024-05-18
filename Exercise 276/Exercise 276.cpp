#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

typedef unsigned long long int ui64;

typedef vector<ui64> TNumbers;

static ui64 Count(ui64 a) {
    if (a & 1)
        return ((a + 3)*(a + 3) + 23)/48;
    else
        return (a*a + 23)/48;
}

int main() {
    static const int N = 10000000;

    TNumbers triangles(N + 1);
    for (int i = 1; i <= N; ++i) {
        triangles[i] = Count(i);
    }

    for (int i = 3; i <= N; ++i) {
        for (ui64 j = 2*i; j <= N; j += i) {
            triangles[j] -= triangles[i];
        }
    }

    ui64 sum = 0;
    for (ui64 i = 3; i <= N; ++i)
        sum += triangles[i];

    printf("%lld\n", sum);

    return 0;
}