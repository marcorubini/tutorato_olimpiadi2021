// https://training.olinfo.it/#/task/ois_islands/statement

#include <iostream>
#include <stack>
#include <vector>

auto leggi_griglia (int R, int C) -> std::vector<std::vector<int>>
{
  auto griglia = std::vector<std::vector<int>> (R);
  for (int i = 0; i < R; ++i) {
    griglia[i] = std::vector<int> (C);
    for (int j = 0; j < C; ++j) {
      std::cin >> griglia[i][j];
    }
  }
  return griglia;
}

bool is_valid (int R, int C, int row, int col)
{
  return row >= 0 && col >= 0 && row < R && col < C;
}

auto visita ( //
  int row,
  int col,
  std::vector<std::vector<int>> const& grid,
  std::vector<std::vector<bool>>& visited) -> std::vector<std::pair<int, int>>
{
  int const R = grid.size ();
  int const C = grid[0].size ();

  auto stack = std::stack<std::pair<int, int>> ();
  auto component = std::vector<std::pair<int, int>> ();
  stack.emplace (row, col);
  visited[row][col] = true;

  while (!stack.empty ()) {
    auto top = stack.top ();
    stack.pop ();
    component.push_back (top);

    int directions[][2] {{0, -1}, {0, +1}, {+1, 0}, {-1, 0}};
    for (int d = 0; d < 4; ++d) {
      int next_row = top.first + directions[d][0];
      int next_col = top.second + directions[d][1];
      if (is_valid (R, C, next_row, next_col)) {
        if (grid[next_row][next_col] == 1) {
          if (!visited[next_row][next_col]) {
            visited[next_row][next_col] = true;
            stack.emplace (next_row, next_col);
          }
        }
      }
    }
  }

  return component;
}

auto visita_tutte (std::vector<std::vector<int>> const& grid) //
  -> std::vector<std::vector<std::pair<int, int>>>
{
  int const R = grid.size ();
  int const C = grid[0].size ();

  auto componenti = std::vector<std::vector<std::pair<int, int>>> ();
  auto visited = std::vector<std::vector<bool>> (R, std::vector<bool> (C, false));

  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (!visited[i][j] && grid[i][j] == 1) {
        auto componente = visita (i, j, grid, visited);
        componenti.push_back (componente);
      }
    }
  }

  return componenti;
}

bool is_bordo (int R, int C, int row, int col)
{
  return (row == 0 || col == 0 || row == R - 1 || col == C - 1);
}

auto scarta_bordi (int R, int C, std::vector<std::vector<std::pair<int, int>>> componenti)
  -> std::vector<std::vector<std::pair<int, int>>>
{
  auto risultato = std::vector<std::vector<std::pair<int, int>>> ();
  for (auto& c : componenti) {
    bool trovato = false;
    for (auto& cella : c) {
      if (is_bordo (R, C, cella.first, cella.second)) {
        trovato = true;
      }
    }
    if (!trovato) {
      risultato.push_back (c);
    }
  }
  return risultato;
}

int main ()
{
  int R;
  int C;
  std::cin >> R >> C;

  auto griglia = leggi_griglia (R, C);
  auto componenti = visita_tutte (griglia);
  auto senza_bordi = scarta_bordi (R, C, componenti);

  std::cout << senza_bordi.size () << '\n';
}
