#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 4e18;

int helper(vector<int>&a,int ind,int k,int cnt){
    if(ind>=a.size()){
        return 0;
    }
    int cur=0;
    cur=helper(a,ind+1,k,cnt);
    if(cnt<2){
    int nxt=upper_bound(a.begin(),a.end(),a[ind]+k)-a.begin();
    nxt--;
    if(nxt<a.size() && a[nxt]-a[ind]<=k){
        cur=max(cur,(nxt-ind+1)+helper(a,nxt+1,k,cnt+1));
    }
    }
    return cur;
    
    
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
       int n,k;
       cin>>n>>k;
       vector<int>a(n),b(n);
       for(auto &x:a)cin>>x;
       for(auto &x:b)cin>>x;
       sort(a.begin(),a.end());
       vector<vector<int>>dp(n+5,vector<int>(3,0));
       for(int i=n-1;i>=0;i--){
           for(int j=0;j<=2;j++){
                int cur=dp[i+1][j];
                if(j<2){
                int nxt=upper_bound(a.begin(),a.end(),a[i]+k)-a.begin();
                nxt--;
                if(nxt<a.size() && a[nxt]-a[i]<=k){
                cur=max(cur,(nxt-i+1)+dp[nxt+1][j+1]);
                }
                dp[i][j]=cur;
            }
           }
           
           
           
       }
       cout<<dp[0][0]<<endl;
      // cout<<helper(a,0,k,0)<<endl;
    }

    return 0;
}
