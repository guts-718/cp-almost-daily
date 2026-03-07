#include <bits/stdc++.h>
#define int long long
using namespace std;

class DSU{
public:
    vector<int> size;
    vector<int> parent;
    int n;

    DSU(int m){
        n = m;
        size.resize(n);
        parent.resize(n);
        for(int i=0;i<n;i++){
            size[i]=1;
            parent[i]=i;
        }
    }

    int findupar(int u){
        if(parent[u]==u) return u;
        return parent[u]=findupar(parent[u]);
    }

    int join(int u,int v){
        int pu=findupar(u);
        int pv=findupar(v);

        if(pu==pv) return 0;

        if(size[pu] > size[pv]){
            parent[pv]=pu;
            size[pu]+=size[pv];
        }else{
            parent[pu]=pv;
            size[pv]+=size[pu];
        }
        return 1;
    }
};

void solve(){
   int n;
   cin>>n;

   vector<int> a(n);
   int sm=0;

   for(auto &x:a){
       cin>>x;
       sm+=x;
   }

   if((sm/2) < n-1){
       cout<<"NO"<<endl;
       return;
   }

   vector<vector<int>> adj(n);

   vector<int> v,vv;

   for(int i=0;i<n;i++){
       if(a[i]>=2) v.push_back(i);
       else vv.push_back(i);
   }

   int dm=v.size()-1;

   for(int i=0;i+1<v.size();i++){
       adj[v[i]].push_back(v[i+1]);
       adj[v[i+1]].push_back(v[i]);
       a[v[i]]--;
       a[v[i+1]]--;
   }
   int k=0;
   if(vv.size()>=1 && v.size()>=1 && a[v[0]]>0){
       dm++;
       k++;
       adj[v[0]].push_back(vv[0]);
       adj[vv[0]].push_back(v[0]);
       a[v[0]]--;
       a[vv[0]]--;
   }

   if(vv.size()>=2 && v.size()>=2 && a[v.back()]>0){
       dm++;
       k++;
       adj[v.back()].push_back(vv[1]);
       adj[vv[1]].push_back(v.back());
       a[v.back()]--;
       a[vv[1]]--;
   }else if(vv.size()>=2 && v.size()==1 && a[v[0]]>0){
      dm++;
       k++;
       adj[v[0]].push_back(vv[1]);
       adj[vv[1]].push_back(v[0]);
       a[v[0]]--;
       a[vv[1]]--;
   }

   int j=0;

   for(int i=k;i<vv.size();i++){
       if(a[vv[i]]==0)continue;
       while(j<v.size() && a[v[j]]==0) j++;
       if(j>=v.size())break;

       adj[v[j]].push_back(vv[i]);
       adj[vv[i]].push_back(v[j]);

       a[v[j]]--;
       a[vv[i]]--;
   }

   cout<<"YES "<<dm<<endl;
   vector<pair<int,int>>sol;
   for(int i=0;i<n;i++){
       for(auto x:adj[i]){
           if(x>i) sol.push_back({i+1,x+1});
           }
   }
   cout<<sol.size()<<endl;
   for(auto x:sol){
       cout<<x.first<<" "<<x.second<<endl;
   }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    while(t--){
        solve();
    }
}