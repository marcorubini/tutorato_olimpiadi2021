// Problema: https://training.olinfo.it/#/task/minato/statement
#include <iostream>
#include <string>

const int MAXN = 101;
int N, M;

std::string grid[MAXN];
int sol[MAXN][MAXN] = {0};

int solve (int riga, int col)
{
  if (riga >= N || col >= M)
    return 0;

  if (sol[riga][col])
    return sol[riga][col];

  if (riga == N - 1 && col == M - 1) {
    return 1;
  }

  if (grid[riga][col] == '+')
    return 0;

  sol[riga][col] = solve (riga + 1, col) + solve (riga, col + 1);
  return sol[riga][col];
}

int main ()
{
#ifndef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  std::cin >> N >> M;
  for (int i = 0; i < N; i++) {
    std::cin >> grid[i];
  }

  std::cout << solve (0, 0);
}
