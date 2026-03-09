
#include <bits/stdc++.h>
using namespace std;
vector<int>color;
int red,blue;
int ans;
int helper(int node,int par,vector<int>adj[],int col){
    int r=0;
    if(color[node]==col){
        r++;
    }else if(color[node]!=0 && color[node]!=col){
        r=-1e5;
    }
    for(auto x:adj[node]){
        if(x==par)continue;
        r+=helper(x,node,adj,col);
    }
    if((col==1 && r==red) || (col==2 && r==blue)){
        ans++;
    }
    // cout<<node+1<<" "<<r<<" "<<red<<" "<<ans<<endl;
    return r;
}

int main() {
   int n,m;
   cin>>n;
   vector<int>adj[n];
   vector<pair<int,int>>edge;
   
   color.resize(n);
   red=0,blue=0;
   for(int i=0;i<n;i++){
       cin>>color[i];
       if(color[i]==1)red++;
       if(color[i]==2)blue++;
   }
   for(int i=0;i<n-1;i++){
       int x,y;
       cin>>x>>y;
       x--;y--;
       adj[x].push_back(y);
       adj[y].push_back(x);   
       
   }
   ans=0;
   helper(0,-1,adj,1);
   helper(0,-1,adj,2);
   cout<<ans<<endl;
}