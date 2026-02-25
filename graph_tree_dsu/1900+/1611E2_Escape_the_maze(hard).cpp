#include <bits/stdc++.h>
using namespace std;
int cnt=0;
void dfs(int node,int par,vector<int>adj[],int dis,vector<int>&dist){
     if(dis>=dist[node]){
        cnt++;
        return;
    }
    if(node!=0 && adj[node].size()==1){
        cnt=-2e7;
        return;
    }
   
    for(auto x:adj[node]){
        if(x==par)continue;
        dfs(x,node,adj,dis+1,dist);
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
        cnt=0;
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
	    dfs(0,-1,adj,0,dist);
	    if(cnt<0){
	        cout<<-1<<endl;
	    }else cout<<cnt<<endl;
	  
	  
	}

}
