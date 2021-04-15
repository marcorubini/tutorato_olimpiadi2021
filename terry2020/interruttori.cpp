#include <iostream>
#include <queue>
#include <vector>

void solve (int t)
{
  int N;
  int A;
  int B;
  std::cin >> N >> A >> B;

  auto tipo1 = std::vector<bool> (N);
  auto graph = std::vector<std::vector<int>> (N);

  for (int i = 0; i < A; ++i) {
    int x;
    std::cin >> x;
    tipo1[x] = true;
  }

  for (int i = 0; i < B; ++i) {
    int x;
    int y;
    std::cin >> x >> y;
    graph[x].push_back (y);
    graph[y].push_back (x);
  }

  auto visited = std::vector<int> (N, false);
  auto distances = std::vector<int> (N, 0);
  auto queue = std::queue<int> ();
  for (int i = 0; i < N; ++i) {
    if (tipo1[i]) {
      visited[i] = true;
      queue.push (i);
    }
  }

  while (!queue.empty ()) {
    int x = queue.front ();
    queue.pop ();

    for (int y : graph[x]) {
      if (!visited[y]) {
        visited[y] = true;
        distances[y] = distances[x] + 1;
        queue.push (y);
      }
    }
  }

  int best_ans = -1;
  int best_index = -1;
  for (int i = 0; i < N; ++i) {
    if (best_ans < distances[i]) {
      best_ans = distances[i];
      best_index = i;
    }
  }

  std::cout << "Case #" << t + 1 << ": " << best_index << " " << best_ans + 1 << '\n';
}

int main ()
{
  int T;
  std::cin >> T;

  for (int i = 0; i < T; ++i) {
    solve (i);
  }
}
