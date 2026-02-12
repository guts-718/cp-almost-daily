#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 4e18;

int helper(vector<int>&a,int ind,int f,vector<vector<int>>&dp){
    if(ind>=a.size())return 0;
    int cur=2e6;
    if(f){
        int cnt=0;
        if(a[ind]==1)cnt++;
        cur=min(cur,cnt+helper(a,ind+1,!f,dp));
        if(ind+1<a.size()){
            if(a[ind+1]==1)cnt++;
            cur=min(cur,cnt+helper(a,ind+2,!f,dp));
        }
        
    }else{
        cur=min(cur,helper(a,ind+1,!f,dp));
        if(ind+1<a.size())cur=min(cur,helper(a,ind+2,!f,dp));
    }
    return dp[ind][f]=cur;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
       int n;
       cin>>n;
       vector<int>a(n);
       for(int i=0;i<n;i++)cin>>a[i];
      
       vector<vector<int>>dp(n+5,vector<int>(2,2e6));
       //cout<<helper(a,0,1,dp)<<endl;
      dp[n][0]=dp[n][1]=0;
      for(int i=n-1;i>=0;i--){
          int ind=i;
          for(int j=0;j<=1;j++){
              if(j){
                int cnt=0;
                if(a[ind]==1)cnt++;
                dp[i][j]=min(dp[i][j],cnt+dp[ind+1][!j]);
                if(ind+1<a.size()){
                        if(a[ind+1]==1)cnt++;
                        dp[i][j]=min(dp[i][j],cnt+dp[ind+2][!j]);
                    
                    }
                
            }else{
                dp[i][j]=min(dp[i][j],dp[ind+1][!j]);
                if(ind+1<a.size())dp[i][j]=min(dp[i][j],dp[ind+2][!j]);
            }
          }   
      }
      cout<<dp[0][1]<<endl;
    }

    return 0;
}
