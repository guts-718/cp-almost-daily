#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

int cnt=0;
int helper(int node,int par,vector<int>adj[]){
    int cur=1;
    for(auto x:adj[node]){
        if(x==par)continue;
        cur+=helper(x,node,adj);
        
    }
    if(cur%2==0){cnt++;return 0;}
    return cur;
}
int main() {
	int t=1;
	//cin>>t;
	while(t--){
	   int n;
	   cin>>n;
	   vector<int>adj[n];
	   for(int i=0;i<n-1;i++){
	       int u,v;
	       cin>>u>>v;
	       u--;v--;
	       adj[u].push_back(v);
	       adj[v].push_back(u);
	   }
	   cnt==0;
	   int ans=helper(0,-1,adj);
	   if(ans==0)cout<<cnt-1<<endl;
	   else cout<<-1<<endl;
	}
}