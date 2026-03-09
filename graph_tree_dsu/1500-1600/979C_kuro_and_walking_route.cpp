#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

void dfs(int node,int y,int par,vector<vector<int>>&adj){
    parent[node]=par;
    for(auto x:adj[node]){
        if(x==par) continue;
        dfs(x,y,node,adj);
    }
}

int dfs2(int node,int par,vector<vector<int>>&adj,vector<int>&vis){
    int cnt=1;
    vis[node]=1;
    for(auto x:adj[node]){
        if(vis[x]) continue;
        cnt+=dfs2(x,node,adj,vis);
    }
    return cnt;
}

int main() {
	int t=1;
	//cin>>t;
	while(t--){
	    int n,x,y;
	    cin>>n>>x>>y;
	    x--; y--;

	    vector<vector<int>> adj(n);
	    for(int i=0;i<n-1;i++){
	        int u,v;
	        cin>>u>>v;
	        u--; v--;
	        adj[u].push_back(v);
	        adj[v].push_back(u);
	    }

        parent.assign(n,-1);
        vector<int> ans;

	    dfs(x,y,-1,adj);

	    int cur=y;
	    do{
	        ans.push_back(cur);
	        cur=parent[cur];
	    }while(cur!=x);
	    ans.push_back(x);

	    reverse(ans.begin(),ans.end());

	    vector<int> vis(n,0);
	    vis[x]=1;
	    vis[y]=1;

	    if(ans.size()>2){
	        vis[ans[1]]=1;
	        vis[ans[ans.size()-2]]=1;
	    }

	    int c0=dfs2(x,-1,adj,vis);
	    int c1=dfs2(y,-1,adj,vis);

	    long long sol=1LL*n*(n-1)-1LL*c1*c0;
	    cout<<sol<<endl;
	}
}