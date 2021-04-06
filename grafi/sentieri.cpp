// Problema: https://training.olinfo.it/#/task/sentieri/statement

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main ()
{
#ifdef EVAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  int N; // numero incroci
  int A; // numero sentieri
  int B; // numero sentieri bollenti
  std::cin >> N >> A >> B;

  struct arco
  {
    int from;
    int to;
    int cost;
  };

  auto graph = std::vector<std::vector<arco>> (N);
  for (int i = 0; i < A; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    --from;
    --to;
    graph[from].push_back (arco {from, to, 0});
    graph[to].push_back (arco {to, from, 0});
  }
  for (int i = 0; i < B; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    --from;
    --to;
    graph[from].push_back (arco {from, to, 1});
    graph[to].push_back (arco {to, from, 1});
  }

  for (auto& adj : graph) {
    auto costo_minore = [] (arco x, arco y) { return x.cost < y.cost; };

    std::sort (adj.begin (), adj.end (), costo_minore);
  }

  auto visited = std::vector<bool> (N);
  // bfs con 2 queue. La prima contiene i nodi appena raggiunti usando un sentiero non bollente.
  // La seconda contiene i nodi appena raggiunti usando un sentiero bollente.
  // I nodi vengono visitati in ordine di distanza, come nella bfs con una coda.
  auto queue_non_bollenti = std::queue<int> ();
  auto queue_bollenti = std::queue<int> ();
  auto distanze = std::vector<int> (N);
  queue_non_bollenti.push (0);
  visited[0] = true;
  distanze[0] = 0;

  while (!queue_non_bollenti.empty () || !queue_bollenti.empty ()) {
    int curr;

    // se la prima coda non è vuota, estraggo dalla prima, altrimenti dalla seconda
    if (!queue_non_bollenti.empty ()) {
      curr = queue_non_bollenti.front ();
      queue_non_bollenti.pop ();
    } else {
      curr = queue_bollenti.front ();
      queue_bollenti.pop ();
    }

    // se sono arrivato a destinazione, stampo la distanza minima e termino
    if (curr == N - 1) {
      std::cout << distanze[curr] << '\n';
      return 0;
    }

    // altrimenti itero su tutti i vicini non visitati
    for (arco vicino : graph[curr]) {
      if (visited[vicino.to]) {
        distanze[vicino.to] = std::min (distanze[vicino.to], distanze[curr] + vicino.cost);
      } else {
        visited[vicino.to] = true;
        distanze[vicino.to] = distanze[curr] + vicino.cost;
        // se il sentiero è bollente, inserisco il vicino nella seconda coda, altrimenti nella prima.
        if (vicino.cost == 0) {
          queue_non_bollenti.push (vicino.to);
        } else {
          queue_bollenti.push (vicino.to);
        }
      }
    }
  }

  // La consegna dice che esiste sempra un percorso, quindi qui a questa riga non arriviamo mai.
  std::cout << "Non trovato\n";
}
