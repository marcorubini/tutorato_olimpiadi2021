// https://training.olinfo.it/#/task/domino/statement

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int domino (std::pair<int, int> tessere[], int N, int i)
{
  if (i == N) {
    return 0;
  } else {
    // la tessera in posizione i è stata fissata, scelgo la prossima tessera
    int answer = 1;
    for (int j = i + 1; j < N; ++j) {
      if (tessere[j].first == tessere[i].second) {
        std::swap (tessere[i + 1], tessere[j]);
        answer = std::max (answer, 1 + domino (tessere, N, i + 1));
        std::swap (tessere[i + 1], tessere[j]);
      } else if (tessere[j].second == tessere[i].second) {
        // ribalto la prossima tessera, la collego e vedo se la soluzione migliora
        std::swap (tessere[j].first, tessere[j].second);
        std::swap (tessere[i + 1], tessere[j]);
        answer = std::max (answer, 1 + domino (tessere, N, i + 1));
        // annullo il ribaltamento
        std::swap (tessere[i + 1], tessere[j]);
        std::swap (tessere[j].first, tessere[j].second);
      }
    }
    return answer;
  }
}

int main ()
{
#ifndef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  int N;
  std::cin >> N;

  auto tessere = std::vector<std::pair<int, int>> (N);
  for (auto& tessera : tessere) {
    std::cin >> tessera.first >> tessera.second;
  }

  int answer = 0;
  for (int i = 0; i < N; ++i) {
    std::swap (tessere[0], tessere[i]);
    answer = std::max (answer, domino (tessere.data (), N, 0));

    std::swap (tessere[0].first, tessere[0].second);
    answer = std::max (answer, domino (tessere.data (), N, 0));

    std::swap (tessere[0].first, tessere[0].second);
    std::swap (tessere[0], tessere[i]);
  }

  std::cout << answer << '\n';
}
