#include <bits/stdc++.h>
using namespace std;

static const long long INF = 1e18;

void solve() {
    long long n, s1, s2;
    cin >> n >> s1 >> s2;
    s1--; 
    s2--;

    int m1;
    cin >> m1;

    vector<vector<int>> adj1(n), adj2(n);
    vector<pair<int,int>> edges1;
    set<pair<int,int>> edges2;

    for (int i = 0; i < m1; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (a > b) swap(a, b);
        adj1[a].push_back(b);
        adj1[b].push_back(a);
        edges1.push_back({a, b});
    }

    int m2;
    cin >> m2;
    for (int i = 0; i < m2; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (a > b) swap(a, b);
        adj2[a].push_back(b);
        adj2[b].push_back(a);
        edges2.insert({a, b});
    }

    vector<vector<long long>> dist(n, vector<long long>(n, INF));

    priority_queue<
        pair<long long, pair<int,int>>,
        vector<pair<long long, pair<int,int>>>,
        greater<>
    > pq;

    dist[s1][s2] = 0;
    pq.push({0, {s1, s2}});

    while (!pq.empty()) {
        auto [d, state] = pq.top();
        pq.pop();
        int x = state.first;
        int y = state.second;

        if (d != dist[x][y]) continue;

        for (int nx : adj1[x]) {
            for (int ny : adj2[y]) {
                long long nd = d + llabs(nx - ny);
                if (nd < dist[nx][ny]) {
                    dist[nx][ny] = nd;
                    pq.push({nd, {nx, ny}});
                }
            }
        }
    }

    long long ans = INF;
    for (auto &e : edges1) {
        if (edges2.count(e)) {
            int v = e.first;
            ans = min(ans, dist[v][v]);
        }
    }

    cout << (ans == INF ? -1 : ans) << '\n';
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
