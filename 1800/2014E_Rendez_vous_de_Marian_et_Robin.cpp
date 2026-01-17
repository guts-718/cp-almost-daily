#include <bits/stdc++.h>
using namespace std;

static const long long INF = (long long)1e18;

struct State {
    int u, o;
    long long d;
    bool operator<(const State& other) const {
        return d > other.d;
    }
};

int n, m, K;
vector<vector<pair<int,int>>> g;
vector<int> special;
vector<array<long long,2>> dist1, dist2;
vector<array<bool,2>> used;

void dijkstra(int src, vector<array<long long,2>>& dist) {
    for (int i = 1; i <= n; i++) {
        dist[i][0] = dist[i][1] = INF;
        used[i][0] = used[i][1] = false;
    }

    priority_queue<State> pq;
    dist[src][special[src]] = 0;
    pq.push({src, special[src], 0});

    while (!pq.empty()) {
        auto [u, o, d] = pq.top();
        pq.pop();
        if (used[u][o]) continue;
        used[u][o] = true;

        for (auto [v, w] : g[u]) {
            int no = o | special[v];
            long long nd = d + (o ? w / 2 : w);
            if (nd < dist[v][no]) {
                dist[v][no] = nd;
                pq.push({v, no, nd});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> K;

        g.assign(n + 1, {});
        special.assign(n + 1, 0);
        dist1.assign(n + 1, {INF, INF});
        dist2.assign(n + 1, {INF, INF});
        used.assign(n + 1, {false, false});

        for (int i = 0; i < K; i++) {
            int x;
            cin >> x;
            special[x] = 1;
        }

        for (int i = 0; i < m; i++) {
            int u, v, d;
            cin >> u >> v >> d;
            g[u].push_back({v, d});
            g[v].push_back({u, d});
        }

        dijkstra(1, dist1);
        dijkstra(n, dist2);

        long long ans = INF;
        for (int i = 1; i <= n; i++) {
            long long a = min(dist1[i][0], dist1[i][1]);
            long long b = min(dist2[i][0], dist2[i][1]);
            ans = min(ans, max(a, b));
        }

        cout << (ans >= INF ? -1 : ans) << '\n';
    }
    return 0;
}
