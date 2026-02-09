#include <bits/stdc++.h>
 
using namespace std;

using li = long long;

const int B = 60;
const li INF = 1e18;

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  array<array<li, B>, B> dp;
  for (int i = 0; i < B; ++i) {
    for (int j = 0; j < B; ++j) {
      dp[i][j] = INF;
    }
  }
  dp[0][0] = 0;
  for (int x = 0; x < B; ++x) {
    for (int i = B - 1; i >= 0; --i) {
      for (int j = B - 1; j >= 0; --j) {
        if (dp[i][j] == INF) continue;
        if (i + x < B) dp[i + x][j] = min(dp[i + x][j], dp[i][j] + (1LL << x));
        if (j + x < B) dp[i][j + x] = min(dp[i][j + x], dp[i][j] + (1LL << x));
      }
    }
  }
  int t;
  cin >> t;
  while (t--) {
    li x, y;
    cin >> x >> y;
    li ans = INF;
    for (int i = 0; i < B; ++i) {
      for (int j = 0; j < B; ++j) {
        if ((x >> i) == (y >> j)) ans = min(ans, dp[i][j]);
      }
    }
    cout << ans << '\n';
  }
}