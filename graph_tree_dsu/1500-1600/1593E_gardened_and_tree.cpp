#include <bits/stdc++.h>
using namespace std;

int distv, maxd, node1, node2;
int n,k;
void dfs1(int node, int par, vector<vector<int>>& adj, int dis, vector<int>& parent) {
    if (dis > maxd) {
        maxd = dis;
        node1 = node;
    }
    parent[node] = par;
    for (auto x : adj[node]) {
        if (x == par) continue;
        dfs1(x, node, adj, dis + 1, parent);
    }
}

void dfs2(int node, int par, vector<vector<int>>& adj, int dis, vector<int>& parent) {
    if (dis > maxd) {
        maxd = dis;
        node1 = node;
        distv = dis;
    }
    parent[node] = par;
    for (auto x : adj[node]) {
        if (x == par) continue;
        dfs2(x, node, adj, dis + 1, parent);
    }
}

int help(vector<int>&leaf,int mid,vector<vector<int>>&adj,vector<int>&indegree){
       vector<int> dist(n, 0);
        vector<int> vis(n, 0);
        queue<pair<int,int>> q;
        vector<int>degree=indegree;
        for (auto x : leaf) {
        
                q.push({x,0});
                vis[x] = 1;
                degree[x]--;
            
        }

        int d = 0;

        while (q.size()) {
            int sz = q.size();
            while(sz--){
                auto [x,z] = q.front();
                q.pop();
                

                dist[x] = d;

                for (auto y : adj[x]) {
                    if(vis[y])continue;
                    degree[y]--;
                    if(degree[y]==1){
                        vis[y]=1;
                        q.push({y,d});
                    }
                    
                }
            }
            d++;
            
        }
        // cout<<"dist  ";
        // for(auto x:dist)cout<<x<<" ";
        // cout<<endl;
        int ansv = 0;
        for (auto x : dist) {
            if (x >= k) ansv++;
        }
        return ansv;

}
int main() {
    int t; 
    cin >> t;

    while (t--) {
        // int n, k;
        //string s;
        //cin >> s;
        cin >> n >> k;

        vector<vector<int>> adj(n);
        vector<int> leaf, indegree(n);

        for (int i = 0; i < n - 1; i++) {
            int a, b; 
            cin >> a >> b;
            a--; b--;

            indegree[a]++;
            indegree[b]++;

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        for (int i = 0; i < n; i++) {
            if (indegree[i] == 1) {
                leaf.push_back(i);
            }
        }

        distv = -1; maxd = -1; node1 = -1; node2 = -1;

        vector<int> par(n, -1);
        dfs1(0, -1, adj, 0, par);

        par.assign(n, -1);
        int end1 = node1;

        node1 = -1; maxd = -1; distv = -1; node2 = -1;

        dfs1(end1, -1, adj, 0, par);
        int end2 = node1;

        vector<int> ans;
        int node = end2;

        do {
            ans.push_back(node);
            node = par[node];
        } while (node != -1);
        // for(auto x:ans)cout<<x<<" ";
        // cout<<"diameter" <<endl;
        int mid1 = ans[ans.size() / 2];
        int mid2 = ans[(ans.size()-1)/2];
        // cout<<"mid 1 ... mid2 "<<mid1<<" "<<mid2<<endl;
        int ansx=min(help(leaf,mid1,adj,indegree),help(leaf,mid2,adj,indegree));
        cout<<ansx<<endl;

    }
}


