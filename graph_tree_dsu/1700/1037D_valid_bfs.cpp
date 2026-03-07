#include <bits/stdc++.h>
using namespace std;



int main() {
    int t=1; 
    //cin >> t;
    while (t--) {
      int n;
      cin>>n;
      vector<int>adj[n];
      for(int i=0;i<n-1;i++){
          int x,y;
          cin>>x>>y;
          x--;y--;
          adj[x].push_back(y);
          adj[y].push_back(x);
      }
      vector<int>bfs(n);
      for(auto &x:bfs){cin>>x;x--;}
      map<int,int>mp;
      int i=1;
      for(auto x:bfs){
          mp[x]=i++;
      }
      queue<int>q;
      q.push(0);
      vector<int>ans;
      vector<int>vis(n,0);
      vis[0]=1;
      while(!q.empty()){
          int nd=q.front();
          q.pop();
          ans.push_back(nd);
          set<pair<int,int>>st;
          for(auto x:adj[nd]){
              if(vis[x])continue;
              vis[x]=1;
              st.insert({mp[x],x});
          }
          for(auto x:st){
              q.push(x.second);
          }
          st.clear();
          
      }
      if(ans==bfs)cout<<"Yes"<<endl;
      else cout<<"No"<<endl;

    }
}