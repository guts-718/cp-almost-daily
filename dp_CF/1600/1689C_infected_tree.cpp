#include <bits/stdc++.h>
using namespace std;

vector<int> sz;
vector<int> dp;

int dfs_size(int u, int p, vector<vector<int>>& adj) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        sz[u] += dfs_size(v, u, adj);
    }
    return sz[u];
}

void dfs_dp(int u, int p, vector<vector<int>>& adj) {

    vector<int> ch;
    for (int v : adj[u])
        if (v != p)
            ch.push_back(v);

    if (ch.empty()) {
        dp[u] = 0;
        return;
    }

    for (int v : ch)
        dfs_dp(v, u, adj);

    if (ch.size() == 1) {
        int c = ch[0];
        dp[u] = max(0, sz[c] - 1);
        return;
    }

    int a = ch[0];
    int b = ch[1];

    int option1 = max(0, sz[a] - 1) + dp[b];
    int option2 = max(0, sz[b] - 1) + dp[a];

    dp[u] = max(option1, option2);
}

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        sz.assign(n, 0);
        dp.assign(n, 0);

        dfs_size(0, -1, adj);
        dfs_dp(0, -1, adj);

        cout << dp[0] << "\n";
    }
}
