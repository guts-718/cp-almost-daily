#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    cin >> n;

    vector<ll> L(n + 1), R(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> L[i] >> R[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> c(n + 1);

    // First DFS: compute c[v]
    function<void(int, int)> dfsAssign = [&](int v, int parent) {
        ll maxChild = 0;
        for (int child : adj[v]) {
            if (child == parent) continue;
            dfsAssign(child, v);
            maxChild = max(maxChild, c[child]);
        }
        c[v] = max(L[v], min(R[v], maxChild));
    };

    dfsAssign(1, 0);

    vector<ll> dp(n + 1, 0);

    // Second DFS: compute dp[v]
    function<void(int, int)> dfsDP = [&](int v, int parent) {
        for (int child : adj[v]) {
            if (child == parent) continue;
            dfsDP(child, v);

            dp[v] += dp[child];
            if (c[child] > c[v]) {
                dp[v] += c[child] - c[v];
            }
        }
    };

    dfsDP(1, 0);

    cout << dp[1] + c[1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
