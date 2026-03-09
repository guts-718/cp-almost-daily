
#include <bits/stdc++.h>
using namespace std;
const int mxn = 1e5 + 10;
int par[mxn];

int find(int x) {
   if (par[x] == -1)
      par[x] = x;
   if (par[x] == x)
      return x;
   return par[x] = find(par[x]);
}
bool helper(int node,int par,vector<int>adj[],int col,vector<int>&color){
    color[node]=col;
    for(auto x:adj[node]){
        if(x==par)continue;
        if(color[x]==col)return true;
        if(helper(x,node,adj,!col,color))return true;
    }
    return false;
}

int main() {
   int n,m;
   cin>>n>>m;
   vector<int>adj[n];
   vector<pair<int,int>>edge;
   for(int i=0;i<m;i++){
       int x,y;
       cin>>x>>y;
       x--;y--;
       edge.push_back({x,y});
       adj[x].push_back(y);
       adj[y].push_back(x);   
       
   }
   vector<int>color(n,-1);
   bool a1=helper(0,-1,adj,0,color);
   if(a1){
       cout<<"NO"<<endl;
   }else{
       cout<<"YES"<<endl;
       for(auto x:edge){
           if(color[x.first])cout<<"1";
           else cout<<"0";
       }
   }
}