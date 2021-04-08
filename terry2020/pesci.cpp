#include <iostream>

void solve (int t)
{
  int N, K;
  std::cin >> N >> K;

  long long sum = 0;
  while (N > 0) {
    sum += N;
    N /= K;
  }

  std::cout << "Case #" << t + 1 << ": " << sum << '\n';
}

int main ()
{
  int T;
  std::cin >> T;
  for (int i = 0; i < T; ++i) {
    solve (i);
  }
}
