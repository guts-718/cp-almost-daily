#include <bits/stdc++.h>
using namespace std;
#define int long long
int ans=0;
int dfs(int node,int par,vector<int>adj[],vector<pair<int,int>>&rg){
    int cur=0;
    int cst=0;
    for(auto x:adj[node]){
        if(x==par)continue;
        cst+=dfs(x,node,adj,rg);
        // cst+=rg[x].second;
    }
    if(cst>=rg[node].first){
        
        return min(cst,rg[node].second);
    }
    ans++;
    return rg[node].second;
}
int32_t main() {
	// your code goes here
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int>adj[n];
        for(int i=2;i<=n;i++){
            int p;
            cin>>p;
            p--;
            adj[p].push_back(i-1);
        }
        ans=0;
        vector<pair<int,int>>rg(n);
        for(int i=0;i<n;i++){
            int l,r;
            cin>>l>>r;
            rg[i]={l,r};
        }
        int sol=dfs(0,-1,adj,rg);
        cout<<ans<<endl;
    }
}
