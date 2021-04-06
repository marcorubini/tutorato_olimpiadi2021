#include <algorithm>
#include <iostream>
#include <numeric> // iota
#include <vector>

void solve (int t)
{
  int N;
  std::cin >> N;

  auto tutor = std::vector<int> (N);
  auto competenza = std::vector<int> (N);
  for (int i = 0; i < N; ++i) {
    std::cin >> tutor[i] >> competenza[i];
  }

  // Inizializzo indici con i numeri da 0 a N-1.
  auto indici = std::vector<int> (N);
  iota (indici.begin (), indici.end (), 0);
  // Ordino gli indici dei tutor per competenza decrescente.
  sort (indici.begin (), indici.end (), [&] (int x, int y) { return competenza[x] > competenza[y]; });

  int scambi = 0;
  for (int i : indici) {
    while (tutor.at (i) != -1 && competenza.at (tutor.at (i)) < competenza.at (i)) {
      // Scambio i con il suo tutor.

      int parente = tutor[i];
      auto childs_of_i = std::vector<int> ();
      auto childs_of_parente = std::vector<int> ();

      // Assegno a tutti quelli che hanno come tutor 'i' il tutor 'parente'.
      for (int j = 0; j < N; ++j) {
        if (tutor[j] == i) {
          childs_of_i.push_back (j);
        }
      }

      // Assegno a tutti quelli che hanno come tutor 'parente' il tutor i.
      for (int j = 0; j < N; ++j) {
        if (tutor[j] == parente && j != i) {
          childs_of_parente.push_back (j);
        }
      }

      for (int x : childs_of_i)
        tutor[x] = parente;
      for (int x : childs_of_parente)
        tutor[x] = i;

      // Assegno a 'i' il tutor di 'parente'.
      tutor[i] = tutor[parente];

      // Assegno a 'parente' il tutor 'i'.
      tutor[parente] = i;

      ++scambi;
    }
  }

  std::cout << "Case #" << t + 1 << ": " << scambi << "\n";
}

int main ()
{
  int T;
  std::cin >> T;
  for (int i = 0; i < T; ++i) {
    solve (i);
  }
}
