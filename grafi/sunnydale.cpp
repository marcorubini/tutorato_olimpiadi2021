// Problema: https://training.olinfo.it/#/task/sunny/statement

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

  int N; // numero di svicoli
  int M; // numero di archi
  int H; // nodo di partenza
  int S; // nodo di arrivo
  std::cin >> N >> M >> H >> S;
  // Nel problema gli indici partono da 1, preferisco che partano da 0.
  --H;
  --S;

  struct arco
  {
    int from;
    int to;
    int luce;
  };

  auto graph = std::vector<std::vector<arco>> (N);
  for (int i = 0; i < M; ++i) {
    int from;
    int to;
    int luce;
    std::cin >> from >> to >> luce;
    // Nel problema gli indici partono da 1, preferisco che partano da 0.
    --from;
    --to;
    graph[from].push_back (arco {from, to, luce});
    graph[to].push_back (arco {to, from, luce});
  }

  // ordino le gallerie
  for (auto& adj : graph) {
    auto luce_minore = [] (arco const& x, arco const& y) { return x.luce < y.luce; };

    std::sort (adj.begin (), adj.end (), luce_minore);
  }

  // eseguo una bfs da H a S, scegliendo ad ogni nodo la galleria meno luminosa.

  struct nodo
  {
    int indice;
    int distanza;
  };

  auto visited = std::vector<bool> (N);
  auto queue = std::queue<nodo> ();
  queue.push (nodo {H, 0});
  visited[H] = true;

  while (!queue.empty ()) {
    auto curr = queue.front ();
    queue.pop ();

    if (curr.indice == S) {
      std::cout << curr.distanza << '\n';
      return 0;
    }

    for (auto arco : graph[curr.indice]) {
      if (!visited[arco.to]) {
        visited[arco.to] = true;
        queue.push ({arco.to, curr.distanza + 1});
      }

      // visito solo la galleria meno luminosa (le ho ordinate per luminosità all'inizio)
      break;
    }
  }

  // non ho trovato nessun percorso che soddisfi la consegna
  // la consegna dice di stampare -1 in questo caso.
  std::cout << -1 << '\n';
}
