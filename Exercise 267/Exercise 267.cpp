#include <iostream>
#include <math.h>
#include <iomanip>
#include <time.h>

using namespace std;

int MAX_LEVEL;

int maximize_win(double goal) {

    double K, maxK = 0;
    double f = 0.00001, maxf;

    while( f < 1.0 ) {
        K = ( (double(MAX_LEVEL)*log(1.0+2.0*f) - log(goal))/( log(1.0+2.0*f) - log(1.0-f) ) );

        if( K > maxK ) { maxK = K; maxf = f; }
        f += 0.00001;
   }

    cout << endl << "f = " << maxf << endl;

    return (int)maxK;
}

void toss(int K) {
       
	long double num = 0.0, den = 0.0, C = 1.0;
        for( int i = 0; i <= MAX_LEVEL; ++i ) {
            if( i <= K ) {
                num += C;
            }
            den += C;
	    C *= double(MAX_LEVEL - i);
	    C /= double(i+1);
        }
        cout << "Probability = " << setprecision(20) << num/den << endl;

        return;
}

int main() {

    double goal;
    cout << "How many coins tosses? " << endl;
    cin >> MAX_LEVEL;
    cout << "Goal? " << endl;
    cin >> goal;

    clock_t start = clock();

    toss( maximize_win(goal) );

    cout << "Time taken: " << setprecision(3) <<
    ((float)(clock()-start))/CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}