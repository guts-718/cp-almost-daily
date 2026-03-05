#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int inf = 1 << 30;

void chmin(int &a, int b) {
  a = min(a, b);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<int> A(n+1);
    for (int i=0; i<n; i++) cin >> A[i];
    vector<int> B(m);
    for (int i=0; i<m; i++) cin >> B[i];
    vector nxt(n, vector<int>(m));
    for (int k=0; k<m; k++) {
      int r = -1, sum = 0;
      for (int i=0; i<n; i++) {
        while (r < n && sum <= B[k]) sum += A[++r];
        nxt[i][k] = r;
        sum -= A[i];
      }
    }
    vector dp(n+1, vector<int>(m, inf));
    dp[0][0] = 0;
    for (int k=0; k<m; k++) {
      for (int i=0; i<n; i++) {
        chmin(dp[nxt[i][k]][k], dp[i][k] + m - k - 1);
        if (k < m-1)
          chmin(dp[i][k+1], dp[i][k]);
      }
    }
    int ans = inf;
    for (int k=0; k<m; k++) {
      chmin(ans, dp[n][k]);
    }
    if (ans == inf) {
      cout << "-1\n";
    } else {
      cout << ans << "\n";
    }
  }
  return 0;
}