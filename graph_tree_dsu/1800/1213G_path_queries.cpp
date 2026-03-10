#include <bits/stdc++.h>
#define int long long
using namespace std;

class DSU{
    public:
    vector<int>size;
    vector<int>parent;
    multiset<int>st;
    int sol=0;
    DSU(int n){
        size.resize(n,0);
        parent.resize(n,0);
        for(int i=0;i<n;i++)size[i]=1;
        for(int i=0;i<n;i++)parent[i]=i;
        for(int i=0;i<n;i++)st.insert(1);
    }
    int findUpar(int x){
        if(x==parent[x])return x;
        return parent[x]=findUpar(parent[x]);
    }
    
    int join(int u,int v){
        int pu=findUpar(u);
        int pv=findUpar(v);
        if(pu==pv)return 0;
        st.erase(st.find(size[pu]));
        st.erase(st.find(size[pv]));
        int su=size[pu],sv=size[pv];
        sol-=((su*(su-1))/2);
        sol-=((sv*(sv-1))/2);
        int sm=su+sv;
        st.insert(sm);
        sol+=((sm)*(sm-1))/2;
        if(size[pu]>size[pv]){
            size[pu]+=size[pv];
            parent[pv]=pu;
        }else{
            size[pv]+=size[pu];
            parent[pu]=pv;
        }
        return 1;
    }
    
};
int32_t main() {
	// your code goes here
    int t=1;
    //cin>>t;
    while(t--){
        int n,q;
        cin>>n>>q;
        vector<vector<int>>edges;
        for(int i=0;i<n-1;i++){
           int u,v,w;
           cin>>u>>v>>w;u--;v--;
           edges.push_back({w,u,v});
        }
        
        sort(edges.begin(),edges.end());
        int j=0;
        vector<vector<int>>query(q,vector<int>(2));
        int i=0;
        while(q--){
            cin>>query[i][0];
            query[i][1]=i;
            i++;
        }
        DSU dsu(n);
        j=0;
        vector<int>ans(query.size(),0);
        sort(query.begin(),query.end());
        for(int i=0;i<query.size();i++){
            while(j<edges.size() && edges[j][0]<=query[i][0]){
                dsu.join(edges[j][1],edges[j][2]);
                j++;
            }
            ans[query[i][1]]=dsu.sol;
        }
        for(auto x:ans)cout<<x<<" ";
        cout<<endl;
        
    }
}
