#include <algorithm>
#include <iostream>

void solve (int t)
{
  int N;
  std::cin >> N;

  int answer = 0;
  for (int i = 0; i < N; ++i) {
    int curr;
    std::cin >> curr;
    answer += std::max (0, curr);
  }

  std::cout << "Case #" << t + 1 << ": " << answer << "\n";
}
int main ()
{
  int T;
  std::cin >> T;
  for (int i = 0; i < T; ++i) {
    solve (i);
  }
}
