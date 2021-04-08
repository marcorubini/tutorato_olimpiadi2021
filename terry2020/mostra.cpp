#include <iostream>
#include <map>
#include <vector>

// Guadagno massimo assignando visitatori e guide
// partendo dal i-simo visitatore e dalla j-esima guida.
int solve_rec (std::vector<int> const& V,
  std::vector<int> const& G,                //
  std::map<std::pair<int, int>, int>& memo, //
  int i,                                    //
  int j)
{
  if (memo.find (std::pair<int, int> {i, j}) != memo.end ()) {
    return memo[std::pair<int, int> {i, j}];
  }

  if (i == V.size ()) {
    return 0;
  } else if (j == G.size ()) {
    return V.size () - i;
  } else {
    int ans = solve_rec (V, G, memo, i + 1, j) + 1;
    ans = std::max (ans, solve_rec (V, G, memo, i, j + 1));
    if (G[j] > V[i]) {
      ans = std::max (ans, solve_rec (V, G, memo, i + 1, j + 1) + 2);
    }
    memo[std::pair<int, int> {i, j}] = ans;
    return ans;
  }
}

void solve (int t)
{
  int N, M;
  std::cin >> N >> M;

  auto V = std::vector<int> (N);
  for (int i = 0; i < N; ++i) {
    std::cin >> V[i];
  }

  auto G = std::vector<int> (M);
  for (int i = 0; i < M; ++i) {
    std::cin >> G[i];
  }

  auto memo = std::map<std::pair<int, int>, int> {};
  int answer = solve_rec (V, G, memo, 0, 0);
  std::cout << "Case #" << t + 1 << ": " << answer << '\n';
}

int main ()
{
  int T;
  std::cin >> T;
  for (int i = 0; i < T; ++i) {
    solve (i);
  }
}
