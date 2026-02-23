#include <bits/stdc++.h>
using namespace std;

int inf=2e9;
int ninf=-2e9;

int main(){
    int t; cin>>t;
    while(t--){
      int n;
      cin>>n;
      vector<int>adj[n];
      vector<vector<int>>ans(n,vector<int>(4));
      for(int i=0;i<n;i++){
          ans[i]={inf,ninf,inf,ninf};
      }
      ans[0]={1,0,1,0};
      int nd=1;
      for(int i=0;i<n;i++){
          char c;
          cin>>c;
          if(c=='+'){
              int u,x;
              cin>>u>>x;
              u--;
              adj[u].push_back(nd);
              int p,q,r,s;
              r=max(0,ans[u][2]+x);
              s=min(0,ans[u][3]+x);
              p=max(r,ans[u][0]);
              q=min(s,ans[u][1]);
              ans[nd]={p,q,r,s};
              nd++;
              
          }else{
              int u,v,k;
              cin>>u>>v>>k;
              u--;v--;
              if(ans[v][0]>=k && ans[v][1]<=k){
                  cout<<"YES"<<endl;
              }else cout<<"NO"<<endl;
          }
      }
      
    }
}