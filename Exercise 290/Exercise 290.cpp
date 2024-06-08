#include <iostream>
#include <Windows.h>
using namespace std;

typedef long long LLT;

#define UN(i) ((i)%10)
#define TN(i) ((i)/10)

LLT memo[19][360][4][10][10];

LLT solveMemo(LLT dl, LLT n, LLT sd, LLT c, LLT p1, LLT p2)
{
	LLT &m = memo[n][sd+180][c][p1][p2];
	if ( m != -1 )
		return m;

	LLT sc = 0;
	if (n == dl)
	{
		// We're out of digits in n but need to finish off the multiplication
		LLT nd0 = TN(7*p1) + UN(3*p1)+TN(3*p2)+UN(p2)+c;
		LLT nd1 = TN(3*p1)+p1+TN(nd0);
		sd += UN(nd0)+UN(nd1)+TN(nd1);
		m = sd == 0 ? 1 : 0;
		return m;
	}	
	
	// Try each possible digit on the left hand end of this one.
	// Update our running digit sums
	for(int i=0; i<=9; ++i)
	{
		LLT nd0  = UN(7*i)+TN(7*p1) + UN(3*p1)+TN(3*p2) + UN(p2) + c;
		LLT ndd = UN(nd0);
		sc += solveMemo(dl, n+1, sd+ndd-i, TN(nd0), i, p1);
	}

	m = sc;
	return sc;
}

int main()
{
	LLT startTime = GetTickCount();
	memset(memo,-1,sizeof(memo));
	LLT answer = solveMemo(18,0,0,0,0,0);
	LLT runTime = GetTickCount() - startTime;
	cout << "Answer=" << answer << " in " << runTime << " ms" << endl;
}