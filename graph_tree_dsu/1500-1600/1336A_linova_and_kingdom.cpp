#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

vector<int> g[N];
int n, k;
int dep[N], sz[N], val[N];

int dfs(int u, int p) {
    dep[u] = dep[p] + 1;
    sz[u] = 1;

    for (int v : g[u]) {
        if (v == p) continue;
        sz[u] += dfs(v, u);
    }

    val[u] = sz[u] - dep[u];
    return sz[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    nth_element(val + 1, val + n - k, val + n + 1, greater<int>());

    long long ans = 0;
    for (int i = 1; i <= n - k; i++)
        ans += val[i];

    cout << ans << "\n";

    return 0;
}