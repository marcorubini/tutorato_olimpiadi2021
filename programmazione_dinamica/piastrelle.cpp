// Problema: https://training.olinfo.it/#/task/piastrelle/submissions

#include <iostream>
#include <string>
using namespace std;

int N;

const char SINGOLA[] = "[O]";
const char DOPPIA[] = "[OOOO]";

void risolvi (string str, int idx, std::ostream& out)
{
  if (idx == N) {
    out << str << "\n";
    return;
  }
  if (idx > N)
    return;

  risolvi (str + SINGOLA, idx + 1, out);
  risolvi (str + DOPPIA, idx + 2, out);
}

int main ()
{
#ifndef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif

  std::cin >> N;
  std::string str = "";
  risolvi (str, 0, std::cout);

  return 0;
}
