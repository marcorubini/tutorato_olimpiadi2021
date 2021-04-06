#include <iostream>
#include <string>
#include <vector>

void solve (int t)
{
  int lunghezze[4];
  for (int i = 0; i < 4; ++i)
    std::cin >> lunghezze[i];

  int M;
  std::cin >> M;

  std::string stringhe[4];
  for (int i = 0; i < 4; ++i)
    std::cin >> stringhe[i];

  for (int i = 0; i < static_cast<int> (stringhe[0].size ()); ++i) {
    for (int j = i; j < static_cast<int> (stringhe[0].size ()); ++j) {
      if (j - i + 1 != M)
        continue;
      auto sub = stringhe[0].substr (i, j - i + 1);
      auto found = std::vector<int> ();
      for (auto pos_found : {stringhe[1].find (sub), stringhe[2].find (sub), stringhe[3].find (sub)})
        if (pos_found != std::string::npos)
          found.push_back (pos_found);
      if (found.size () == 3) {
        std::cout << "Case #" << t + 1 << ": ";
        std::cout << i << " " << found[0] << " " << found[1] << " " << found[2] << "\n";
        return;
      }
    }
  }
}

int main ()
{
  int T;
  std::cin >> T;
  for (int i = 0; i < T; ++i) {
    solve (i);
  }
}
