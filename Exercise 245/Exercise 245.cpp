#include <cstdint>
#include <iostream>
#include <vector>

#include "math_utils.h"
#include "sieve.h"

void sieve_odd_sqr_free_tnts(uint64_t sqrt_n,
                            std::vector<uint64_t> const& prms,
                            std::vector<uint64_t>& orig,
                            std::vector<uint64_t>& tnts) {
  auto a { orig[0U] };
  auto sv_size = orig.size();
  for (auto p : prms) {
    if (p > sqrt_n) {
      break;
    } else {
      auto x = a % p;
      auto i = (x == 0ULL) ? 0ULL : (p - x);
      while (i < sv_size) {
        if (tnts[i] > 0ULL) {
          orig[i] = orig[i] / p;
          if ((orig[i] % p) == 0ULL) {
            tnts[i] = 0ULL;
          } else {
            tnts[i] = tnts[i] * (p - 1ULL);
          }
        }
        i = i + p;
      }
    }
  }
  for (auto i = 0ULL; i < sv_size; ++i) {
    if ((tnts[i] > 0ULL) && (orig[i] > 1ULL)) {
      tnts[i] = tnts[i] * (orig[i] - 1ULL);
    }
  }
}

void init_orig_tnts(uint64_t start,
                    uint64_t segment_size,
                    std::vector<uint64_t>& orig,
                    std::vector<uint64_t>& tnts) {
  bool is_even { (start % 2ULL) == 0ULL };
  for (auto j = 0ULL; j < segment_size; ++j) {
    orig[j] = start + j;
    if (is_even) {
      tnts[j] = 0ULL;
      is_even = false;
    } else {
      tnts[j] = 1ULL;
      is_even = true;
    }
  }
}

uint64_t sum_composite_unit_fraction_coresilience(uint64_t n) {
  auto sqrt_n = pe::i_sqrt(n);
  auto sv_limit = sqrt_n + pe::MAX_PRIME_GAP_BELOW_BILLION;
  auto sv { pe::Sieve(sv_limit) };
  auto prms { std::vector<uint64_t>() };
  sv.extract_primes(prms);
  auto segment_size = sqrt_n + sqrt_n;
  auto orig { std::vector<uint64_t>(segment_size, 0ULL) };
  auto tnts { std::vector<uint64_t>(segment_size, 0ULL) };
  auto start { 2ULL };
  auto result { 0ULL };
  while (start <= n) {
    init_orig_tnts(start, segment_size, orig, tnts);
    sieve_odd_sqr_free_tnts(sqrt_n, prms, orig, tnts);
    for (auto i = 0ULL; i < segment_size; ++i) {
      auto x = start + i;
      auto x_minus_1 = x - 1ULL;
      auto t = tnts[i];
      if ((t > 0ULL) && ((t == x_minus_1) == false)) {
        auto nr = x - t;
        auto is_unit_fraction = ((x_minus_1 % nr) == 0ULL);
        if (is_unit_fraction) {
          result = result + x;
        }
      }
    }
    start = start + segment_size;
  }
  return result;
}

uint64_t solve(uint64_t n) {
  auto result = sum_composite_unit_fraction_coresilience(n);
  return result;
}

int main(int argc, char** argv) {
  auto n { 200000000000ULL };
  auto result { solve(n) };
  std::cout << result << std::endl;
  return 0;
}