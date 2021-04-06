// https://training.olinfo.it/#/task/ois_estintori/statement

#include <iostream>
#include <string>
#include <vector>

int R, C;

bool visita (std::vector<std::string>& grid, int riga, int colonna, std::vector<std::vector<bool>>& visited)
{
  visited[riga][colonna] = true;
  bool trovato = grid[riga][colonna] == '@';

  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, +1};
  for (int d = 0; d < 4; ++d) {
    int riga2 = riga + dr[d];
    int colonna2 = colonna + dc[d];
    if (riga2 < 0 || colonna2 < 0 || riga2 >= R || colonna2 >= C)
      continue;

    if (grid[riga2][colonna2] == '#')
      continue;

    if (visited[riga2][colonna2])
      continue;

    trovato |= visita (grid, riga2, colonna2, visited);
  }

  return trovato;
}

int main ()
{
#ifndef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  std::cin >> R >> C;
  std::cin.ignore (1);

  auto grid = std::vector<std::string> (R);
  for (int i = 0; i < R; ++i) {
    std::getline (std::cin, grid[i]);
    std::cout << grid[i] << '\n';
  }

  auto visited = std::vector<std::vector<bool>> (R, std::vector<bool> (C, false));

  int componenti_senza_estintore = 0;
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if ((grid[i][j] == '.' || grid[i][j] == '@') && !visited[i][j]) {
        std::cout << "Visit " << i << ", " << j << std::endl;
        bool trovato = visita (grid, i, j, visited);
        componenti_senza_estintore += !trovato;
      }
    }
  }

  std::cout << componenti_senza_estintore << '\n';
}
