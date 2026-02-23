#include <bits/stdc++.h>

using namespace std;

using li = long long;

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    li delta = 0, ans = 0;
    li sum = 0, mx = 0;
    for (int i = 0; i < n; ++i) {
      li x; cin >> x;
      sum += x;
      mx = max(mx, sum);
      if (sum - mx < delta) {
        delta = sum - mx;
        ans = mx;
      }
    }
    cout << ans << '\n';
  }
}