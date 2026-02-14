#include <bits/stdc++.h>
using namespace std;
int maxd;
void dfs(int node,int parent,vector<int>adj[],int dep,map<int,int>&mp){
    mp[dep]++;
    maxd=max(maxd,mp[dep]);
    for(auto x:adj[node]){
        if(x==parent)continue;;
        dfs(x,node,adj,dep+1,mp);
    }
    
}
int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n;
	    cin>>n;
	    vector<int>adj[n];
	    maxd=0;
	    for(int i=0;i<n-1;i++){
	        int u,v;cin>>u>>v;u--;v--;
	        adj[u].push_back(v);adj[v].push_back(u);
	    }
	    map<int,int>mp;
	    int f=0;
	    dfs(0,-1,adj,1,mp);
	    for(int i=0;i<n;i++){
	        if(i==0){
	            if(adj[i].size()==maxd){
	                f=1;
	            }
	        }else if(adj[i].size()==maxd+1)f=1;
	    }
	    if(f)maxd++;
	    cout<<maxd<<endl;
	    
	    
	}

}
