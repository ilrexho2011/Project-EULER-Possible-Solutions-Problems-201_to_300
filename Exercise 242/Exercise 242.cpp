#include<stdio.h>
#include<stdlib.h>
#include<map>

const long long N = 1000000000000LL;
const long long M = (N-1)/4;

std::map<long long, long long> cache;
long long f(long long x) {
  std::map<long long, long long>::iterator iter = cache.find(x);
  if (iter!=cache.end()) return iter->second;
  if (x == 0) return cache[x] = 0;
  if (x == 1) return cache[x] = 1;
  if (x%2 == 1) return cache[x] = 2*f(x/2) + f((x/2)+1);
  else return cache[x] = 3*f(x/2);
}

int main (void) {
  printf("%lld\n",f(M+1));
  return 0;
}