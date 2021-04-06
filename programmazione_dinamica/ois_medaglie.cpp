// Problema: https://training.olinfo.it/#/task/ois_medaglie/statement

#include <iostream>
#include <vector>

const int MAXN = 100010;

int numMedaglie;
int puntiMedaglie[MAXN];
int somme[MAXN];

int migliori[MAXN] = {0};

int migliore (int n)
{
  if (n < 0) {
    return 0;
  }

  if (migliori[n] != 0) {
    return migliori[n];
  }

  int punti1 = somme[n] - migliore (n - 1);
  int punti2 = somme[n] - migliore (n - 2);
  int punti3 = somme[n] - migliore (n - 3);

  if (punti1 >= punti2 && punti1 >= punti3) {
    migliori[n] = punti1;
  } else if (punti2 >= punti1 && punti2 >= punti3) {
    migliori[n] = punti2;
  } else {
    migliori[n] = punti3;
  }

  return migliori[n];
}

int main ()
{
#ifndef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  std::cin >> numMedaglie;

  for (int i = 0; i < numMedaglie; i++) {
    int a;
    std::cin >> a;
    if (a == 0) {
      puntiMedaglie[i] = 100;
    } else if (a == 1) {
      puntiMedaglie[i] = 300;
    } else {
      puntiMedaglie[i] = 500;
    }
  }

  somme[0] = puntiMedaglie[0];
  for (int i = 1; i < numMedaglie; i++) {
    somme[i] = somme[i - 1] + puntiMedaglie[i];
  }

  std::cout << migliore (numMedaglie - 1) << "\n";
}
