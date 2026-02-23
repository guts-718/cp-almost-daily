#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	   int n,k;
	   cin>>n>>k;
	   vector<int>a(n);
	   for(auto &x:a)cin>>x;
	   vector<int>indegree(n,0);
	   vector<int>cost(n,2e9);
	   for(int i=0;i<k;i++){
	       int x;
	       cin>>x;
	       x--;
	       a[x]=0;
	   }
	   vector<int>adj[n];
	   for(int i=0;i<n;i++){
	       int m;
	       cin>>m;
	       for(int j=0;j<m;j++){
	           int x;
	           cin>>x;
	           adj[x-1].push_back(i);
	           indegree[i]++;
	       }
	   }
	   queue<pair<int,int>>q;
	   vector<int>dp(n,0);
	  for(int i=0;i<n;i++){
	       if(indegree[i]==0){
	           q.push({i,a[i]});
	           dp[i]=a[i];
	   }
	   }
	   
	   while(!q.empty()){
	       auto it=q.front();
	       int node=it.first;
	       int cst=it.second;
	       q.pop();
	       for(auto x:adj[node]){
	           indegree[x]--;
	           dp[x]+=cst;
	           if(indegree[x]==0){
	             
	               dp[x]=min(dp[x],a[x]);
	               q.push({x,dp[x]});
	           }
	       }
	       
	   }
	   for(auto x:dp){
	       cout<<x<<" ";
	   }
	   cout<<endl;
	   
	}

}
