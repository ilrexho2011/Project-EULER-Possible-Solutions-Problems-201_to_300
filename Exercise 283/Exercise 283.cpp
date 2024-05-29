#include <cmath>
#include <cstdio>
#include <cassert>
#include <vector>

#define PB push_back

using namespace std;

typedef long long ll;
typedef double ld;

ll gcd(ll x, ll y) {
  return x==0 ? y : gcd(y%x, x);
}

ll get_area(ll a, ll b, ll c) {
  ld s = (a+b+c)/2;
  ld area = sqrt(s*(s-a)*(s-b)*(s-c));
  return ll(area+0.5);
}

vector<ll> factors(ll n) {
  vector<ll> A;
  for(ll i=1; i*i<=n; i++) {
    if(n%i==0) {
      A.PB(i);
      if(i*i < n) {
        A.PB(n/i);
      }
    }
  }
  return A;
}

int main() {
  ll LIM = 1000;

  ll ans = 0;
  ll count1 = 0;
  ll count2 = 0;
  for(ll m=1; m<=LIM; m++) {
    for(ll u : factors(2*m)) {
      for(ll v=1; v <= sqrt(3)*u; v++) {
        if(gcd(u,v)!=1) { continue; }
        ll val = 4*m*m*(u*u+v*v);
        ll d1 = -((2*m*u)%v);
        while(true) {
          d1 += v;
          if(d1*d1 > val) { break; }
          assert((d1+2*m*u)%v == 0);
          if(val%d1 != 0) { continue; }
          count1 += 1;
          ll d2 = val/d1;
          if((d2+2*m*u)%v!=0) { continue; }
          if(u<v && !(2*m/u*(v*v-u*u) <= d1 && d1<=2*m*sqrt(u*u+v*v))) { continue; }
          ll a = (d1+2*m*u)/v + (2*m*v)/u;
          ll b = (d2+2*m*u)/v + (2*m*v)/u;
          ll c = (d1+d2+4*m*u)/v;

          ll perimeter = a+b+c;
          // ll area = get_area(a, b, c);
          // assert(perimeter*m == area);

          ans += perimeter;
          count2 += 1;
          if(count2%1000 == 0) {
            printf("ratio=%lld count1=%lld count2=%lld\n", m, count1, count2);
            //printf("area=%lld perimeter=%lld ratio=%lld count=%lld\n", area, perimeter, m, cnt);
          }
        }
      }
    }
  }
  printf("%lld\n", ans);
}