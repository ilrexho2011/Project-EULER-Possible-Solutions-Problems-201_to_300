#include <iostream>
#include <cmath>

using namespace std;

double annulus(double a, double x)
{
  return (((x / 2.0) * sqrt((a * a) - (x * x))) + (((a * a) / 2.0) * asin(x / a))) - x;
}

int main()
{
  long int k;
  double a, b, m, p, q;
  double ts = 0.0;

  // k=1 case
  m = annulus(1.5, sqrt(1.25)) - annulus(1.5, 1);
  ts = ts + m;
  for (k = 2; k <= 100000; k++) {
    a = ((double) k) + 0.5;
    q = sqrt((a * a) - 1);
    m = annulus(a, q) - annulus(a, 1);
    p = m;
    b = ((double) k) - 0.5;
    q = sqrt((b * b) - 1);
    m = annulus(b, q) - annulus(b, 1);
    p = p - m;
    p = p / (k * k);
    ts = ts + (k * p);
  }
  cout.precision(14);
  cout << ts << endl;

  return 0;
}