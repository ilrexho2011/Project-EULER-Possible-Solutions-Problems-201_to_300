#include <iostream>
#include <bitset>
#include <set>

const int L = 15, dx[] = {0,1, 0,-1}, dy[] = {1,0,-1, 0};
static int b[2 * L][2 * L];
static std::set<long> s;

void generate(int d, int x, int y, long a)
{
  b[x][y] = d;
  a <<= ((d + 1) / 2);
  for (int i = 0; i < 4; ++i)
    if (b[x + dx[i]][y + dy[i]] >= 0)
      a |= 1 << (b[x + dx[i]][y + dy[i]] / 2);
  if (d == L - 1) s.insert(a);
  else
    for (int i = 0; i < 4; ++i)
      if (b[x + dx[i]][y + dy[i]] < 0)
        generate(d + 1, x + dx[i], y + dy[i], a);
  b[x][y] = -1;
}

void nub()
{
  std::set<long> t = s;
  s.clear();
  for (auto a = t.rbegin(); a != t.rend(); ++a) {
    bool b = false;
    for (auto c = s.begin(); c != s.end(); ++c)
      if (b = (*c == (*a | *c))) break;
    if (!b) s.insert(*a);
  }
}

int count(int h)
{
  long t = 0;
  for (int i = 0; i < L; ++i) {
    t <<= ((i + 1) / 2);
    if (h & (1 << i))
      for (int j = (i + 1) % 2; j < i; j += 2)
        if (h & (1 << j)) t |= 1 << (j / 2);
  }
  int m = 0;
  for (auto a = s.begin(); a != s.end(); ++a)
    m = std::max(m, (int)((std::bitset<64>)(t & *a)).count());
  return m;
}

int main()
{
  for (int i = 0; i < 2 * L; ++i)
    for (int j = 0; j < 2 * L; ++j)
      b[i][j] = -1;
  generate(0, L, L, 0);
  nub();
  long c = 0;
  for (int i = 0; i < (1 << L); ++i) c += count(i);
  std::cout.precision(20);
  std::cout << c / 32768.0 << std::endl;
}