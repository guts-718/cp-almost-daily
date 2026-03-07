#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,k;
    cin>>n>>m>>k;

    vector<vector<pair<int,int>>> adj(n);
    map<pair<int,int>,int> mp;

    for(int i=0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;
        x--; y--;

        mp[{x,y}] = i;
        mp[{y,x}] = i;

        adj[x].push_back({y,w});
        adj[y].push_back({x,w});
    }

    vector<int> dist(n,LLONG_MAX);
    vector<int> parent(n,-1);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    pq.push({0,0});
    dist[0]=0;

    // FULL DIJKSTRA
    while(!pq.empty()){
        auto [cost,node] = pq.top();
        pq.pop();

        if(cost>dist[node]) continue;

        for(auto [to,w]:adj[node]){
            if(dist[to] > cost + w){
                dist[to] = cost + w;
                parent[to] = node;
                pq.push({dist[to],to});
            }
        }
    }

    // build shortest path tree
    vector<vector<int>> tree(n);

    for(int i=1;i<n;i++){
        if(parent[i]!=-1){
            tree[parent[i]].push_back(i);
        }
    }

    // BFS on tree
    queue<int> q;
    q.push(0);

    vector<pair<int,int>> ans;

    while(!q.empty() && ans.size()<k){
        int node=q.front();
        q.pop();

        for(auto x:tree[node]){
            ans.push_back({node,x});
            q.push(x);
            if(ans.size()==k) break;
        }
    }

    cout<<ans.size()<<"\n";

    for(auto [u,v]:ans){
        cout<<mp[{u,v}]+1<<" ";
    }

    cout<<"\n";
}