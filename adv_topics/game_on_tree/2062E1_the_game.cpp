#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class FenwickTree {
private:
    int n;
    vector<ll> bit;

public:
    FenwickTree(int n) : n(n), bit(n, 0) {}

    void add(int idx, ll val) {
        while (idx < n) {
            bit[idx] += val;
            idx = idx | (idx + 1);
        }
    }

    ll prefixSum(int idx) const {
        ll res = 0;
        while (idx >= 0) {
            res += bit[idx];
            idx = (idx & (idx + 1)) - 1;
        }
        return res;
    }

    ll rangeSum(int l, int r) const {
        if (l > r) return 0;
        return prefixSum(r) - prefixSum(l - 1);
    }
};

void solve() {
    int n;
    cin >> n;

    vector<ll> color(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Euler tour (tin, tout)
    vector<int> tin(n + 1), tout(n + 1);
    int timer = 0;

    function<void(int, int)> dfs = [&](int node, int parent) {
        tin[node] = timer++;
        for (int nxt : adj[node]) {
            if (nxt != parent) {
                dfs(nxt, node);
            }
        }
        tout[node] = timer;
    };

    dfs(1, 0);

    // Nodes grouped by color
    vector<vector<int>> nodesByColor(n + 1);
    for (int i = 1; i <= n; i++) {
        nodesByColor[color[i]].push_back(i);
    }

    FenwickTree ft(n);
    ll activeCount = 0;

    for (int c = n; c >= 1; c--) {
        for (int node : nodesByColor[c]) {
            if (ft.rangeSum(tin[node], tout[node] - 1) != activeCount) {
                cout << node << '\n';
                return;
            }
        }

        for (int node : nodesByColor[c]) {
            ft.add(tin[node], 1);
            activeCount++;
        }
    }

    cout << 0 << '\n';
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