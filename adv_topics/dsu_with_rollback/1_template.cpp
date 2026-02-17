/*
Normal DSU uses path compression, which destroys history.
Rollback DSU does NOT use path compression so that we can undo merges.
Instead it uses:
union by size (keeps tree shallow)
stack storing changes
*/
#include <bits/stdc++.h>
using namespace std;

struct RollbackDSU {
    int n, comps;
    vector<int> parent, sz;

    // stack of changes for rollback
    vector<pair<int,int>> history; 
    // stores (node, old_size_of_parent)

    RollbackDSU(int n) : n(n), comps(n) {
        parent.resize(n+1);
        sz.assign(n+1,1);
        for(int i=1;i<=n;i++) parent[i]=i;
    }

    int find(int x){
        while(x!=parent[x]) x=parent[x];
        return x;
    }

    bool unite(int a,int b){
        a=find(a);
        b=find(b);
        if(a==b){
            history.push_back({-1,-1}); // mark no merge
            return false;
        }
        if(sz[a]<sz[b]) swap(a,b);

        history.push_back({b, sz[a]});

        parent[b]=a;
        sz[a]+=sz[b];
        comps--;
        return true;
    }

    void rollback(){
        if(history.empty()) return;
        auto [b, old_size]=history.back();
        history.pop_back();

        if(b==-1) return; // nothing happened

        int a=parent[b];

        sz[a]=old_size;
        parent[b]=b;
        comps++;
    }

    int snapshot(){
        return history.size();
    }

    void rollback_to(int snap){
        while((int)history.size()>snap)
            rollback();
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q;
    cin>>n>>q;

    RollbackDSU dsu(n);

    while(q--){
        int type;
        cin>>type;

        if(type==1){
            int u,v;
            cin>>u>>v;
            dsu.unite(u,v);
        }
        else if(type==2){
            dsu.rollback();
        }
        else if(type==3){
            cout<<dsu.comps<<"\n";
        }
    }
}
