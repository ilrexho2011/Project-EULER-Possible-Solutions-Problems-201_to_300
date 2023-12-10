#include<stdio.h>
#include<queue>
#define VALIDATE(_y, _x) (((_y)<n)&&((_x)<m)&&((_x)>=0)&&((_y)>=0))
using namespace std;

double res[30][30];
double div[30][30];
double bfs[2][30][30];
int n, m, r;
int mask[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
queue<int> Q;

void BFS(int y, int x) {
	while (!Q.empty())
		Q.pop();
	Q.push((y*30)+x);
	bfs[0][y][x] = 1;
	while (!Q.empty()) {
		int a = Q.front(), ay, ax, at;
		Q.pop();
		ax = a%30;
		a /= 30;
		ay = a%30;
		a /= 30;
		at = a;
		if (at==r) {
			res[ay][ax] *= (1-bfs[at%2][ay][ax]);
		} else			
			for (int i=0; i<4; i++)
				if (VALIDATE(ay+mask[i][0], ax+mask[i][1])) {
					if (bfs[(at+1)%2][ay+mask[i][0]][ax+mask[i][1]]==0)
						Q.push(((((at+1)*30)+ay+mask[i][0])*30)+ax+mask[i][1]);
					bfs[(at+1)%2][ay+mask[i][0]][ax+mask[i][1]] += bfs[at%2][ay][ax] / div[ay][ax];
				}
		bfs[at%2][ay][ax] = 0;
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &r);

	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
			res[i][j] = 1;

	for (int i=1; i<n-1; i++)
		for (int j=1; j<m-1; j++)
			div[i][j] = 4;

	for (int i=1; i<n-1; i++)
		div[0][i] = div[n-1][i] = div[i][0] = div[i][m-1] = 3;

	div[0][0] = div[n-1][m-1] = div[n-1][0] = div[0][m-1] = 2;

	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++) {
			BFS(i, j);
		}
	double tot = 0;
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
			tot += res[i][j];
	printf("%.10lf\n", tot);

	return 0;
}