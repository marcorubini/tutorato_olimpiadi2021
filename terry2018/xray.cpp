#include <algorithm>
#include <iostream>
#include <vector>

int solve_rec (int* first, int* last)
{
  if (first == last) {
    return 0;
  } else {
    auto min_pos = std::min_element (first, last);
    int min_value = *min_pos;
    int answer = 0;
    for (auto it = first; it != last; ++it)
      *it -= min_value;
    answer += min_value;
    answer += solve_rec (first, min_pos);
    answer += solve_rec (min_pos + 1, last);
    return answer;
  }
}

void solve (int t)
{
  int N;
  std::cin >> N;
  auto radiazioni = std::vector<int> (N);
  for (int i = 0; i < N; ++i) {
    std::cin >> radiazioni[i];
  }

  int answer = solve_rec (radiazioni.data (), radiazioni.data () + N);
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
