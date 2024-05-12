#include <iostream>
#include <map>
#include <stdio.h>

#define SIEVE_RANGE (10000000)
#define PRIME_COUNT (664579)

bool sieve_visited[SIEVE_RANGE] = {};
std::map<int, int> aux_map;

void InitAuxMap()
{
    aux_map[1] = 9;
    aux_map[3] = 3;
    aux_map[7] = 7;
    aux_map[9] = 1;
}

long long GetDivisibilityMultiplier(long long p)
{
    if ((p % 2 == 0) || (p % 5 == 0))
    {
        return 0LL;
    }
    return (p * aux_map[p % 10] + 1) / 10;
}

void Solve()
{
    long long sum = 0;
    for (long long i = 2; i < SIEVE_RANGE; i++)
    {
        if (!sieve_visited[i])
        {
            sum += GetDivisibilityMultiplier(i);
            for (long long j = i + i; j < SIEVE_RANGE; j += i)
            {
                sieve_visited[j] = true;
            }
        }
    }
    std::cout << sum << std::endl;
}

int main(int argc, char* argv[])
{
    InitAuxMap();
    Solve();
    return 0;
}