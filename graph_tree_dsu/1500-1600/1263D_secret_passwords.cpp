#include <bits/stdc++.h>
using namespace std;

class DSU{
    public:
    vector<int>parent;
    vector<int>size;
    DSU(int n){
        parent.resize(n);
        size.resize(n);
        for(int i=0;i<n;i++){
            parent[i]=i;
            size[i]=1;
        }
    }
    int findupar(int u){
        if(parent[u]==u)return u;
        return parent[u]=findupar(parent[u]);
        
    }
    
    int join(int u,int v){
        int pu=findupar(u);
        int pv=findupar(v);
        if(pu==pv)return 0;
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
int main() {
	// your code goes here
	int n;
	cin>>n;
	vector<string>v(n);
	for(int i=0;i<n;i++){
	    cin>>v[i];
	}
	DSU dsu(n+27);
	for(int i=0;i<n;i++){
	    for(auto x:v[i]){
	        dsu.join(x-'a',i+26);
	    }
	}
	unordered_set<int>st;
	for(int i=i;i<n;i++){
	    st.insert(dsu.findupar(i+26));
	}
	cout<<st.size()<<endl;
	

}
