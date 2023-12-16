#include <iostream>

#include "../useful/everything.h"

using namespace std;

const long long MAX = 10000000000000000;

int main() {
  primes_init();

  // stores the divisors of 84*2 = 168
  vector<int> divs = divisors(168);

  // generating primitive pythagorean triples with a=u^2-v^2, b=2uv, c=u^2+v^2 with gcd(u,v)==1 and u-v odd
  // if perfect triple, u^2+v^2 must be a perfect square - that means u and v must be the sides of a pythagorean triple
  // so u = u2^2-v2^2, v = 2*u2*v2
  // if gcd(u,v)==1, u and v are part of primitive triple, so gcd(u2,v2)==1
  // if c<=MAX, then u^2+v^2<=MAX, or u2^4 + 2*u2^2*v2^2 + v2^4<=MAX, so u2^4<=MAX
  // super-perfect, area%84 == 0
  int count = 0;
  for(long long u2 = 1; u2*u2*u2*u2 <= MAX; ++u2) {
    for(long long v2 = 1; v2 < u2; ++v2) {
      // make sure it will produce primitive triple
      if(gcd(u2,v2) != 1 || (u2-v2)%2 == 0) {
        continue;
      }

      long long u = u2*u2 - v2*v2;
      long long v = 2*u2*v2;
      if(u*u + v*v > MAX) {
        continue; 
      }

      long long a = abs(u*u - v*v);
      long long b = 2*u*v;
      // check if area (a*b/2) will be divisble by 84
      // we do this by checking if a and b are divisible by divisors of 2*84
      bool tocount = true;
      for(unsigned int i = 0; i < divs.size(); ++i) {
        if(a%divs[i]==0 && b%(168/divs[i])==0) {
          tocount = false;
          break;
        }
      }
      if(tocount) {
        ++count;
      }
    }
  }

  cout << count << "\n";
  return 0;
}