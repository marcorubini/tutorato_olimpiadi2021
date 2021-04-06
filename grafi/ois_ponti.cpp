// https://training.olinfo.it/#/task/ois_ponti/statement

#include <iostream>
#include <vector>

void visita (std::vector<std::vector<int>>& graph, int nodo, std::vector<bool>& visited)
{
  visited[nodo] = true;
  for (auto x : graph[nodo]) {
    if (!visited[x]) {
      visita (graph, x, visited);
    }
  }
}

int main ()
{
#ifndef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  int N, M;
  std::cin >> N >> M;

  auto graph = std::vector<std::vector<int>> (N);
  for (int i = 0; i < M; ++i) {
    int da;
    int a;
    std::cin >> da >> a;
    graph[da].push_back (a);
    graph[a].push_back (da);
  }

  auto visited = std::vector<bool> (N, false);
  int componenti = 0;
  for (int i = 0; i < N; ++i) {
    if (!visited[i]) {
      visita (graph, i, visited);
      componenti++;
    }
  }

  std::cout << componenti - 1 << '\n';
}
