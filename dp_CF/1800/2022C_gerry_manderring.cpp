#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll rec(int i,int o,int n,string &s1,string &s2,vector<vector<int>> &dp){
    if(i==n) return 0;
    if(dp[i][o]!=-1) return dp[i][o];

    ll ans=0;
    int shift=o-1;
    int j=i;
    int k=i+shift;

    // take 3 block
    if(j+3<=n && k+3<=n){
        int w=0;
        int c1=(s1[j]=='A')+(s1[j+1]=='A')+(s1[j+2]=='A');
        int c2=(s2[k]=='A')+(s2[k+1]=='A')+(s2[k+2]=='A');
        if(c1>1) w++;
        if(c2>1) w++;
        ans=max(ans, rec(i+3,o,n,s1,s2,dp)+w);
    }

    // left skew
    if(shift<0){
        int cnt=(s1[j]=='A')+(s2[k]=='A')+(s2[k+1]=='A');
        ans=max(ans, rec(i+1,1,n,s1,s2,dp)+(cnt>1));
    }

    // right skew
    else if(shift>0){
        int cnt=(s1[j]=='A')+(s1[j+1]=='A')+(s2[k]=='A');
        ans=max(ans, rec(i+2,1,n,s1,s2,dp)+(cnt>1));
    }

    // centered
    else{
        int cnt1=(s1[j]=='A')+(s1[j+1]=='A')+(s2[k]=='A');
        int cnt2=(s1[j]=='A')+(s2[k]=='A')+(s2[k+1]=='A');

        ans=max(ans, rec(i+2,0,n,s1,s2,dp)+(cnt1>1));
        ans=max(ans, rec(i+1,2,n,s1,s2,dp)+(cnt2>1));
    }

    return dp[i][o]=ans;
}

void solve(){
    int n;
    cin>>n;
    string s1,s2;
    cin>>s1>>s2;

    vector<vector<int>> dp(n,vector<int>(3,-1));
    cout<<rec(0,1,n,s1,s2,dp)<<"\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin>>t;
    while(t--) solve();
}