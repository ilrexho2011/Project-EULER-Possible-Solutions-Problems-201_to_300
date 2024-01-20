#include <cstdint>
#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <utility>

typedef std::pair<uint32_t, uint16_t> pf_t;
typedef std::pair<uint64_t, uint64_t> pq_t;

void sieve_smallest_prime_factors(uint32_t n, std::vector<uint16_t>& pfs) {
  for (uint32_t i = 2; (i * i) <= n; ++i) {
    uint16_t pfs_i = pfs[i];
    if (pfs_i == 0) {
      for (uint32_t j = (i * i); j <= n; j = j + i) {
        uint16_t pfs_j = pfs[j];
        if (pfs_j == 0) {
          pfs[j] = i;
        }
      }
    }
  }
}

void pfs_from_sieve(std::vector<uint16_t> const& smallest_pfs, uint32_t n, std::map<uint32_t, uint16_t>& pfs) {
  pfs.clear();
  if (n == 0) {
    std::cerr << "pfs_from_sieve: n must be greater than 0." << std::endl;
    exit(EXIT_FAILURE);
  }
  if (n == 1) {
    return;
  }
  while (true) {
    uint32_t pf = smallest_pfs[n];
    if (pf == 0) {
      ++(pfs[n]);
      return;
    } else {
      ++(pfs[pf]);
    }
    n = n / pf;
  }
}

uint64_t binpow(uint64_t a, uint64_t b)
{
    uint64_t res = 1;
    while (b){
        if (b & 1) res = res * a;
        a = (a * a);
        b >>= 1;
    }
    return res;
}

pq_t perfection_quotient(std::map<uint32_t, uint16_t> const& pfs) {
  pq_t pq(1, 1);
  for (std::map<uint32_t, uint16_t>::const_iterator iter = pfs.begin();
       iter != pfs.end();
       ++iter) {
    uint64_t n = binpow(iter->first, iter->second + 1) - 1;
    n = n / (iter->first - 1);
    pq.first = pq.first * n;
    pq.second = pq.second * binpow(iter->first, iter->second);
  }
  return pq;
}

bool is_k_plus_half(uint64_t numerator, uint64_t denominator) {
  uint64_t g = std::__gcd(numerator, denominator);    
  uint64_t d = denominator / g;
  if (d == 2) {
    uint64_t n = numerator / g;
    return n & 1;
  }
  return false;
}

int main(int argc, char** argv) {
  uint32_t n = 200000000;
  std::vector<uint16_t> pfs(n + 1, 0);
  sieve_smallest_prime_factors(n, pfs);
  std::map<uint32_t, uint16_t> pf;
  for (uint32_t i = 2; i <= n; i = i + 2) {
    pfs_from_sieve(pfs, i, pf);
    pq_t pq = perfection_quotient(pf);
    if (is_k_plus_half(pq.first, pq.second)) {
      std::cout << i << " --> [" << pq.first << "," << pq.second << "] --> ";
      for (std::map<uint32_t, uint16_t>::const_iterator iter = pf.begin();
           iter != pf.end();
           ++iter) {
        std::cout << "(" << iter->first << "," << iter->second << ")";
      }
      std::cout << std::endl;
    }
  }
  return 0;
}
