#include <iostream>
#include <vector>

using namespace std;

vector<__int64> primes;
typedef vector<__int64>::iterator PrimeIterator;

bool is_prime(__int64 n);

int main(int argc, char** argv)
{	
    primes.reserve(78499);	
    primes.push_back(2);
    
    for (__int64 i = 3; i <= 1000003; i++)
    {
	if (is_prime(i))		
	    primes.push_back(i);																		
    }

    __int64 sum = 0;

    PrimeIterator it = primes.begin();
    PrimeIterator pre_end = primes.end();	
	
    pre_end--;
	
    while (it != pre_end)
    {		
	__int64 p1 = *it;
	__int64 p2 = *(it + 1);		

	bool is_finished_1 = false;		
	bool is_finished_2 = false;		

	__int64 p1_sqr = p1*p1;
	__int64 p2_sqr = p2*p2;

	__int64 g = p2_sqr/p1;

	for (__int64 k = p1 + 1; k <= g; k++)
	{
	    if (k % p2)
	    {
		if (k*p1 > 999966663333)
		{
		    is_finished_1 = true;
		    break;
	        }

		sum += k*p1;
	    }
	}

	for (__int64 k = p1_sqr/p2 + 1; k < p2; k++)
	{
	    if (k % p1)
	    {
		if (k*p2 > 999966663333)
		{
		    is_finished_2 = true;
		    break;
		}

		sum += k*p2;
	    }
        }

        if (is_finished_1 && is_finished_2)
	    break;

        ++it;
    }

    cout << "Answer: " << sum << "\n";

    return 0;
}

bool is_prime(__int64 n)
{
    if (n % 2 == 0)
        return false;

    PrimeIterator it = primes.begin();
    while (it != primes.end())
    {
        __int64 p = *it;
	if (p*p > n)
	    return true;

	if (n % p == 0)
	    return false;

	++it;
    }

    return true;
}