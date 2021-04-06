// Problema: https://training.olinfo.it/#/task/triangolo/statement

#include <algorithm>
#include <iostream>
#include <vector>

int memo[100][100];
bool calcolati[100][100];

int triangolo_massimo (int tri[][100], int livello, int pos, int n)
{

  if (calcolati[livello][pos])
    return memo[livello][pos];

  if (livello == n - 1) {
    return tri[livello][pos];
  }

  // provo tutte le soluzioni ricorsivamente
  int sol1 = triangolo_massimo (tri, livello + 1, pos, n) + tri[livello][pos];
  int sol2 = triangolo_massimo (tri, livello + 1, pos + 1, n) + tri[livello][pos];

  memo[livello][pos] = std::max (sol1, sol2);
  calcolati[livello][pos] = true;

  return std::max (sol1, sol2);
}

int triangolo_massimo_bottom_up (int tri[][100], int n)
{
  auto soluzioni_sopra = std::vector<int> (n);
  auto soluzioni_sotto = std::vector<int> (n);

  // calcolo le soluzioni per l'ultimo livello
  for (int i = 0; i < n; ++i)
    soluzioni_sotto[i] = tri[n - 1][i];

  for (int j = n - 2; j >= 0; --j) {
    for (int i = 0; i < j + 1; ++i) {
      int numero = tri[j][i];
      int sol1 = soluzioni_sotto[i] + numero;
      int sol2 = soluzioni_sotto[i + 1] + numero;
      soluzioni_sopra[i] = std::max (sol1, sol2);
    }

    std::fill (soluzioni_sotto.begin (), soluzioni_sotto.end (), 0);
    std::swap (soluzioni_sopra, soluzioni_sotto);
  }

  return *std::max_element (soluzioni_sotto.begin (), soluzioni_sotto.end ());
}

int main ()
{
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);

  int triangoli[100][100];
  int n;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i + 1; j++) {
      std::cin >> triangoli[i][j];
    }
  }

  std::cout << triangolo_massimo (triangoli, 0, 0, n) << '\n';
}
