#include <bits/stdc++.h>
using namespace std;

static const long long INF = 1e18;

bool ok(const vector<int>& p,
        const vector<int>& c,
        int fp, int fc) {
    int n = p.size();
    for (int j = 0; j < n; j++) {
        if (p[j] + fp == c[j] + fc) return false;
    }
    return true;
}

long long solve(const vector<vector<int>>& g,
                const vector<int>& cost) {

    int n = g.size();
    vector<vector<long long>> dp(n, vector<long long>(2, INF));

    dp[0][0] = 0;
    dp[0][1] = cost[0];

    for (int i = 1; i < n; i++) {
        for (int f = 0; f <= 1; f++) {
            for (int pf = 0; pf <= 1; pf++) {
                if (ok(g[i-1], g[i], pf, f)) {
                    dp[i][f] = min(dp[i][f],
                                   dp[i-1][pf] + (f ? cost[i] : 0));
                }
            }
        }
    }

    return min(dp[n-1][0], dp[n-1][1]);
}

void trans(vector<vector<int>>& g) {
    int n = g.size();
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            swap(g[i][j], g[j][i]);
}

void run() {
    int n;
    cin >> n;

    vector<vector<int>> g(n, vector<int>(n));
    for (auto& r : g)
        for (int& x : r)
            cin >> x;

    vector<int> a(n), b(n);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;

    long long x = solve(g, a);
    trans(g);
    long long y = solve(g, b);

    long long ans = x + y;
    cout << (ans >= INF ? -1 : ans) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) run();
    return 0;
}
