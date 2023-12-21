#define THE_RACE_GIVEN_POINTS_TO_WIN	100
#define THE_RACE_MIN_POINTS_TO_WIN		1

// to avoid overflowing the stack with recursive calls
#define THE_RACE_MAX_POINTS_TO_WIN		(THE_RACE_GIVEN_POINTS_TO_WIN * 75)

class C_TheRace
{
	int m_NPointsToWin, m_MaxTForNPointsToWin ;
	vector <vector <double>> m_P2WinProbabilities ;

	C_TheRace (int NPointsToWin)
	{
		if (NPointsToWin >= THE_RACE_MIN_POINTS_TO_WIN && NPointsToWin <= THE_RACE_MAX_POINTS_TO_WIN)
		{
			m_NPointsToWin = NPointsToWin ;
			m_MaxTForNPointsToWin = (int) ceil (log ((double) m_NPointsToWin)/ log (2.0)) + 1 ;

			vector <double> TempD (NPointsToWin + 1, -1.0) ;
			m_P2WinProbabilities.resize (NPointsToWin + 1, TempD) ;
		}
	} ;

	double CalcP2WinProbabilities (int P1Score, int P2Score)
	{
		double RetVal ;

		if ((RetVal = m_P2WinProbabilities [P1Score] [P2Score]) < 0.0)
		{
			if (P2Score >= m_NPointsToWin) { RetVal = 1.0 ; }
			else if (P1Score >= m_NPointsToWin) { RetVal = 0.0 ; }
			else
			{
				int NewP1ScoreWithWin = P1Score + 1 ;
				int P2NPointsToWin = m_NPointsToWin - P2Score ;

				RetVal = 0.0 ;

				for (int T = 1, N = 2 ; T <= m_MaxTForNPointsToWin ; T ++, N <<= 1)
				{
					int NMinusOne = N - 1 ;
					int PointsIfP2WinsBet = 1 << (T - 1) ;
					int NewP2ScoreWithWin = P2Score + PointsIfP2WinsBet ;
					
					if (NewP2ScoreWithWin > m_NPointsToWin) { NewP2ScoreWithWin = m_NPointsToWin ; }

					double InverseOfNPlusOne = 1.0 / (double) (N + 1) ;
					double BetOdds = InverseOfNPlusOne * (
						(double) NMinusOne * CalcP2WinProbabilities (NewP1ScoreWithWin, P2Score) +
						CalcP2WinProbabilities (P1Score, NewP2ScoreWithWin) +
						CalcP2WinProbabilities (NewP1ScoreWithWin, NewP2ScoreWithWin)) ;

					if (BetOdds > RetVal) { RetVal = BetOdds ; }
				}
			}
			m_P2WinProbabilities [P1Score] [P2Score] = RetVal ;
		}
		return RetVal ;
	} ;

	double CalcP2WinProbabilities ()
	{
		double p00 = CalcP2WinProbabilities (0, 0) ;
		return (p00 + m_P2WinProbabilities [1] [0]) * 0.5 ;
	} ;

public :

	static void SolveArbitraryProblem (int NPointsToWin)
	{
		CString Str ;

		if (NPointsToWin >= THE_RACE_MIN_POINTS_TO_WIN && NPointsToWin <= THE_RACE_MAX_POINTS_TO_WIN)
		{
			clock_t StartTime = clock () ;
			C_TheRace TheRace (NPointsToWin) ;
			double P2WinProbabilities = TheRace.CalcP2WinProbabilities () ;
			clock_t TotalTime = clock () - StartTime ;

			Str.Format ("P2's probability to race first to %d points is: %.8f (%ldms)", NPointsToWin, P2WinProbabilities, TotalTime) ;
		}
		else
		{
			Str.Format ("Invalid number of points to win: %d", NPointsToWin) ;
		}

		AfxMessageBox (Str, MB_OK) ;
	} ;

	static void SolveProblem232 ()
	{
		SolveArbitraryProblem (THE_RACE_GIVEN_POINTS_TO_WIN) ;
		//SolveArbitraryProblem (THE_RACE_MAX_POINTS_TO_WIN) ;
	} ;
} ;