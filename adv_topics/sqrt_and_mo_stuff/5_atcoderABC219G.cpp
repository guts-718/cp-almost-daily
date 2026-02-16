// didn't get AC - 39/40

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
   int n,m,q;
   cin>>n>>m>>q;
   vector<int>adj[n];
   vector<pair<int,int>>arr(n);
   
   for(int i=0;i<m;i++){
       int u,v;
       cin>>u>>v;
       u--;v--;
       adj[u].push_back(v);
       adj[v].push_back(u);
   }
   vector<int>isheavy(n+2,0);
   int block=sqrt(2*m);
   for(int i=0;i<n;i++){
       if(adj[i].size()>=block)isheavy[i]=1;
       arr[i]={i,-1};
   }
   vector<int>heavy_adj[n];
   for(int i=0;i<n;i++){
       for(auto x:adj[i]){
           if(isheavy[x])heavy_adj[i].push_back(x);
       }
   }
   vector<int>last(n+1,-1);
   for(int i=0;i<q;i++){
       int x;
       cin>>x;
       x--;
       last[x]=i;
       if(!isheavy[x]){
           int col=arr[x].first,tim=arr[x].second;
           
           for(auto y:heavy_adj[x]){
               
               if(arr[y].second>tim && last[y]>=arr[y].second){
                   tim=arr[y].second;;
                   col=arr[y].first;
               }
           }
           for(auto y:adj[x]){
              if(arr[y].first!=col) arr[y].second=i;
               arr[y].first=col;
               
           }
           arr[x].first=col;
           arr[x].second=i;
       }else{
           int col=arr[x].first,tim=arr[x].second;
           
           for(auto y:heavy_adj[x]){
               
               if(arr[y].second>tim && last[y]>=arr[y].second){
                   tim=arr[y].second;;
                   col=arr[y].first;
               }
           }
           for(auto y:heavy_adj[x]){
               if(arr[y].first!=col) arr[y].second=i;
                arr[y].first=col;
              
           }
           arr[x].first=col;
           arr[x].second=i;
       
      
   }
}


    for(int i=0;i<n;i++){
           if(!isheavy[i]){
               int col=arr[i].first,tim=arr[i].second;
           
               for(auto y:heavy_adj[i]){
                   
                   if(arr[y].second>tim  && last[y]>=arr[y].second){
                       tim=arr[y].second;;
                       col=arr[y].first;
                   }
               }
               arr[i].first=col;
               arr[i].second=tim;
           }
       }
       for(auto x:arr)cout<<x.first+1<<" ";
       
       cout<<endl;
}

