
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