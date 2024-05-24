#include <iostream>
#include <cmath>

using namespace std;

int gcd( int x, int y )
{
    if ( y == 0 ) return x;
    return gcd( y, x % y );
}

int main()
{
    int u, uMod3, v, p0, pmax, n = 0;

    cout << "pmax = ? ";
    cin >> pmax;

    p0 = 0;

    for ( u = 2; p0 <= 2 * pmax; u ++ )
    {
        uMod3 = u % 3;

        if ( uMod3 == 0 )
        {
            u ++;
            uMod3 = u % 3;
        }

        for ( v = 3 - uMod3; 2 * v <= u; v += 3 )
        {
            if ( gcd( u, v ) == 1 )
            {
                p0 = ( u + v ) * ( 2 * u - v ) / 3;
                n += pmax / p0;
            }
        }
    }

    p0 = 0;

    for ( u = 3; p0 <= 2 * pmax; u ++ )
    {
        for ( v = 1; 2 * v < u; v ++ )
        {
            if ( gcd( u, v ) == 1 && ( u + v ) % 3 != 0 )
            {
                p0 = ( u + v ) * ( 2 * u - v );
                n += pmax / p0;
            }
        }
    }

    p0 = 0;

    for ( u = 2; p0 <= 2 * pmax; u ++ )
    {
        for ( v = 1 + u % 2; v < u; v += 2 )
        {
            if ( gcd( u, v ) == 1 )
            {
                p0 = 2 * u * ( u + v );
                n += pmax / p0;
            }
        }
    }

    p0 = 0;

    for ( u = 4; p0 <= 6 * pmax; u ++ )
    {
        uMod3 = u % 3;

        if ( uMod3 == 0 )
        {
            u ++;
            uMod3 = u % 3;
        }

        for ( v = uMod3; v < u; v += 3 )
        {
            if ( gcd( u, v ) == 1 )
            {
                p0 = ( u + v ) * ( 2 * u + v ) / 3;
                n += pmax / p0;
            }
        }
    }

    cout << "\nThe total number of integer-sided triangles with an integer angle (in degrees) and perimeter not exceeding " << pmax << " is "
        << n << ".\n";
    return 0;
}
