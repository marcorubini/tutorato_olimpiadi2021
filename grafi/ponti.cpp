// https://training.olinfo.it/#/task/ponti/statement

#include <iostream>
#include <vector>

void visita (int curr, std::vector<std::vector<int>> const& graph, std::vector<bool>& visited)
{
  visited[curr] = true;
  for (int other : graph[curr])
    if (!visited[other])
      visita (other, graph, visited);
}

int main ()
{
#ifndef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  int N;
  int M;
  std::cin >> N >> M;

  auto graph = std::vector<std::vector<int>> (N);
  for (int i = 0; i < M; ++i) {
    int from, to;
    std::cin >> from >> to;
    graph[from].push_back (to);
    graph[to].push_back (from);
  }

  auto visited = std::vector<bool> (N);
  int counter = 0;
  for (int i = 0; i < N; ++i) {
    if (!visited[i]) {
      visita (i, graph, visited);
      counter++;
    }
  }

  std::cout << counter - 1 << '\n';
}
