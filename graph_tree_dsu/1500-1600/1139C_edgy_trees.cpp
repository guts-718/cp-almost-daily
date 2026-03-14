#include <bits/stdc++.h>
using namespace std;

int mod=1e9+7;
int dfs(int node,int par,vector<int>adj[],vector<int>&vis){
    vis[node]=1;
    int cur=1;
    for(auto x:adj[node]){
        if(x==par)continue;
        cur+=dfs(x,node,adj,vis);
    }
    return cur;
    
}
long long powr(long long a,long long b){
    long long ans=1;
    while(b){
        if(b&1)ans*=a;
        ans%=mod;
        a*=a;
        a%=mod;
        b/=2;
    }
    return ans;
}
int main() {
	// your code goes here
	int n,k;
	cin>>n>>k;
	vector<int>adj[n];
	for(int i=0;i<n-1;i++){
	    int u,v,w;
	    cin>>u>>v>>w;
	    u--;v--;
	    if(w==1)continue;
	    adj[u].push_back(v);
	    adj[v].push_back(u);
	}
	long long ans=0;
	vector<int>vis(n,0);
	for(int i=0;i<n;i++){
	    if(!vis[i]){
	        int cur=dfs(i,-1,adj,vis);
	        ans+=powr(cur,k);
	    }
	}
	long long p=powr(n,k);
	p=(p-ans+mod)%mod;
	cout<<p<<endl;

}
