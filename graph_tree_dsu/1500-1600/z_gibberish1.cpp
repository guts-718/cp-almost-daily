#include<bits/stdc++.h>
using namespace st;

int32_t main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int>adj[n];
        vector<int>indegree(n,0);
        for(int i=0;i<n;i++){
            int x,y;
            cin>>x>>y;
            x--;
            y--;
            indegree[x]++;
            indegree[y]++;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        queue<int>q;
        for(int i=0;i<n;i++){
            if(indegree[x]==0){
                q.push(x);
            }
        }
        vector<int>topo;
        while(q--){
            int nd=q.front();
            q.pop();
            topo.push_back(nd);
            for(auto x:adj[nd]){
                indegree[x]--;
                if(indegree[x]==0){
                    q.push(x);
                }
            }
        }
        vector<int>dp(n,0);
        int r=0;
        cin>>r;
        dp[r]=1;
        for(auto x:topo){
            for(auto y:adj[x]){
                dp[y]*=dp[x];
                dp[y]%=mod;
            }
        }
        cout<<dp[n]<<endl;


    }
}



int dfs(int node,int par,vector<int>adj[],vector<int>&cost){
    int m1=0,m2=0;
    int cur=0;
    for(auto x:adj[node]){
        if(x==par)continue;
        int op=dfs(x,node,adj,cost);
        if(op>=m1){
            m2=m1;
            m1=op;
        }else if(m2>=op){
            m2=op;

        }
    }
    ans=max(ans,cost[node]+m2+m1);
    return m1+cost[node];



}


int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int>adj[n];
        for(int i=0;i<n-1;i++){
            int x,y;
            cin>>x>>Y;
            x--;
            y--;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        vector<int>vis(n,0);

        for(int i=0;i<n;i++){
            if(!vis[i])dfs(i,-1,adj,cost);
        }
        cout<<ans<<endl;
    }
}