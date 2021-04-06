// Problema: https://training.olinfo.it/#/task/mappa/statement

#include <iostream>
#include <queue>
#include <string>
#include <vector>

int main ()
{
#ifdef EVAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  int N;
  std::cin >> N;
  std::cin.ignore (1);

  auto grid = std::vector<std::string> (N);
  for (auto& row : grid)
    std::getline (std::cin, row);

  // bfs da (0,0) a (N-1, N-1)

  struct nodo
  {
    int riga;
    int colonna;
    int distanza;
  };

  auto visited = std::vector<std::vector<bool>> (N, std::vector<bool> (N, false));
  auto queue = std::queue<nodo> ();

  // visito il primo nodo
  queue.push (nodo {0, 0, 0});
  visited[0][0] = true;

  // fintantochè la coda non è vuota
  while (!queue.empty ()) {
    auto curr = queue.front ();
    queue.pop ();

    // se sono arrivato a (N-1, N-1)
    if (curr.riga == N - 1 && curr.colonna == N - 1) {
      // la consegna vuole il numero di lastroni attraversati, che è uguale al numero di passi +1
      std::cout << curr.distanza + 1 << '\n';
      return 0;
    }

    // visito tutti gli adiacenti
    int delta_row[] = {-1, +1, 0, 0};
    int delta_col[] = {0, 0, -1, +1};
    for (int dr : delta_row) {
      for (int dc : delta_col) {
        int row = curr.riga + dr;
        int col = curr.colonna + dc;
        // controllo di non uscire dai bordi, di non visitare due volte lo stesso nodo, e di visitare solo lastroni
        if (row >= 0 && col >= 0 && row < N && col < N && !visited[row][col] && grid[row][col] == '*') {
          queue.push (nodo {row, col, curr.distanza + 1});
          visited[row][col] = true;
        }
      }
    }
  }

  // La consegna dice che un percorso esiste sempre, quindi a questa riga non arriveremo mai.
  std::cout << "Percorso non trovato" << std::endl;
}
