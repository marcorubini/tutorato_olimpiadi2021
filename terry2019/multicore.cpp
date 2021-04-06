#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <unordered_map>
#include <vector>

struct cpu
{
  int cores;
  int cost;
};

const int MAX_CORES = 200;
const int MAX_CPUS = 300;

using memo_table = std::vector<std::vector<long long>>;

auto solve_rec (std::vector<cpu> const& cpus, memo_table& memo, int last, int cores) -> long long
{
  if (memo[last][cores] != -1)
    return memo[last][cores];

  if (cores == 0)
    return memo[last][cores] = 0;

  if (last == cpus.size ())
    return memo[last][cores] = 1ull << 33;

  if (cpus[last].cores > cores)
    return memo[last][cores] = solve_rec (cpus, memo, last + 1, cores);

  long long answer = 1ull << 33;
  answer = std::min (answer, solve_rec (cpus, memo, last + 1, cores));
  answer = std::min (answer, solve_rec (cpus, memo, last + 1, cores - cpus[last].cores) + cpus[last].cost);
  return memo[last][cores] = answer;
}

void solve (int t)
{
  int N;
  int B;
  std::cin >> N >> B;

  auto cpus = std::vector<cpu> (N);
  for (int i = 0; i < N; ++i) {
    std::cin >> cpus[i].cores >> cpus[i].cost;
  }

  auto memo = memo_table (N + 1, std::vector<long long> (N * MAX_CORES + 1, -1ll));

  for (int C = N * MAX_CORES; C >= 0; --C) {
    if (solve_rec (cpus, memo, 0, C) <= B) {
      std::cout << "Case #" << t + 1 << ": " << C << '\n';
      break;
    }
  }
}

int main ()
{
  int T;
  std::cin >> T;
  for (int i = 0; i < T; ++i) {
    solve (i);
  }
}
