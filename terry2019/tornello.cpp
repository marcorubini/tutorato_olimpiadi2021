#include <iostream>

void solve (int t)
{
  int N;
  std::cin >> N;

  int entrati = 0;
  int usciti = 0;
  int answer = 0;
  for (int i = 0; i < N; ++i) {
    int evento;
    std::cin >> evento;
    if (evento == 1) {
      if (usciti > 0)
        --usciti;
      ++entrati;
    } else {
      if (entrati > 0)
        --entrati;
      ++usciti;
    }
    answer = std::max (answer, std::abs (entrati - usciti));
  }

  std::cout << "Case #" << t + 1 << ": " << answer << std::endl;
}

int main ()
{
  int T;
  std::cin >> T;
  for (int i = 0; i < T; ++i) {
    solve (i);
  }
}
