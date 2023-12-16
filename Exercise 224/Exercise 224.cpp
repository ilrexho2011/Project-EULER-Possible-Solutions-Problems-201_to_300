#include <numeric>
#include <vector>
#include <iostream>

const int P = 75'000'000;
const int P2 = P/2;

std::vector<std::pair<int, int>> squares;
int nsquares[P2+1];

void InitSquares() {
  for (int a = 0; a*a <= P2; ++a)
    for (int b = 0; a*a + b*b <= P2; ++b)
      ++nsquares[a*a + b*b];

  std::partial_sum(std::begin(nsquares), std::end(nsquares), std::begin(nsquares));
  squares.resize(nsquares[P2]);

  for (int a = 0; a*a < P2; ++a)
    for (int b = 0; a*a + b*b < P2; ++b)
      squares[--nsquares[a*a + b*b]] = {a, b};
}

int CountSolutions(int c) {
  std::vector<std::pair<int, int>> results;
  for (int i = nsquares[c-1]; i < nsquares[c]; ++i)
    for (int j = nsquares[c+1]; j < nsquares[c+2]; ++j) {
      auto [a1, b1] = squares[i];
      auto [a2, b2] = squares[j];
      // a + bi = (a1 + i b1) (a2 + i b2)
      int a = abs(a1*a2 - b1*b2);
      int b = a1*b2 + b1*a2;
      if (a > b) std::swap(a, b);
      if (a == 0 || b == 0 || a + b + c > P) continue;
      results.emplace_back(a, b);
    }
  sort(results.begin(), results.end());
  return unique(results.begin(), results.end()) - results.begin();
}

int main() {
  InitSquares();
  int count = 0;
  for (int c = 3; c < P2; c += 2)
    count += CountSolutions(c);
  std::cout << count << std::endl;
  return 0;
}