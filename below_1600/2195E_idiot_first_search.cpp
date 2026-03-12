#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll md=1000000007;
 
int main()
{
  int t;cin>>t;
  while(t--)
  {
    ll n;cin>>n;
    vector<ll>L(n),R(n);
    for(int i=0;i<n;i++)
    {
      cin>>L[i]>>R[i];
      L[i]--;R[i]--;
    }
    vector<ll>dp(n);
    auto dfs1=[&](auto dfs1,int x)->ll
    {
      if(L[x]==-1)return dp[x]=1;
      else return dp[x]=(dfs1(dfs1,L[x])+dfs1(dfs1,R[x])+3)%md;
    };
    dfs1(dfs1,0);
    auto dfs2=[&](auto dfs2,int x)->void
    {
      if(L[x]==-1)return;
      else
      {
        dp[L[x]]=(dp[L[x]]+dp[x])%md;
        dp[R[x]]=(dp[R[x]]+dp[x])%md;
        dfs2(dfs2,L[x]);
        dfs2(dfs2,R[x]);
      }
    };
    dfs2(dfs2,0);
    for(int i=0;i<n;i++)cout<<dp[i]<<" \n"[i+1==n];
  }
}