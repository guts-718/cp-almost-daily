#include <bits/stdc++.h>
using namespace std;
void dfs(int node,int par,vector<int>adj[],int dis,vector<int>&dista){
    dista[node]=dis;
    for(auto x:adj[node]){
        if(x==par)continue;
        dfs(x,node,adj,dis+1,dista);
    }
}
int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n,k;
	    cin>>n>>k;
	    vector<int>a(k);
	    for(auto &x:a){cin>>x;x--;}
	    vector<int>adj[n];

	    for(int i=0;i<n-1;i++){
	        int u,v;
	        cin>>u>>v;
	        u--;v--;
	        adj[u].push_back(v);
	        adj[v].push_back(u);
	        
	    }
	    vector<int>dist(n,1e7);
	    vector<int>dista(n,1e7);
        vector<int>vis(n,0);
	    dfs(0,-1,adj,0,dista);
	    queue<int>q;
	    for(auto x:a){q.push(x);vis[x]=1;}
	    int cur=0;
	    while(q.size()){
	        int sz=q.size();
	        while(sz--){
	            int nd=q.front();
	            q.pop();
	            dist[nd]=min(dist[nd],cur);
	            for(auto x:adj[nd]){
	                if(vis[x])continue;
	                q.push(x);
	                vis[x]=1;
	            }
	            
	           
	        }
	        cur++;

	    }
	    int f=0;
	    for(int i=1;i<n;i++){
	        if(adj[i].size()==1){
	            if(dista[i]<dist[i]){
	                f=1;
	                break;
	            }
	        }
	    }
	    if(f)cout<<"YES"<<endl;
	    else cout<<"NO"<<endl;
	}

}
