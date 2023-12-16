#include <iostream>
using namespace std ;

int main()
{
	int d = 27 ;
	int z = 0 ;
	
	int Tnm1 = 1, Tnm2 = 1, Tnm3 = 1 ;
	for ( int n = 4 ;  z < 124 ;  ++n )
	{
		int Tn_neu = ( Tnm1 + Tnm2 + Tnm3 ) % d ;
		Tnm3 = Tnm2 ;
		Tnm2 = Tnm1 ;
		Tnm1 = Tn_neu ;

		if ( Tn_neu == 0 )
		{
			d += 2 ;
			n = 3 ;
			Tnm1 = Tnm2 = Tnm3 = 1 ;
			continue ;
		}

		if ( Tnm1 == Tnm2 && Tnm2 == Tnm3 )
		{
			++z ;

			if ( z == 124 )
				cout << d << " is the solution. " << endl ;

			d += 2 ;
			n = 3 ;
			Tnm1 = Tnm2 = Tnm3 = 1 ;
			continue ;
		}
	}


	return 0 ;
}