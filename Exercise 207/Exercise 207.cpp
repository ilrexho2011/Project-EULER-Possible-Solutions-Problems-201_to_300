#include <iostream>

using namespace std;

int main()
{
    __int64 perfect = 0, total = 0, nextPowerOf2 = 2, num, i = 1;

    long double Val = (long double)1/12345;

    while (true)
    {
        num = i * (i + 1);
        total += 1;

        if (i + 1 == nextPowerOf2)
        {
            perfect++;
            nextPowerOf2 *= 2;
        }

        if (((long double)perfect/total) < Val)
        {
            cout << perfect << "/" << total << endl;
            break;
        }

        i++;
    }

    cout << num << endl;

    return 0;
}