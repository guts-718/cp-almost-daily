#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--; 
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int leafCount = 0;

    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            leafCount++;
        }
    }

    cout<<fixed<<setprecision(10)<<(2.0 * k) / leafCount << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}




   <<ans<<endl;
}