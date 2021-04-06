// Problema: https://training.olinfo.it/#/task/torri/statement

#include <iostream>
#include <vector>

int poldo (std::vector<std::pair<int, int>> torri)
{
  std::vector<int> soluzioni (torri.size ());

  int totale = 0;
  for (auto& torre : torri)
    totale += torre.second;
  soluzioni[0] = totale - torri[0].second;

  // soluzioni[i] contiene la migliore soluzione che
  // finisce con la torre i-esima
  for (int i = 1; i < (int)torri.size (); ++i) {
    soluzioni[i] = totale - torri[i].second;
    for (int j = 0; j < i; ++j) {
      if (torri[j].first > torri[i].first)
        soluzioni[i] = std::min (soluzioni[i], soluzioni[j] - torri[i].second);
    }
  }

  int mini = 1u << 30;
  for (int i = 0; i < (int)torri.size (); ++i) {
    mini = std::min (mini, soluzioni[i]);
  }

  return mini;
}

int main ()
{
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);

  int n;
  std::cin >> n;

  auto torri = std::vector<std::pair<int, int>> (n);
  for (auto& torre : torri)
    std::cin >> torre.first >> torre.second;

  std::cout << poldo (torri) << '\n';
}
