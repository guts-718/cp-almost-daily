/**
 *    author:  tourist
 *    created: 05.10.2025 09:38:52
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    int ans = 0;
    for (int r = 0; r < 2; r++) {
      vector<int> b(n);
      b[0] = r;
      for (int i = 1; i < n; i++) {
        b[i] = 1 - (b[i - 1] + a[i] - a[i - 1]);
      }
      int mn = *min_element(b.begin(), b.end());
      int mx = *max_element(b.begin(), b.end());
      if (0 <= mn && mx <= 1) {
        int cnt = 1 + accumulate(b.begin() + 1, b.end(), 0);
        if (cnt == a[0]) {
          ans += 1;
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
