#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k, s;
    cin >> n >> m >> k >> s;

    vector<vector<int>> adj(n);
    vector<int> arr(n);
    vector<vector<int>> mp(k + 1);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        mp[arr[i]].push_back(i);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // vector<priority_queue<int>> v(n);
    vector<vector<int>>v(n);
    vector<int> vis(n, -1);

    for (int type = 1; type <= k; type++) {
        queue<int> q;

        for (int x : mp[type]) {
            q.push(x);
            vis[x] = type;
        }

        int dist = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                int x = q.front();
                q.pop();

                // v[x].push(dist);
                // if (v[x].size() > s) {
                //     v[x].pop();
                // }
                v[x].push_back(dist);

                for (int y : adj[x]) {
                    if (vis[y] == type) continue;
                    vis[y] = type;
                    q.push(y);
                }
            }

            dist++;
        }
    }

    for (int i = 0; i < n; i++) {
        int ans = 0;
        sort(v[i].begin(),v[i].end());
        for(int j=0;j<s;j++){ans+=v[i][j];}
        cout << ans << " ";
    }

    cout << endl;
}