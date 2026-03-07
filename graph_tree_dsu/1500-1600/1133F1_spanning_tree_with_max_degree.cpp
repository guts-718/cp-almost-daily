#include <bits/stdc++.h>
#define int long long
using namespace std;

class DSU{
public:
    vector<int> size;
    vector<int> parent;
    int n;

    DSU(int m){
        n = m;
        size.resize(n);
        parent.resize(n);
        for(int i=0;i<n;i++){
            size[i]=1;
            parent[i]=i;
        }
    }

    int findupar(int u){
        if(parent[u]==u) return u;
        return parent[u]=findupar(parent[u]);
    }

    int join(int u,int v){
        int pu=findupar(u);
        int pv=findupar(v);

        if(pu==pv) return 0;

        if(size[pu] > size[pv]){
            parent[pv]=pu;
            size[pu]+=size[pv];
        }else{
            parent[pu]=pv;
            size[pv]+=size[pu];
        }
        return 1;
    }
};

void solve(){
    int n,m;
    cin>>n>>m;

    vector<int> indegree(n,0);
    vector<pair<int,int>> edges;
    vector<vector<int>> adj(n);

    int maxi=-1, nd=0;

    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        x--; y--;

        edges.push_back({x,y});

        adj[x].push_back(y);
        adj[y].push_back(x);

        indegree[x]++;
        indegree[y]++;

        if(maxi < indegree[x]){
            maxi = indegree[x];
            nd = x;
        }

        if(maxi < indegree[y]){
            maxi = indegree[y];
            nd = y;
        }
    }

    DSU dsu(n);

    int cnt=1;
    vector<pair<int,int>> ans;

    for(auto x:adj[nd]){
        ans.push_back({x,nd});
        dsu.join(x,nd);
        cnt++;
    }

    for(auto x:edges){
        int u=x.first;
        int v=x.second;

        if(dsu.findupar(u)==dsu.findupar(v)) continue;

        if(dsu.join(u,v)){
            ans.push_back({u,v});
            cnt++;
        }
    }

    if(cnt==n){
        for(auto x:ans){
            cout<<x.first+1<<" "<<x.second+1<<"\n";
        }
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    //cin>>t;

    while(t--){
        solve();
    }
}

