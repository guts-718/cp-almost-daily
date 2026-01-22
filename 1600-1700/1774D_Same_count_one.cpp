#include <bits/stdc++.h>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d %d", &n, &m);
    std::vector<std::vector<int>> A(n, std::vector<int>(m, 0));
    std::vector<int> sum(n, 0);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", &A[i][j]);
        sum[i] += A[i][j];
      }
    }
    int tot = 0;
    for (int i = 0; i < n; ++i) tot += sum[i];
    if (tot % n) {
      puts("-1");
      continue;
    }
    tot /= n;
    std::vector<std::tuple<int, int, int>> ans;
    std::vector<int> Vg, Vl;
    Vg.reserve(n), Vl.reserve(n);
    for (int j = 0; j < m; ++j) {
      for (int i = 0; i < n; ++i) {
        if (sum[i] > tot && A[i][j]) Vg.push_back(i);
        if (sum[i] < tot && !A[i][j]) Vl.push_back(i);
      }
      for (int i = 0; i < (int)std::min(Vl.size(), Vg.size()); ++i) {
        ++sum[Vl[i]], --sum[Vg[i]];
        ans.emplace_back(Vl[i], Vg[i], j);
      }
      Vl.clear(), Vg.clear();
    }
    printf("%d\n", (int)ans.size());
    for (auto [i, j, k] : ans) printf("%d %d %d\n", i + 1, j + 1, k + 1);
  }
  return 0;
}