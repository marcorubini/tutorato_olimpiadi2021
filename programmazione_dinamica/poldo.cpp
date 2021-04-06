// Problema: https://training.olinfo.it/#/task/poldo/statement
// panini [3, 6, 7, 5, 3]
// soluz. [1, 1, 1, 2, 3]
// Longest increasing/decreasing subsequence

#include <iostream>
#include <vector>

int poldo (int panini[], int n)
{
  std::vector<int> soluzioni;
  soluzioni.assign (n, 0);
  soluzioni[0] = 1;

  // soluzioni[i] contiene la migliore soluzione che
  // finisce con il panino i-esimo
  for (int i = 1; i < n; ++i) {
    soluzioni[i] = 1;
    for (int j = 0; j < i; ++j) {
      if (panini[j] > panini[i])
        soluzioni[i] = std::max (soluzioni[i], soluzioni[j] + 1);
    }
  }

  int maxi = -1;
  for (int i = 0; i < n; ++i) {
    maxi = std::max (maxi, soluzioni[i]);
  }

  return maxi;
}

int main ()
{
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
  int n;
  std::cin >> n;

  auto panini = std::vector<int> (n);
  for (int& p : panini)
    std::cin >> p;

  std::cout << poldo (panini.data (), panini.size ()) << '\n';
}
