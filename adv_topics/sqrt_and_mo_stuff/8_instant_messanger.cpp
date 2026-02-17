#include <bits/stdc++.h>
using namespace std;

struct nod{
    char c;
    int u;
    int v;
    nod(char _c,int _u,int _v=-1){
        c=_c;
        u=_u;
        v=_v;
    }
}; 

int main() {
	int n,m,q;
	cin>>n>>m>>q;

	vector<int>online(n,0);
	int o;
	cin>>o;
	for(int i=0;i<o;i++){ 
	    int x;
	    cin>>x;
	    x--;
	    online[x]=1;
	}

	vector<int>tdeg(n,0);
	vector<unordered_set<int>>adj(n);

	for(int i=0;i<m;i++){
	    int x,y;
	    cin>>x>>y;
	    x--;y--;
	    tdeg[x]++;
	    tdeg[y]++;
	    adj[x].insert(y);
	    adj[y].insert(x);
	}

	vector<nod>v;

	while(q--){
	    char c;
	    cin>>c;
	    if(c=='A' || c=='D'){
	        int u,vv; 
	        cin>>u>>vv;
	        u--;vv--;
	        tdeg[u]++;
	        tdeg[vv]++; 
	        v.push_back(nod(c,u,vv)); 
	    }else{
	        int u;
	        cin>>u;
	        u--;
	        tdeg[u]++;
	        v.push_back(nod(c,u,-1)); 
	    }
	} 


	vector<int>isheavy(n,0);
	for(int i=0;i<n;i++){
	    if(tdeg[i]>sqrt(m+q)){
	        isheavy[i]=1;
	    }
	}

	vector<int>ans(n,0);
	vector<unordered_set<int>>heavy_adj(n);

	for(int i=0;i<n;i++){
	    if(online[i] && !isheavy[i]){
	        for(auto x:adj[i]){
	            ans[x]++;
	        }
	    }
	    for(auto x:adj[i]){
	        if(isheavy[x]){
	            heavy_adj[i].insert(x);
	        }
	    }
	}
	


	for(auto x:v){
	    if(x.c=='O'){
	        if(isheavy[x.u]){
	        }else{
	            for(auto y:adj[x.u]){
	                ans[y]++;
	            }
	        }
	        online[x.u]=1; 
	    }
	    else if(x.c=='F'){
	        if(isheavy[x.u]){
	        }else{
	            for(auto y:adj[x.u]){
	                ans[y]--;
	            }
	        }
	        online[x.u]=0; 
	    }
	    else if(x.c=='A'){
	        adj[x.u].insert(x.v);
	        adj[x.v].insert(x.u);

	        if(online[x.u] && !isheavy[x.u]) ans[x.v]++;
	        if(online[x.v] && !isheavy[x.v]) ans[x.u]++;

	        if(isheavy[x.u]) heavy_adj[x.v].insert(x.u);
	        if(isheavy[x.v]) heavy_adj[x.u].insert(x.v);
	    }
	    else if(x.c=='D'){
	        adj[x.u].erase(x.v);
	        adj[x.v].erase(x.u);

	        if(online[x.u] && !isheavy[x.u]) ans[x.v]--;
	        if(online[x.v] && !isheavy[x.v]) ans[x.u]--;

	        if(isheavy[x.u]) heavy_adj[x.v].erase(x.u);
	        if(isheavy[x.v]) heavy_adj[x.u].erase(x.v);
	    }
	    else{
	        int node=x.u;
	        int sol=ans[node];
	        for(auto y:heavy_adj[node]){
	            if(online[y]) sol++;
	        }
	        cout<<sol<<endl;
	    }
	}
}
