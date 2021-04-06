// Problema: https://training.olinfo.it/#/task/spesa/statement

#include <iostream>
#include <queue>
#include <vector>

// segna alla posizione i la distanza tra sorgente e i.
void segna_distanze (int sorgente, std::vector<std::vector<int>> const& grafo, std::vector<int>& distanze)
{
  // segna tutte le distanze a -1, così sappiamo quali nodi non vengono neanche visitati
  std::fill (distanze.begin (), distanze.end (), -1);

  int const N = grafo.size ();
  auto visited = std::vector<bool> (N, false);

  // visito la sorgente e segno la sua distanza (0)
  auto queue = std::queue<int> ();
  queue.push (sorgente);
  visited[sorgente] = 0;
  distanze[sorgente] = 0;

  // uso la bfs, così visito i nodi in ordine di distanza.
  while (!queue.empty ()) {
    int nodo = queue.front ();
    queue.pop ();

    // visito tutti i vicini
    for (int vicino : grafo[nodo]) {
      if (!visited[vicino]) {
        visited[vicino] = true;
        distanze[vicino] = distanze[nodo] + 1;
        queue.push (vicino);
      }
    }
  }
}

int main ()
{
#ifdef EVAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif
  int N; // numero incroci
  int M; // numero strade
  int K; // numero supermercati

  std::cin >> N >> M >> K;

  // Leggo gli indici dei supermercati, diminuisco di 1 per farli partire da 0.
  auto supermercati = std::vector<int> (K);
  for (int i = 0; i < K; ++i) {
    std::cin >> supermercati[i];
    supermercati[i]--;
  }

  // Leggo il grafo, diminuisco di 1 gli indici per farli partire da 0.
  auto graph = std::vector<std::vector<int>> (N);
  for (int i = 0; i < M; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    from--;
    to--;
    graph[from].push_back (to);
    graph[to].push_back (from);
  }

  auto distanze_da_casa = std::vector<int> (N);
  auto distanze_da_nonna = std::vector<int> (N);

  segna_distanze (0, graph, distanze_da_casa);
  segna_distanze (N - 1, graph, distanze_da_nonna);

  // trovo il supermercato che minimizza la somma distanza_da_casa + distanza_da_nonna
  int risultato = N * 2;
  for (int s : supermercati) {
    int d1 = distanze_da_casa[s];
    int d2 = distanze_da_nonna[s];
    if (d1 != -1 && d2 != -1) {
      risultato = std::min (risultato, d1 + d2);
    }
  }

  std::cout << risultato << '\n';
}
