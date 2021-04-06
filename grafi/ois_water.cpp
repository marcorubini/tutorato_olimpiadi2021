// Problema: https://training.olinfo.it/#/task/ois_water/statement

#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

struct nodo
{
  long long numero;
  int passi;
};

int main ()
{
#ifndef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  int N;
  std::cin >> N;

  auto queue = std::queue<nodo> ();
  queue.push (nodo {N, 0});

  auto potenze3 = std::vector<long long> (25);
  potenze3[0] = 1ll;
  for (int i = 1; i < 25; ++i) {
    potenze3[i] = potenze3[i - 1] * 3;
  }

  auto visitati = std::unordered_set<long long> ();
  visitati.insert (N);

  // visitiamo i nodi in ordine di distanza da N
  while (!queue.empty ()) {
    nodo curr = queue.front ();
    queue.pop ();

    if (curr.numero == 0) {
      std::cout << curr.passi << '\n';
      return 0;
    }

    auto n1 = curr.numero + 1;
    auto n2 = curr.numero - 1;
    auto n3 = curr.numero * 2;

    if (!visitati.count (n1)) {
      queue.push (nodo {n1, curr.passi + 1});
      visitati.insert (n1);
    }

    if (!visitati.count (n2)) {
      queue.push (nodo {n2, curr.passi + 1});
      visitati.insert (n2);
    }

    if (!visitati.count (n3)) {
      queue.push (nodo {n3, curr.passi + 1});
      visitati.insert (n3);
    }

    for (auto p : potenze3) {
      if (p != 1 && curr.numero % p == 0) {
        auto n4 = curr.numero / p;
        if (!visitati.count (n4)) {
          queue.push ({n4, curr.passi + 1});
          visitati.insert (n4);
        }
      }
    }
  }
}
