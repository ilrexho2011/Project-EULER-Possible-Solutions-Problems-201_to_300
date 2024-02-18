#include <iostream>

using namespace std;

const int limit = 1000;

#define WIN		1
#define LOSS	2
#define UNKNOWN	0


char WC[limit + 1][limit + 1][limit + 1] = {UNKNOWN};

void MarkWinningPosition(int a,int b,int c)
{
	//case 1 (N stones from any single pile)

	for(int n = 1;a + n <= limit;n++)
		WC[a + n][b][c] = WIN;

	for(int n = 1;b + n <= limit;n++)
		WC[a][b + n][c] = WIN;

	for(int n = 1;c + n <= limit;n++)
		WC[a][b][c + n] = WIN;

	//case 2 (N stones from each of any two piles (2N total)

	for(int n = 1;n + a <= limit && n + b <= limit;n++)
		WC[a + n][b + n][c] = WIN;

	for(int n = 1;n + a <= limit && n + c <= limit;n++)
		WC[a + n][b][c + n] = WIN;

	for(int n = 1;n + b <= limit && n + c <= limit;n++)
		WC[a][b + n][c + n] = WIN;


	//case 3 (N stones from each of the three piles)

	for(int n = 1;n + a <= limit && n + b <= limit && n + c <= limit;n++)
		WC[a + n][b + n][c + n] = WIN;
}

bool WinningConfiguration(int a,int b,int c)
{
	if(WC[a][b][c] != UNKNOWN)
		return WC[a][b][c] == WIN;

	if(a+b+c == 0)
		return false;
	else
	{
		bool IWin = false;
		
		int max_n = a;

		if(b > max_n)
			max_n = b;

		if(c > max_n)
			max_n = c;

		//take N from one pile

		for(int n = 1;n <= max_n && !IWin;n++)
		{
			if(a >= n)
				IWin |= !WinningConfiguration(a-n,b,c);

			if(b >= n)
				IWin |= !WinningConfiguration(a,b-n,c);

			if(c >= n)
				IWin |= !WinningConfiguration(a,b,c-n);
		}
		
		//take N from two piles

		for(int n = 1;n <= max_n && !IWin;n++)
		{
			if(a >= n && b >= n)
				IWin |= !WinningConfiguration(a-n,b-n,c);

			if(b >= n && c >= n)
				IWin |= !WinningConfiguration(a,b-n,c-n);

			if(c >= n && a >= n)
				IWin |= !WinningConfiguration(a-n,b,c-n);
		}
		
		//take N from all piles

		for(int n = 1;n <= max_n && !IWin;n++)
			if(a >= n && b >= n && c >= n)
				IWin |= !WinningConfiguration(a-n,b-n,c-n);
		

		if(IWin)
		{
			WC[a][b][c] = WIN;
			WC[a][c][b] = WIN;
			WC[b][a][c] = WIN;
			WC[b][c][a] = WIN;
			WC[c][a][b] = WIN;
			WC[c][b][a] = WIN;
		}
		else
		{
			WC[a][b][c] = LOSS;
			WC[a][c][b] = LOSS;
			WC[b][a][c] = LOSS;
			WC[b][c][a] = LOSS;
			WC[c][a][b] = LOSS;
			WC[c][b][a] = LOSS;

			MarkWinningPosition(a,b,c);
			MarkWinningPosition(a,c,b);
			MarkWinningPosition(b,a,c);
			MarkWinningPosition(b,c,a);
			MarkWinningPosition(c,a,b);
			MarkWinningPosition(c,b,a);
		}

		return IWin;
	}
}

int main()
{
	unsigned long long answer = 0;

	for(int z = 0;z <= limit;z++) 
		for(int y = 0;y <= z;y++)
			for(int x = 0;x <= y;x++)
				if(WinningConfiguration(x,y,z) == false)
					answer += (x+y+z);
	
	cout << endl << "answer=" <<  answer << endl;
}