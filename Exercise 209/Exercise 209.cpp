#pragma once

/*
*	Solves instantly for 6 inputs
*	Call: C_Problem209::Solve () ;
*	Output: Count: 15964587728784 (0ms)
*
*	Also solves instantly for 7 inputs:
*	Call: C_Problem209::Solve (7) ;
*	Output: Count: 4832970151116837148 (0ms)
*/

#define PROBLEM_209_MAX_INPUT_BITS		((unsigned int) 7)	// more than that overflows UInt64
#define PROBLEM_209_DEF_INPUT_BITS		((unsigned int) 6)
#define PROBLEM_209_MIN_INPUT_BITS		((unsigned int) 4)

typedef pair <__int64, pair <__int64, pair <__int64, __int64 > > > K_Problem209 ;
typedef 
	map <
		pair <__int64, 
			pair <__int64, 
				pair <__int64, __int64> 
			> 
		>, 
		__int64> M_Problem209 ;

class C_Problem209
{
protected :

	unsigned int m_NInputBits ;
	unsigned int m_NInputCombinations ;
	unsigned __int64 m_NTruthTables ;
	vector <unsigned int> m_SecondInputCombinations ;
	vector <unsigned int> m_CycleLengths ;
	vector <__int64> m_TotalPerCycle ;
	M_Problem209 m_Map ;

	C_Problem209 (unsigned int NInputBits)
	{
		m_NInputBits = 0 ;
		m_NInputCombinations = 0 ;
		m_NTruthTables = 0 ;

		if (NInputBits >= PROBLEM_209_MIN_INPUT_BITS && NInputBits <= PROBLEM_209_MAX_INPUT_BITS)
		{
			m_NInputBits = NInputBits ;
			m_NInputCombinations = (1 << NInputBits) ;
			m_NTruthTables = (unsigned __int64) 1 << (unsigned __int64) m_NInputCombinations ;

			unsigned int ABit = m_NInputCombinations >> 1 ;
			unsigned int BBit = ABit >> 1 ;
			unsigned int CBit = BBit >> 1 ;
			unsigned int ValidInputMask = m_NInputCombinations - 1 ;

			vector <bool> InCycle (m_NInputCombinations, false) ;

			m_SecondInputCombinations.resize (m_NInputCombinations) ;

			for (unsigned int iInputCombination = 0 ; iInputCombination < m_NInputCombinations ; iInputCombination ++)
			{
				if (! InCycle [iInputCombination])
				{
					unsigned int CycleElem = iInputCombination ;

					m_CycleLengths.push_back (0) ;
					m_TotalPerCycle.push_back (-1) ;

					do
					{
						InCycle [CycleElem] = true ;
						m_CycleLengths [m_CycleLengths.size () - 1] ++ ;

						unsigned int aBit = (CycleElem & ABit) != 0 ? 1 : 0 ;
						unsigned int bBit = (CycleElem & BBit) != 0 ? 1 : 0 ;
						unsigned int cBit = (CycleElem & CBit) != 0 ? 1 : 0 ;
						unsigned int AXorBAndC = aBit ^ (bBit & cBit) ;

						CycleElem = m_SecondInputCombinations [CycleElem] = ((CycleElem << 1) & ValidInputMask) | AXorBAndC ;
					}
					while (! InCycle [CycleElem]) ;
				}
			}
		}
	} ;

	bool CreatedOK () const
	{
		return m_NInputBits > 0 ;
	} ;

	__int64 DoCount (int CurrentCycle, int PositionInCycle, int FirstBitInCycle, int PrevBitInCycle)
	{
		__int64 RetVal = 0 ;

		if (PositionInCycle == m_CycleLengths [CurrentCycle])
		{
			if ((PrevBitInCycle & FirstBitInCycle) == 0)
			{
				if (CurrentCycle < m_CycleLengths.size () - 1)
				{
					if ((RetVal = m_TotalPerCycle [CurrentCycle + 1]) < 0)
					{
						RetVal = m_TotalPerCycle [CurrentCycle + 1] = DoCount (CurrentCycle + 1, 1, 0, 0) + DoCount (CurrentCycle + 1, 1, 1, 1) ;
					}
				}
				else
				{
					RetVal = 1 ;
				}
			}
		}
		else
		{
			K_Problem209 MapKey = make_pair (CurrentCycle, make_pair (PositionInCycle, make_pair (FirstBitInCycle, PrevBitInCycle))) ;
			M_Problem209 :: iterator it = m_Map.find (MapKey) ;

			if (it == m_Map.end ())
			{
				RetVal = DoCount (CurrentCycle, PositionInCycle + 1, FirstBitInCycle, 0) ;

				if (PrevBitInCycle == 0)
				{
					RetVal += DoCount (CurrentCycle, PositionInCycle + 1, FirstBitInCycle, 1) ;
				}
				m_Map.insert (make_pair (MapKey, RetVal)) ;
			}
			else
			{
				RetVal = it->second ;
			}
		}

		return RetVal ;
	} ;

public :

	static C_Problem209 * Create (unsigned int NInputBits)
	{
		C_Problem209 * RetVal = new C_Problem209 (NInputBits) ;

		if (RetVal)
		{
			if (! RetVal->CreatedOK ())
			{
				delete RetVal ;
				RetVal = NULL ;
			}
		}
		return RetVal ;
	} ;

	__int64 Count ()
	{
		return DoCount (0, 1, 0, 0) + DoCount (0, 1, 1, 1) ;
	} ;

	static void Solve (unsigned int NInputBits)
	{
		CString Str ;
		clock_t StartTime = clock () ;
		C_Problem209 * P209 = C_Problem209::Create (NInputBits) ;

		if (P209)
		{
			__int64 Count = P209->Count () ;
			clock_t TotalTime = clock () - StartTime ;

			Str.Format ("Count: %I64d (%ldms)", Count, TotalTime) ;
			delete P209 ;
		}
		else
		{
			Str = "Could not create problem 209 object" ;
		}
		AfxMessageBox (Str, MB_OK) ;
	} ;

	static void Solve ()
	{
#if 1
		unsigned int NInputBits = PROBLEM_209_DEF_INPUT_BITS ;
#else
		unsigned int NInputBits = PROBLEM_209_MAX_INPUT_BITS ;
#endif
		Solve (NInputBits) ;
	} ;
} ;