#include<bits/stdc++.h>
using namespace std;


int help(int node,int par,vector<int>adj[],vector<int>&cost){
    int m1=0,m2=0;
    for(auto x:adj[node]){
        if(x==par)continue;
        int xo=help(x,node,adj,cost);
        if(xo>=m1){
            m2=m1;
            m1=xo;
        }else if(xo>=m2)m2=xo;
    }
    ans=max(ans,m1+m2+cost[node]);
    return cost[node]+m1;
}
int main(){
    int q;
    int m;
    cin>>q>>m;
    vector<int>indegree(n);
    vector<int>Adj[n];
    for(int i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        x--;y--;
        indegree[x]++;
        indegree[y]++;
        adj[x].push_back(y);
        adj[y].push_bcak(x);
    }

    queue<int>q;
    for(int i=0;i<n;i++){
        if(indegree[i]==0)q.push(i);
    }
    vector<int>topo;
    while(!q.empty()){
        int nd=q.front();
        q.pop();
        for(auto x:adj[nd]){
            indegree[x]--;
            if(indegree[x]==0)q.push(x);
        }
    }
    int r;
    cin>>r;
    vector<int>dp(n,0);
    dp[r]=1;
    for(auto x:topo){
        for(auto y:adj[x]){
            dp[y]*=dp[x];
            dp[y]%=mod;
        }
    }



}

vector<int>ans;
void topo(int node,int par,vector<int>adj[]){
    for(auto x:adj[node]){
        if(x==par)continue;
        topo(x,node,adj);
    }
    ans.push_back(node);
}

class DSU{
    public:
    vector<int>parent;
    vector<int>size;
    int n;
    DSU(int m){
        n=m;
        parent.resize(n,0);
        size.resize(n,1);
        for(int i=0;i<n;i++)parent[i]=i;

    }

    int findUpar(int a){
        if(parent[a]==a)return a;
        return parent[a]=findUpar(parent[a]);
    
    int join(int u,int v){
        int pu=findUpar(u);
        int pv=findUpar(v);
        if(pu==pr)return 0;
        if(size[pu]>size[pu]){
            size[pu]+=size[pv];
            parent[pv]=pu;
        }else{
            size[pv]+=size[pu];
            prent[pu]=pv;
        }
        return 1;
    }
};

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        vector<vector<int>>edges;
        for(int i=0;i<m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            u--;v--;
            edges.push_back({w,u,v});

        }
        DSU dsu(n);
        sort(edges.begin(),edges.end());
        for(auto x:edges){
            int w=x[0],u=x[1],v=x[2];
            if(dsu.findUpar(x)!=dsu.findUpar(v)){
                ans+=w;
                dsu.join(u,v);
            }
        }
        cout<<ans<<endl;
    }
}