#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <inttypes.h>

typedef unsigned int uint_t;

static const uint32_t Modulo = 20092010;
static const uint_t N = 2000;

uint32_t vecmul_cnt;

void vecmul(
	uint32_t dst[N], // can overlap sources
	const uint32_t a[N],
	const uint32_t b[N]
) {
	vecmul_cnt++;
//	fprintf(stderr, "vecmul %u \n", vecmul_cnt);
	static uint64_t tmp[N * 2];

	for (uint_t i = 0; i < N * 2; i++)
		tmp[i] = 0;

	for (uint_t i = 0; i < N; i++) {
		for (uint_t j = 0; j < N; j++) {
			tmp[i + j] += a[i] * (uint64_t) b[j];
		}
	}

	for (uint_t i = 0; i < N; i++) {
		tmp[i + 0] += tmp[i + 2000];
		tmp[i + 1] += tmp[i + 2000];
	}

	for (uint_t i = 0; i < N; i++)
		dst[i] = tmp[i] % Modulo;
}

void vecpow(
	uint32_t res[N],
	const uint32_t a[N],
	uint64_t n
) {
	static uint32_t b[N];
	for (uint_t i = 0; i < N; i++) {
		b[i] = a[i];
		res[i] = 0;
	}
	res[0] = 1 % Modulo;

	while (n > 0) {
		if (n & 1) {
			vecmul(res, res, b);
		}
		n >>= 1;
		if (n <= 0)
			break;
		vecmul(b, b, b);
	}
}


int main()
{
	vecmul_cnt = 0;
	static uint32_t a[N], r[N];
	uint64_t n = 1000000000000000000ULL;

	for (uint_t i = 0; i < N; i++) {
		a[i] = 0;
		r[i] = 0;
	}
	a[1] = 1 % Modulo;

	vecpow(r, a, n);
	printf("N=%u, Modulo=%u, n=%" PRIu64 " \n", N, Modulo, n);
	printf("vecmul_cnt=%u \n", vecmul_cnt);

	uint64_t res = 0;
	for (uint_t i = 0; i < N; i++)
			res += r[i];

	printf("res=%u \n", (uint_t) (res % Modulo));

	return 0;
}