#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
        int n;
        cin >> n;
        vector<ll> A(n);
        for (int i=0; i<n; i++) cin >> A[i];
        map<ll,vector<ll>> adj;
        for (int i=1; i<n; i++) {
            ll u = A[i] + i;
            ll v = u + i;
            adj[u].push_back(v);
        }
        set<ll> vis;
        function<void(ll)> dfs = [&](ll u) -> void {
            if (vis.count(u)) return;
            vis.insert(u);
            for (ll v : adj[u]) dfs(v);
        };
        dfs(n);
        cout << *vis.rbegin() << "\n";
  }
  return 0;
}