// Problema: https://training.olinfo.it/#/task/nonna/statement

#include <algorithm>
#include <iostream>
#include <string>

const int MAXN = 5001;
const int MAXK = 5001;
const int MAXP = 1000001;

int portate[MAXN];
int N, K;

int risolvi ()
{
  // dina[i] == true se è possibile costruire una portata di i grammi.
  bool dina[MAXP] = {0};

  // risultato (portata più leggera che è possibile costruire, e pesa più di K)
  int ris = MAXP;

  std::sort (portate, portate + N);
  dina[0] = true;

  for (int i = 0; i < N; i++) {
    // se la portata non è gigantesca, provo ad abbinarla a portate precedenti
    if (portate[i] < MAXK) {
      for (int j = MAXK; j >= 0; j--) {
        dina[j + portate[i]] |= dina[j];
      }
    }
    // posso mangiare l'unica portata portate[i]
    dina[portate[i]] = true;
  }

  for (int i = K; i < MAXP; i++) {
    if (dina[i])
      return i;
  }

  return ris;
}

int main ()
{
#ifndef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  std::cin >> N >> K;

  for (int i = 0; i < N; i++) {
    std::cin >> portate[i];
  }

  std::cout << risolvi ();
  return 0;
}
