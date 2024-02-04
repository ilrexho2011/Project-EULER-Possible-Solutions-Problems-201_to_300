#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <map>
using namespace std;

template<typename T> int size(const T& c) { return int(c.size()); }

typedef long long int64;

const int n = 40;
map<vector<int>,double> memo[n][n][(n+1)/2+1];

double solve(int L, int R, vector<int> M, int maxSoFar, int leftSpaces) {
	if (R < L) swap(L, R);
	sort(M.begin(), M.end());
	assert(M.empty() || M[0] > 0);
	maxSoFar = max(maxSoFar, size(M)+1);
	if (memo[L][R][maxSoFar].count(M))
		return memo[L][R][maxSoFar][M];
	static int cnt = 0;
	++cnt;
	if (cnt%1000 == 0)
		printf("size of cache: %d\n", cnt);
	double& res = memo[L][R][maxSoFar][M];
	if (leftSpaces == 0)
		return res = maxSoFar;
	for (int i = 0; i < L-1; ++i) {
		vector<int> M2 = M;
		M2.push_back(L-1-i);
		res += solve(i, R, M2, maxSoFar, leftSpaces-1);
	}
	if (L > 0)
		res += solve(L-1, R, M, maxSoFar, leftSpaces-1);
	for (int i = 0; i < R-1; ++i) {
		vector<int> M2 = M;
		M2.push_back(R-1-i);
		res += solve(L, i, M2, maxSoFar, leftSpaces-1);
	}
	if (R > 0) 
		res += solve(L, R-1, M, maxSoFar, leftSpaces-1);
	for (int i = 0; i < size(M); ++i) {
		for (int j = 0; j < M[i]; ++j) {
			vector<int> M2 = M;
			M2.erase(M2.begin()+i);
			if (j > 0) M2.push_back(j);
			if (M[i]-1-j > 0) M2.push_back(M[i]-1-j);
			res += solve(L, R, M2, maxSoFar, leftSpaces-1);
		}
	}
	return res;
}

int main() {
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += solve(i, n-1-i, vector<int>(), 1, n-1);
		printf("%d\n", i);
	}
	for (int i = 2; i <= n; ++i)
		sum /= i;
	printf("%.6lf\n", sum);
	exit(0);
}