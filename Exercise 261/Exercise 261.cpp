#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using int128_t  = __int128;

/// Generates primes up to n in primes using a sieve.
template <class T>
void generate_primes( T n, std::vector<T>& primes)
{
    T n_2 = (n-1) / 2;
    T n_4 = n/4;

    std::vector<bool> sieve( n_2+1, true);

    T k = static_cast<T>( floor( sqrt( static_cast<double>( n_4))));

    for( T i = 1; i <= k; ++i)
        // cppcheck-suppress arrayIndexThenCheck
        if( sieve[i] && i <= n_4/(i+1))
            for( T j = 2*i*(i+1); j <= n_2; j += 2*i+1)
                sieve[j] = false;

    primes.clear();
    primes.push_back( 2);
    for( T i = 1; i <= n_2; ++i)
        if( sieve[i])
            primes.push_back( 2*i+1);
}

/// Computes the prime factorization of n.
///
/// Prime factors are returned in \p factors with corresponding multiples in \p multiples.
template <class T>
void compute_prime_factorization(
    T n, const std::vector<T>& primes, std::vector<T>& factors, std::vector<T>& multiples)
{
    assert( n > 0);

    factors.clear();
    multiples.clear();

    size_t i = 0;
    T p( primes[i++]);

    while( p*p <= n) {

        if( n % p == 0) {

            T i = 1; // compute highest power of p that divides n, reduce n
            n /= p;
            while( n % p == 0) {
                ++i;
                n /= p;
            }

            factors.push_back( p);
            multiples.push_back( i);
        }

        if( i == primes.size())
            break;

        p = primes[i++];
    }

    // single prime as remaining factor
    if( n > 1) {
        assert( is_prime( n)); // check that primes was large enough
        factors.push_back( n);
        multiples.push_back( 1);
    }
}

/// Evaluates a factorization with given multiples.
template <class T>
T evaluate_factorization( const std::vector<T>& factors, const std::vector<T>& multiples)
{
    assert( factors.size() == multiples.size());

    T x( 1);
    for( size_t i = 0; i < factors.size(); ++i)
        for( size_t j = 0; j < static_cast<size_t>( multiples[i]); ++j)
            x *= factors[i];
    return x;
}

/// Returns the integer square root (rounded down).
///
/// Using double precision internally. Rounding errors which occur for example
/// for large values of type long are compensated with explicit searching for
/// the correct value. Suffix 'w' for while-loop.
template <class T>
T sqrtiw( T x)
{
    assert( x >= 0);

    T y( static_cast<T>( floor( sqrt( static_cast<double>( x)))));

    while( (y+1)*(y+1) <= x)
        ++y;
    while( y*y > x)
        --y;

    assert( y*y <= x);
    assert( (y+1)*(y+1) > x);

    return y;
}

/// Returns the smallest z >= x such that z % y == 0.
int128_t round_up( int128_t x, int128_t y)
{
    return (x + y-1) / y * y;
}

/// Returns the square-free part of a number, i.e., the product of the prime
/// factors that occur only once.
template <class T>
T compute_sqf( const std::vector<T>& factors, const std::vector<T>& multiples)
{
    assert( factors.size() == multiples.size());

    T x( 1);

    for( size_t i = 0; i < factors.size(); ++i)
        if( static_cast<size_t>( multiples[i]) % 2 == 1)
            x *= factors[i];

    return x;
}

/// Indicates whether the number contains a square, i.e., any multiples are
/// larger than 1.
template <class T>
bool contains_square( const std::vector<T>& multiples)
{
    for( const T& m: multiples)
        if( m >= 2)
            return true;
    return false;
}

int main( int /*argc*/, char* /*argv*/[])
{
    const long K = 1E10;

    const long P = sqrtiw( sqrtiw( K));
    std::vector<long> primes;
    generate_primes( P, primes);
    
    std::set<long> square_pivots;
    
    long m = 1;
    std::vector<long> factors, multiples;
    compute_prime_factorization( m, primes, factors, multiples);

    while( true) {
    
        // Store some properties of m
        bool m_contains_square = contains_square( multiples);
        long sqf = m_contains_square ? compute_sqf( factors, multiples) : 0;

        // Compute d such that k % d == 0 iff k*k % m == 0.
        for( auto& mu: multiples)
            mu = (mu + 1) / 2;
        long d = evaluate_factorization( factors, multiples);

        // Compute prime factorization of m+1
        compute_prime_factorization( m+1, primes, factors, multiples);
        bool mp1_contains_square = contains_square( multiples);

        // Compute lower bound between subsequent solutions
        bool special = m_contains_square && mp1_contains_square;
        double ratio = special ? 4 * sqrt( static_cast<double>( sqf)) : 4 * static_cast<double>( m) + 1;
        int128_t last_k = 0;

        int128_t k = 2*m*m + 2*m;
        if( k > K)
            break;

        while( k <= K) {

            assert( k*k % m == 0);

            int128_t D = (m+1) * (m+1) + 4 * (k*k + k*k/m) - 4 * (1+m)*k;
            int128_t r = sqrtiw( D);

            if( r*r == D) {
            
                square_pivots.insert( static_cast<long>( k));

                if( last_k > 0)
                    ratio = static_cast<double>( k) / static_cast<double>( last_k);
                last_k = k;
                k = ratio > 1 ? static_cast<int128_t>( floor( ratio * static_cast<double>( k))) : k+1;
                k = round_up( k, d);

            } else
                k += d;
        }

        ++m;
    }

    long sum = std::accumulate( square_pivots.begin(), square_pivots.end(), 0l);

    std::cout << sum << std::endl;
    assert( sum == 238890850232021l);
    return EXIT_SUCCESS;
}