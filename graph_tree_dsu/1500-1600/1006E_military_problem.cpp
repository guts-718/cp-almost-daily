#include <bits/stdc++.h>
using namespace std;

vector<int>mp;
int i;
int dfs(int node,int par,vector<int>adj[],vector<int>&sz,vector<int>&path){
    int cur=1;
    path.push_back(node);
    mp[node]=i++;
    for(auto x:adj[node]){
        if(x==par)continue;
        cur+=dfs(x,node,adj,sz,path);
        
    }
    sz[node]=cur;
    return cur;
}
int main() {
	// your code goes here
	int n,q;
	cin>>n>>q;
	vector<int>adj[n];
	vector<int>sz(n),path;
	for(int i=1;i<=n-1;i++){
	    int x;
	    cin>>x;x--;
	    adj[i].push_back(x);
	    adj[x].push_back(i);
	}

    mp.resize(n,0);
    i=0;
    dfs(0,-1,adj,sz,path);
    while(q--){
        int u,k;
        cin>>u>>k;
        u--;
        int idx=mp[u];
        int size=sz[u];
        if(size<k)cout<<-1<<endl;
        else cout<<path[idx+k-1]+1<<endl;
    }
}
