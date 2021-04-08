#include <cassert>
#include <iostream>
#include <vector>

void solve (int t)
{
  int N;
  std::cin >> N;
  auto A = std::vector<int> (N);
  for (int i = 0; i < N; ++i) {
    std::cin >> A[i];
  }

  auto con_follower = std::vector<int> ();
  auto senza_follower = std::vector<int> ();
  for (int i = 0; i < N; ++i) {
    if (A[i] == 0) {
      senza_follower.push_back (i);
    } else {
      con_follower.push_back (i);
    }
  }

  auto F = std::vector<int> (N);
  for (int i = 0; i < (int)con_follower.size (); ++i) {
    int j = (i + 1) % con_follower.size ();
    F[con_follower[i]] = con_follower[j];
    A[con_follower[j]]--;
  }

  for (int i : con_follower) {
    while (A[i] > 0) {
      int x = senza_follower.back ();
      senza_follower.pop_back ();
      F[x] = i;
      A[i]--;
    }
  }

  std::cout << "Case #" << t + 1 << ": ";
  for (int x : F)
    std::cout << x << " ";
  std::cout << "\n";
}

int main ()
{
  int T;
  std::cin >> T;
  for (int i = 0; i < T; ++i) {
    solve (i);
  }
}
