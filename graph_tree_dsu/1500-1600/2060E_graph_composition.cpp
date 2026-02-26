#include <bits/stdc++.h>
using namespace std;

class DSU{
    private:
    vector<int>size;
    vector<int>parent;
    public:
    DSU(int n){
        size.resize(n,1);
        parent.resize(n,0);
        for(int i=0;i<n;i++)parent[i]=i;
    }
    int findUpar(int u){
        if(parent[u]==u)return u;
        return parent[u]=findUpar(parent[u]);
    }
    bool join(int u,int v){
        if(findUpar(u)==findUpar(v)){
            return false;
        }
        int pu=findUpar(u);
        int pv=findUpar(v);
        if(size[pv]>=size[pu]){
            parent[pu]=pv;
            size[pv]+=size[pu];
        }else{
            parent[pv]=pu;
            size[pu]+=size[pv];
        }
        return true;
    }
    
};

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n,m1,m2;
	    cin>>n>>m1>>m2;
	    vector<pair<int,int>>g1,g2;
	    DSU dsu1(n+1),dsu2(n+1);
	    for(int i=0;i<m1;i++){
	        int u,v;
	        cin>>u>>v;
	        u--;v--;
	        g1.push_back({u,v});
	        dsu1.join(u,v);
	        
	    }
	    for(int i=0;i<m2;i++){
	        int u,v;
	        cin>>u>>v;
	        u--;v--;
	        g2.push_back({u,v});
	        dsu2.join(u,v);
	        
	    }
	    int cnt=0;
	    int i=0;
	    vector<int>use(m1,1);
	    for(auto [a,b]:g1){
	        if(dsu2.findUpar(a)!=dsu2.findUpar(b)){
	            cnt++;
	            use[i]=0;
	        }
	        i++;
	    }
	    DSU dsu3(n);
	    for(int i=0;i<m1;i++){
	        if(use[i]){
	            dsu3.join(g1[i].first,g1[i].second);
	        }
	    }
	    for(auto [a,b]:g2){
	        if(dsu3.findUpar(a)!=dsu3.findUpar(b)){
	            cnt++;
	            dsu3.join(a,b);
	        }
	    }
	    cout<<cnt<<endl;
	    
	}

}
