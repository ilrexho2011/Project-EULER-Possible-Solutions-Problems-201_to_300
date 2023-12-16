#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
#include <tuple>

#include "include/gcd.h"
#include "include/misc.h"
#include "include/types.h"

// Returns r >= start such that r*r = -1 mod c.
int128_t find_r( int128_t c, int128_t start)
{
    for( int128_t r = start; r < c; ++r)
        if( (r*r+1) % c == 0)
            return r;

    return -1;
}

// Returns p, q such that a*p + b*q = rhs. If possible, returns values for p
// and q that are both positive.
void find_p_q( int128_t a, int128_t b, int128_t rhs, int128_t& p, int128_t& q)
{
    int128_t pd, qd;
    int128_t d = extended_gcd( a, b, pd, qd);

    assert( rhs % d == 0);
    int128_t pr = rhs/d * pd;
    int128_t qr = rhs/d * qd;

    if( pr >= 0 && qr >= 0) {
        p = pr;
        q = qr;
    }

    if( pr < 0 && qr >= 0) {
        int128_t k = qr/a;
        q = qr - k*a;
        p = pr + k*b;
    }

    if( pr >= 0 && qr < 0) {
        int128_t k = pr/b;
        p = pr - k*b;
        q = qr + k*a;
    }
}

// Returns the smallest integer larger or equal to n/d.
int128_t lower_bound( int128_t n, int128_t d)
{
    assert( d > 0);
    if( n >= 0)
        return n/d + 1;
    else
        return -((-n)/d) + 1;

}

// Indicates whether a,b,c,p,q,r lead to a barely accute triangle.
bool is_valid(
    int128_t a, int128_t b, int128_t c,
    int128_t p, int128_t q, int128_t r)
{
    int128_t bound[5];
    bound[0] = lower_bound( p, a);
    bound[1] = lower_bound( q, b);
    bound[2] = lower_bound( r, c);
    bound[3] = lower_bound( p-r, c-a);
    bound[4] = lower_bound( q-r, c-b);
    int128_t t = *std::max_element( bound, bound+5);

    int128_t x = a*t + p;
    int128_t y = b*t + q;
    int128_t z = c*t + r;

    assert( x > 0);
    assert( y > 0);
    assert( z > 0);
    assert( x < z);
    assert( y < z);

    return x*x + y*y == z*z + 1;
}

// Generates all barely accute triangles on x = a*t + p, y = b*t + q, and z = c*t + r with
// x+y+z <= N.
void generate(
    int128_t a, int128_t b, int128_t c,
    int128_t p, int128_t q, int128_t r,
    int128_t N,
    std::set<std::tuple<int128_t,int128_t,int128_t> >& T)
{
    int128_t bound[5];
    bound[0] = lower_bound( p, a);
    bound[1] = lower_bound( q, b);
    bound[2] = lower_bound( r, c);
    bound[3] = lower_bound( p-r, c-a);
    bound[4] = lower_bound( q-r, c-b);
    int128_t t = *std::max_element( bound, bound+5);

    int128_t x = a*t + p;
    int128_t y = b*t + q;
    int128_t z = c*t + r;

    assert( x > 0);
    assert( y > 0);
    assert( z > 0);
    assert( x < z);
    assert( y < z);

    assert( x*x + y*y == z*z+1);

    while( true) {

        x = a*t + p;
        y = b*t + q;
        z = c*t + r;
        assert( x > 0);
        assert( y > 0);
        assert( z > 0);
        assert( x < z);
        assert( y < z);

        assert( x*x + y*y == z*z + 1);

        int128_t P = x+y+z;
        if( P > N)
            break;

        T.insert( { x<y ? x : y, x<y ? y : x, z} );
        ++t;
    }
}

int main( int /*argc*/, char* /*argv*/[])
{
    std::set<std::tuple<int128_t,int128_t,int128_t> > T;

    const long N = 25000000;
    const long M = sqrti( N/2);

    for( long m = 2; m <= M; ++m) {
        for( long n = m%2 + 1; n < m; n += 2) {

            if( gcd( m, n) > 1)
                continue;

            int128_t a = m*m - n*n;
            int128_t b = 2*m*n;
            int128_t c = m*m + n*n;

            int128_t start_r = 0;
            int128_t p, q, r;

            while( true) {

                r = find_r( c, start_r);
                if( r == -1)
                   break;
                start_r = r+1;
                assert( (r*r + 1) % c == 0);

                find_p_q( a, b, c*r, p, q);
                assert( a*p + b*q == c*r);

                if( p <= 0 || q <= 0)
                    continue;

                if( p >= a) {
                    while( p >= a) {
                        p -= b;
                        q += a;
                    }
                } else if( q >= b) {
                    while( q >= b) {
                        q -= a;
                        p += b;
                    }
                }
                assert( a*p + b*q == c*r);

                if( p >= a || q >= b)
                    continue;

                if( !is_valid( a, b, c, p, q, r))
                    continue;

                break;
            }

            if( r == -1) {
                assert( false);
                continue;
            }

            generate( a, b, c, p, q, r, N, T);
            generate( a, b, c, a-p, b-q, c-r, N, T);
        }
    }

    for( int128_t b = 1; b <= (N-1)/2; ++b)
        T.insert( { 1, b, b } );

    std::cout << T.size() << std::endl;
    assert( T.size() == 61614848);
    return EXIT_SUCCESS;
}