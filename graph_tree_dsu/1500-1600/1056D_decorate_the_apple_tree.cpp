#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

int cnt=0;
vector<vector<int>>dp;
vector<int> helper(int node,int par,vector<int>adj[]){
    vector<int>cur={0,1,node};
    int f=0;
    for(auto x:adj[node]){
        if(x==par)continue;
        f=1;;
        auto y=helper(x,node,adj);
        cur[0]+=y[0];
        cur[1]+=y[1];
        
        
    }
    if(f==0)cur[0]++;
    dp[node]=cur;
    return cur;

}
int main() {
	int t=1;
	//cin>>t;
	while(t--){
	   int n;
	   cin>>n;
	   vector<int>adj[n];
	   for(int i=1;i<=n-1;i++){
	       int u,v;
	       cin>>u;
	       u--;;
	       adj[u].push_back(i);
	       adj[i].push_back(u);
	   }
	   dp.assign(n,vector<int>(3));
	   helper(0,-1,adj);
	   sort(dp.begin(),dp.end());
	   adj[0].push_back(-1);
	   int j=0;
	   int cl=0;
	   int ans=1;
	   set<int>st;
	   st.insert(1);
	   int pp=1;
	   for(int i=1;i<=n;i++){
	       if(dp[j][0]==1){
	           cout<<1<<" ";
	           j++;
	           cl++;
	           continue;
	       }else{
	           int leaf=dp[j][0];
	           while(st.size()<leaf){
	               st.insert(++pp);
	           }
	           cout<<st.size()<<" ";
	           j++;
	       }
	   }
	  
	}
}