// Problema: https://training.olinfo.it/#/task/trampolino/statement

#include <iostream>

const int MAXN = 1000000;

int trampolini[MAXN];
int N;

// x è il punto in cui sono arrivato facendo salti ottimali
int soluzione (int x)
{
  if (x >= N)
    return 0;

  // massimo è il punto più a destra in cui posso saltare
  int massimo = x + trampolini[x];
  if (massimo >= N)
    return 1;

  // idx è il prossimo trampolino in cui saltare
  int idx = massimo;

  // intervallo di trampolini raggiungibili da x
  int fine = x + trampolini[x];
  int inizio = x + 1;

  // trovo il trampolino in [inizio, fine) che mi permette di saltare più a destra
  // possibile al prossimo salto
  for (int i = inizio; i <= fine; i++) {
    if (massimo < x + trampolini[i] + (i - x)) {
      massimo = x + trampolini[i] + (i - x);
      idx = i;
    }
  }

  return 1 + soluzione (idx);
}

int main ()
{
#ifndef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  std::cin >> N;
  for (int i = 0; i < N; i++)
    std::cin >> trampolini[i];

  std::cout << soluzione (0) << "\n";

  return 0;
}
