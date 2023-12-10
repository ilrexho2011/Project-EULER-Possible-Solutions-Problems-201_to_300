#include <stdio.h>
#include <inttypes.h>
#include <math.h>

int n = 64000000;

int dividers[64000000];
int64_t cache[64000000];

void init_dividers(unsigned int n) {
    unsigned i,j;
    printf("Preparing dividers table ...\n");
    for (i=1;i<n;i++) dividers[i] = 0;
    i = 2;
    while (i<n) {
	for (j=i;j<n;j+=i) dividers[j] = i;
	while (dividers[i]) i++;
    }
    dividers[1] = 1;
}

int64_t sigma(unsigned int n) {
    if (cache[n]) return cache[n];
    unsigned int p = n;
    unsigned int a = dividers[p];
    unsigned int b = a;
    int64_t sum = 1;
    int64_t mul = 1;
    while (a == b) {
	mul *= a;
	mul *= a;
	sum += mul;
	p /= a;
	a = dividers[p];
    }
    return cache[n] = sigma(p) * sum;
}

bool is_square(int64_t n) {
    int64_t a = (int64_t)sqrt((double)n);
    return a*a==n;
}

int main() {
    init_dividers(n);
    printf("Clearing cache ...\n");
    for (int i=1;i<n;i++) cache[i] = 0;
    cache[1] = 1;
    unsigned int sum = 0;
    printf("Searching perfect squares ...\n");
    for (int i=1;i<n;i++) {
	if (i % 1000000 ==0) printf("%d\n", i);
	int64_t m = sigma(i);
	if (is_square(m)) sum += i;
    }
    printf("Result=%u\n", sum);
}