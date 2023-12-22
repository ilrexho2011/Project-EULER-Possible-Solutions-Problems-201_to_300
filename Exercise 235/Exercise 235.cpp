#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

double target = -600000000000.0;
double tolerance = 0.0000000000001;
int maxK = 5000;

double CalculateSum(double r)
//  Calculate sum for k = 1 to maxK of (900 - 3k)r^(k-1)
{
    double sum = 897;   // For every r, the first term of the sun
                        // is (900 - 2 * 1) * r ^ 0 = 897
    double power_of_r = 1.0;
    for (int k = 2; k <= maxK; k++)
    {
        power_of_r *= r;
        sum = sum + (900 - 3 * k) * power_of_r;
    }
    return sum;
}

int main()
{
    time_t t = clock();
    double lowerBound = 1.0;
    double upperBound = 2.0;
    double mid;
    double sum = 0;
    
    while (upperBound - lowerBound > tolerance)
    {
        mid = (lowerBound + upperBound) / 2;
        sum = CalculateSum(mid);
        if (sum > target)
        {
            lowerBound = mid;
        }
        else
        {
            upperBound = mid;
        }
    }
    cout << fixed << setprecision(12) << mid << endl;

    cout << double(clock() - t) / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}