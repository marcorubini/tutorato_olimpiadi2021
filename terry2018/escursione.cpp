#include <cstring>
#include <iostream>
#include <queue>

void solve (int t)
{
  int H;
  int W;
  std::cin >> H >> W;

  int mappa[100][100];
  for (int i = 0; i < H; ++i)
    for (int j = 0; j < W; ++j)
      std::cin >> mappa[i][j];

  int pericoli_minimi[100][100];
  for (int i = 0; i < 100; ++i)
    for (int j = 0; j < 100; ++j)
      pericoli_minimi[i][j] = 1000000;
  pericoli_minimi[0][0] = 0;

  struct nodo
  {
    int riga;
    int colonna;
    int pericolo;
  };

  auto queue = std::queue<nodo> ();
  queue.push (nodo {0, 0, 0});
  while (!queue.empty ()) {
    nodo curr = queue.front ();
    queue.pop ();

    if (curr.pericolo == pericoli_minimi[curr.riga][curr.colonna]) {
      int diff_row[] = {0, 0, 1, -1};
      int diff_col[] = {1, -1, 0, 0};
      for (int i = 0; i < 4; ++i) {
        int nuova_riga = curr.riga + diff_row[i];
        int nuova_colonna = curr.colonna + diff_col[i];
        if (nuova_riga >= 0 && nuova_riga < H && nuova_colonna >= 0 && nuova_colonna < W) {
          int pericolo_passo = std::abs (mappa[curr.riga][curr.colonna] - mappa[nuova_riga][nuova_colonna]);
          int pericolo = std::max (pericolo_passo, curr.pericolo);
          if (pericolo < pericoli_minimi[nuova_riga][nuova_colonna]) {
            queue.push (nodo {nuova_riga, nuova_colonna, pericolo});
            pericoli_minimi[nuova_riga][nuova_colonna] = pericolo;
          }
        }
      }
    }
  }

  std::cout << "Case #" << t << ": " << pericoli_minimi[H - 1][W - 1] << '\n';
}

bool check (int mappa[][100], bool visited[][100], int riga, int colonna, int H, int W, int soluzione)
{

  if (riga == H - 1 && colonna == W - 1) {
    return true;
  }

  visited[riga][colonna] = true;
  int diff_row[] = {0, 0, 1, -1};
  int diff_col[] = {1, -1, 0, 0};

  for (int i = 0; i < 4; ++i) {
    int nuova_riga = riga + diff_row[i];
    int nuova_colonna = colonna + diff_col[i];
    if (nuova_riga >= 0 && nuova_colonna >= 0 && nuova_riga < H && nuova_colonna < W) {

      if (!visited[nuova_riga][nuova_colonna]) {
        int pericolo_passo = std::abs (mappa[nuova_riga][nuova_colonna] - mappa[riga][colonna]);
        if (pericolo_passo <= soluzione) {
          if (check (mappa, visited, nuova_riga, nuova_colonna, H, W, soluzione))
            return true;
        }
      }
    }
  }

  return false;
}

#include <set>

void solve2 (int t)
{
  int H;
  int W;
  std::cin >> H >> W;

  int mappa[100][100];
  for (int i = 0; i < H; ++i)
    for (int j = 0; j < W; ++j)
      std::cin >> mappa[i][j];

  auto deltas = std::set<int> ();
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      for (int dx : {0, 0, -1, +1}) {
        for (int dy : {1, -1, 0, 0}) {
          if (dx == 0 || dy == 0) {
            int x = i + dx;
            int y = j + dy;
            if (x >= 0 && y >= 0 && x < H && y < W) {
              deltas.insert (std::abs (mappa[i][j] - mappa[x][y]));
            }
          }
        }
      }
    }
  }

  bool visited[100][100] {};
  for (int i : deltas) {
    memset (visited, 0, sizeof (visited));
    if (check (mappa, visited, 0, 0, H, W, i)) {
      std::cout << "Case #" << t << ": " << i << "\n";
      return;
    }
  }
}

int main ()
{
  int T;
  std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve2 (t);
  }
}
