
#include <bits/stdc++.h>
using namespace std;



int main() {
   int n,m;
   cin>>n>>m;
   vector<int>adj[n];

   for(int i=0;i<m;i++){
       int x,y;
       cin>>x>>y;
       x--;y--;
       adj[x].push_back(y);
       adj[y].push_back(x);   
       
   }
    priority_queue<int>pq;
    pq.push(0);
    vector<int>vis(n,0);
    vis[0]=1;
    vector<int>ans;
    while(pq.size()>0){
        int nd=abs(pq.top());
        pq.pop();
        ans.push_back(nd);
        for(auto x:adj[nd]){
            if(vis[x])continue;
            vis[x]=1;
            pq.push(-1*x);
        }
    }
    for(auto x:ans)cout<<x+1<<" ";
    cout<<endl;
}