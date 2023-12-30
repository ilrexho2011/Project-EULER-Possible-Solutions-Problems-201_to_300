#include <algorithm>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

uint64_t
gcd ( uint64_t a, uint64_t b )
{
  uint64_t c;
  while ( a != 0 ) {
     c = a; a = b%a;  b = c;
  }
  return b;
}

struct sort_frac {
    bool operator()(const pair<uint64_t,uint64_t> &left, const pair<uint64_t,uint64_t> &right)
    {
        return (double) left.first / (double) left.second > (double) right.first / (double) right.second;
    }
};

int main()
{
  vector<uint64_t> A = {5248, 1312, 2624, 5760, 3936, };
  vector<uint64_t> B = { 640, 1888, 3776, 3776, 5664, };

  uint64_t sum_A = 0ULL, sum_B = 0ULL;

  for(uint32_t i = 0; i < A.size(); i++)
  {
    sum_A += A[i];
    sum_B += B[i];
  }

  vector<pair<uint64_t,uint64_t> > m;

  // Forming up the initial candidates of m based on the product
  // Beluga Caviar
  for(uint64_t b = 0; b <= B[0]; b++)
    for(uint64_t a = 1; a <= A[0]; a++)
      if(b * A[0] > a * B[0])
      {
        uint64_t frac_gcd = gcd(b * A[0], a * B[0]);

        m.push_back(pair<uint64_t,uint64_t>(b * A[0] / frac_gcd, a * B[0] / frac_gcd));
      }

  sort(m.begin(), m.end());
  vector<pair<uint64_t,uint64_t> >::iterator it = unique(m.begin(), m.end());
  m.resize(it - m.begin());

  // Christmas Cake to Champagne Truffles
  for(uint32_t product_index = 1; product_index < A.size(); product_index++)
  {
    vector<pair<uint64_t,uint64_t> > curr_m;

    for(uint64_t b = 0; b <= B[product_index]; b++)
      for(uint64_t a = 1; a <= A[product_index]; a++)
        if(b * A[product_index] > a * B[product_index])
        {
          uint64_t frac_gcd = gcd(b * A[product_index], a * B[product_index]);

          curr_m.push_back(pair<uint64_t,uint64_t>(b * A[product_index] / frac_gcd, a * B[product_index] / frac_gcd));
        }

    sort(curr_m.begin(), curr_m.end());
    vector<pair<uint64_t,uint64_t> >::iterator it = unique(curr_m.begin(), curr_m.end());
    m.resize(distance(curr_m.begin(), it));

    vector<pair<uint64_t,uint64_t> > next_m(min(m.size(), curr_m.size()));

    it = set_intersection(curr_m.begin(), curr_m.end(), m.begin(), m.end(), next_m.begin());
    next_m.resize(it - next_m.begin());

    m = next_m;
  }

  sort(m.begin(), m.end(), sort_frac());

  for(uint32_t i = 0; i < m.size(); i++)
    printf("%llu/%llu\n", m[i].first, m[i].second);

  return 0;
}