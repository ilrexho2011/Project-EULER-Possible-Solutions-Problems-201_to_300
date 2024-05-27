#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100;
const int lim[30] = {0, 18, 10, 7, 6, 5, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
const ll LIM = 1e15, mo = 23333333333333333ll;

int cp, pr[N], eu[N]; bool nop[N]; ll ans;
void sieve () {
	eu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!nop[i]) pr[++cp] = i, eu[i] = i - 1;
		for (int j = 1; j <= cp && i * pr[j] < N; ++j) {
			nop[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				eu[i * pr[j]] = eu[i] * pr[j];
				break;
			} else eu[i * pr[j]] = eu[i] * eu[pr[j]];
		}
	}
}
ll slow_mul (ll a, ll b, ll ret = 0) {
	for ( ; b; b >>= 1) {
		if (b & 1) ret = (ret + a) % mo;
		a = a * 2 % mo;
	}
	return ret;
}
ll fast_pow (ll a, ll b, ll ret = 1) {
	for ( ; b; b >>= 1) {
		if (b & 1) ret = slow_mul(ret, a);
		a = slow_mul(a, a);
	}
	return ret;
}
ll inv (ll x) {
	return fast_pow(x, mo - 2);
}
ll fac (int n, ll ret = 1) {
	for (int i = 1; i <= n; ++i) ret = slow_mul(ret, i);
	return ret;
}
ll power (ll n, int k, ll ret = 1) {
	for (int i = 1; i <= k; ++i) ret = slow_mul(ret, n);
	return ret;
}
ll get (int m, int d) {
	return slow_mul(fac(m * d), inv(power(fac(d), m)));
}
ll calc (int m, int n, ll ret = 0) {
	for (int d = 1; d <= n; ++d) if (n % d == 0) {
		ll sgl = get(m, d);
		if (sgl / (m * n) > LIM) return 1e18;
		sgl *= eu[n / d];
		if (sgl / (m * n) > LIM) return 1e18;
		ret += sgl;
		if (ret / (m * n) > LIM) return 1e18;
	}
	ret = ret % mo;
	return slow_mul(ret, inv(n * m));
}
int main () {
	sieve(), ans = 0;
	for (int n = 1; n <= 29; ++n)
	for (int m = 2; m <= lim[n]; ++m) {
		ll tmp = calc(m, n);
		if (tmp <= LIM) ans += tmp;
	}
	cout << ans << endl;
	return 0;
}