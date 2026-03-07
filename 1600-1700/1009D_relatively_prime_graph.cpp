#include <bits/stdc++.h>
using namespace std;



int main() {
    int t=1; 
    //cin >> t;
    while (t--) {
      int n,m;
      cin>>n>>m;
      if(m<n-1){
          cout<<"Impossible"<<endl;
          continue;
      }
      vector<vector<int>>adj(n+1);
      int cnt=0;
      
      for(int i=2;i<=n;i++){
          cnt++;
          adj[1].push_back(i);
          adj[i].push_back(1);
      }
      
    //   while(cnt<m){
      for(int i=2;i<=n;i++){
          if(cnt==m)break;
          for(int j=i+1;j<=n;j++){
              if(__gcd(i,j)==1){
                  adj[i].push_back(j);
                  adj[j].push_back(i);
                  cnt++;
                  if(cnt==m){
                      break;
                  }
              }
              if(cnt==m)break;
          }
          if(cnt==m)break;
      }
      
      if(cnt==m){
          vector<pair<int,int>>ans;
          cout<<"Possible"<<endl;
          for(int i=1;i<=n;i++){
              for(auto x:adj[i]){
                  if(i<x)cout<<i<<" "<<x<<endl;
              }
          }
      }else cout<<"Impossible"<<endl;
      
      
      

    }
}