#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;

        vector<int> b(n+1,0), p(n+1,0);
        vector<vector<int>> adj(n+1);

        for(int i = 1; i <= n; i++){
            cin >> b[i];
            if(b[i]==i)continue;
            adj[b[i]].push_back(i);
        }

        for(int i = 1; i <= n; i++)
            cin >> p[i];

        if(b[p[1]] != p[1]){
            cout << -1 << endl;
            continue;
        }

        int root = p[1];

        vector<int> dist(n+1, 0), vis(n+1, 0);
        unordered_set<int> st;

        dist[root] = 0;
        vis[root] = 1;
        st.insert(root);

        int idx = 1;
        bool ok = true;
        int maxi=0;
        while(idx <= n){
            if(st.find(p[idx]) == st.end()){
                ok = false;
                break;
            }

            int node = p[idx];
            st.erase(node);
            dist[node] = (maxi++);
            for(auto x : adj[node]){
                if(!vis[x]){
                    vis[x] = 1;
                    st.insert(x);
                }
            }

            idx++;
        }

        if(!ok){
            cout << -1 << endl;
        } else {
            for(int i=1;i<=n;i++){
                cout<<dist[i]-dist[b[i]]<<" ";
            }
            // for(int i = 1; i <= n; i++)
            //     cout << dist[i] << " ";
            cout << endl;
        }
    }
}