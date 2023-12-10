#include <iostream>
#include <ctime>
using namespace std;

typedef unsigned long long ull;

bool isRightNumber( ull number );

int main()
{
  ull MIN = 1010101010;
  ull MAX = 1389026623;
  ull i;
  clock_t begin, end;
  
  begin = clock();	

  for( i = MIN; i < MAX; i+=10 ) {
    if( isRightNumber( i*i ) ) {
      cout << endl << i << "\t" << i*i << endl;
    }
  }
    
  end = clock();
  
  cout << end-begin << " clocks." << endl;
  cout << static_cast<double>(end-begin)/CLOCKS_PER_SEC << " seconds." << endl;
}

bool isRightNumber( ull number )
{
  bool isNumber = ( ( number % 10 ) == 0 );
  ull i;
  ull divisor = 10;

  for( i = 1; i < 10 && isNumber; i++ ) {
    number /= 100;
    isNumber = ( ( number % 10 ) == ( 10 - i ) );
  }
  
  return isNumber;		 
}