#include <bits/stdc++.h>
#define int long long
using namespace std;

int mod=1e9+7;
int n;

int helper(vector<int>&a,vector<int>&b,int d,int i,vector<vector<int>>&dp){
    if(d==n){
        return 1;
        
    }
    if(d>n)return 0;
    if(dp[d][i]!=-1)return dp[d][i];
    int cur=0;
    int m=a.size();
    
    for(int j=0;j<m;j++){
        int p=helper(a,b,d+1,j,dp);
        p%=mod;
        cur+=(a[i]*b[j]*p)%mod;
        cur%=mod;
        cur+=(a[i]*a[j]*p)%mod;
        cur%=mod;
        cur+=(b[i]*a[j]*p)%mod;
        cur%=mod;
    }
    return dp[d][i]= cur%mod;
    
}


int32_t main() {
	// your code goes here
	int t=1;
	//cin>>t;
	while(t--){
	  int m;
	  cin>>m>>n;
	  vector<int>a(m),b(m);
	  for(int i=0;i<m;i++)cin>>a[i];
	  for(int i=0;i<m;i++)cin>>b[i];
	  vector<vector<int>>dp(n+5,vector<int>(m+5,-1));
// 	  cout<<a[0]*helper(a,b,1,1)+b[0]*helper(a,b,0,1)<<endl;
      cout<<helper(a,b,0,0,dp)<<endl;
	    
	}

}
