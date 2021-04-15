// Statement: https://training.olinfo.it/#/task/topologia/statement

#include <algorithm>
#include <stack>
#include <vector>

auto visita ( //
  int index,
  std::vector<std::vector<int>> const& grafo,
  std::vector<bool>& visited) -> std::vector<int>
{
  int const N = grafo.size ();

  auto stack = std::stack<int> ();
  auto component = std::vector<int> ();
  stack.emplace (index);
  visited[index] = true;

  while (!stack.empty ()) {
    auto top = stack.top ();
    stack.pop ();
    component.push_back (top);

    for (int adj : grafo[top]) {
      if (!visited[adj]) {
        visited[adj] = true;
        stack.emplace (adj);
      }
    }
  }

  return component;
}

auto visita_tutte (std::vector<std::vector<int>> const& grafo) //
  -> std::vector<std::vector<int>>
{
  int const N = grafo.size ();
  auto componenti = std::vector<std::vector<int>> ();
  auto visited = std::vector<bool> (N, false);

  for (int i = 0; i < N; ++i) {
    if (!visited[i]) {
      auto componente = visita (i, grafo, visited);
      componenti.push_back (componente);
    }
  }

  return componenti;
}

bool is_linea (std::vector<int> const& component, std::vector<int> const& incoming)
{
  int count2 = std::count_if (component.begin (),
    component.end (), //
    [&] (int x) { return incoming[x] == 2; });
  int count1 = std::count_if (component.begin (), //
    component.end (),
    [&] (int x) { return incoming[x] == 1; });
  return (count2 == (int)component.size () - 2 && count1 == 2);
}

bool is_ciclo (std::vector<int> const& component, std::vector<int> const& incoming)
{
  int count2 = std::count_if (component.begin (),
    component.end (), //
    [&] (int x) { return incoming[x] == 2; });
  return (count2 == component.size ());
}

bool is_stella (std::vector<int> const& component, std::vector<int> const& incoming)
{
  int count1 = std::count_if (component.begin (),
    component.end (), //
    [&] (int x) { return incoming[x] == 1; });
  return component.size () >= 4 && count1 == component.size () - 1;
}

void Analizza (int N, int M, int A[], int B[], int T[])
{
  auto graph = std::vector<std::vector<int>> (N);
  auto incoming = std::vector<int> (N);

  for (int i = 0; i < M; ++i) {
    int from = A[i];
    int to = B[i];
    from--;
    to--;
    graph[from].push_back (to);
    graph[to].push_back (from);
    incoming[from]++;
    incoming[to]++;
  }

  for (auto c : visita_tutte (graph)) {
    T[0] += is_linea (c, incoming);
    T[1] += is_ciclo (c, incoming);
    T[2] += is_stella (c, incoming);
  }
}
