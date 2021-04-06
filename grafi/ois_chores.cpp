// Problema: https://training.olinfo.it/#/task/ois_chores/statement

#include <iostream>
#include <vector>

void segna_distanze_albero_rec (int curr,
  std::vector<std::vector<int>> const& grafo,
  std::vector<int>& distanze,
  std::vector<bool>& visited)
{
  for (int vicino : grafo[curr]) {
    if (!visited[vicino]) {
      visited[vicino] = true;
      distanze[vicino] = distanze[curr] + 1;
      segna_distanze_albero_rec (vicino, grafo, distanze, visited);
    }
  }
}

void segna_distanze_albero (int partenza, std::vector<std::vector<int>> const& grafo, std::vector<int>& distanze)
{
  int const N = grafo.size ();
  auto visited = std::vector<bool> (N, false);

  distanze[partenza] = 0;
  visited[partenza] = true;
  segna_distanze_albero_rec (partenza, grafo, distanze, visited);
}

int nodo_lontano (std::vector<int> const& distanze)
{
  int nodo = -1;
  int dist = -1;
  for (unsigned i = 0; i < distanze.size (); ++i) {
    if (distanze[i] > dist) {
      dist = distanze[i];
      nodo = i;
    }
  }

  return nodo;
}

int main ()
{
#ifdef EVAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  int N;
  std::cin >> N;

  auto graph = std::vector<std::vector<int>> (N);
  for (int i = 0; i < N - 1; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    graph[from].push_back (to);
    graph[to].push_back (from);
  }

  auto distanze1 = std::vector<int> (N);
  segna_distanze_albero (0, graph, distanze1);
  int lontano1 = nodo_lontano (distanze1);

  auto distanze2 = std::vector<int> (N);
  segna_distanze_albero (lontano1, graph, distanze2);
  int lontano2 = nodo_lontano (distanze2);

  std::cout << distanze2[lontano2] * 2 << '\n';
}
