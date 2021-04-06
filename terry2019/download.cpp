#include <iostream>

void solve (int t)
{
  int N, F, C;
  std::cin >> N >> F >> C;

  int filmati = N / F;
  N %= F;
  int canzoni = N / C;

  std::cout << "Case #" << t + 1 << ": " << filmati << " " << canzoni << "\n";
}

int main ()
{
  int T;
  std::cin >> T;
  for (int i = 0; i < T; ++i) {
    solve (i);
  }
}
