#include<bits/stdc++.h>
using namespace std;

struct HLD {
    int n, timer=0;
    vector<vector<int>>& adj;

    vector<int> parent, depth, heavy, head, pos, subtree;
    vector<long long> base;

    struct SegTree {
        int n;
        vector<long long> st,lz; // *** lazy added

        SegTree(int n=0){ init(n); }

        void init(int n_){
            n=n_;
            st.assign(4*n,0);
            lz.assign(4*n,0); // ***
        }

        void push(int p,int l,int r){ // ***
            if(lz[p]==0) return;
            st[p]+= (r-l+1)*lz[p];
            if(l!=r){
                lz[p<<1]+=lz[p];
                lz[p<<1|1]+=lz[p];
            }
            lz[p]=0;
        }

        long long merge(long long a,long long b){
            return a+b;
        }

        void build(int p,int l,int r,vector<long long>& base){
            if(l==r){ st[p]=base[l]; return; }
            int m=(l+r)/2;
            build(p<<1,l,m,base);
            build(p<<1|1,m+1,r,base);
            st[p]=merge(st[p<<1],st[p<<1|1]);
        }

        void update(int p,int l,int r,int i,int j,long long val){ // ***
            push(p,l,r);

            if(r<i||l>j) return;

            if(i<=l&&r<=j){
                lz[p]+=val;
                push(p,l,r);
                return;
            }

            int m=(l+r)/2;
            update(p<<1,l,m,i,j,val);
            update(p<<1|1,m+1,r,i,j,val);

            st[p]=merge(st[p<<1],st[p<<1|1]);
        }

        long long query(int p,int l,int r,int i,int j){
            push(p,l,r);

            if(r<i||l>j) return 0LL;
            if(i<=l&&r<=j) return st[p];

            int m=(l+r)/2;
            return merge(query(p<<1,l,m,i,j),
                         query(p<<1|1,m+1,r,i,j));
        }
    } seg;

    HLD(int n, vector<vector<int>>&adj):n(n),adj(adj){
        parent.resize(n);
        depth.resize(n);
        heavy.assign(n,-1);
        head.resize(n);
        pos.resize(n);
        subtree.resize(n);
        base.resize(n);
    }

    int dfs(int v,int p){
        parent[v]=p;
        subtree[v]=1;
        int mx=0;

        for(int u:adj[v]){
            if(u==p) continue;
            depth[u]=depth[v]+1;
            int s=dfs(u,v);
            subtree[v]+=s;

            if(s>mx){
                mx=s;
                heavy[v]=u;
            }
        }
        return subtree[v];
    }

    void decompose(int v,int h){
        head[v]=h;
        pos[v]=timer++;

        if(heavy[v]!=-1)
            decompose(heavy[v],h);

        for(int u:adj[v]){
            if(u==parent[v]||u==heavy[v]) continue;
            decompose(u,u);
        }
    }

    void build(vector<long long>& values,int root=0){
        dfs(root,-1);
        decompose(root,root);

        for(int i=0;i<n;i++)
            base[pos[i]]=values[i];

        seg.init(n);
        seg.build(1,0,n-1,base);
    }

    // *** PATH UPDATE
    void updatePath(int a,int b,long long val){
        while(head[a]!=head[b]){
            if(depth[head[a]]<depth[head[b]])
                swap(a,b);

            seg.update(1,0,n-1,pos[head[a]],pos[a],val);

            a = parent[head[a]];
        }

        if(depth[a]>depth[b]) swap(a,b);

        seg.update(1,0,n-1,pos[a],pos[b],val);
    }

    long long queryPath(int a,int b){
        long long res=0LL;

        while(head[a]!=head[b]){
            if(depth[head[a]]<depth[head[b]])
                swap(a,b);

            res+=seg.query(1,0,n-1,pos[head[a]],pos[a]);

            a = parent[head[a]];
        }

        if(depth[a]>depth[b]) swap(a,b);

        res+= seg.query(1,0,n-1,pos[a],pos[b]);

        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q;
    cin>>n>>q;
    vector<vector<int>> adj(n);

    auto addEdge=[&](int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    vector<long long> vals(n);
    for(auto &x:vals)cin>>x;

    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        a--;b--;
        addEdge(a,b);
    }

    HLD hld(n,adj);
    hld.build(vals);

    while(q--){
        int type;
        cin>>type;

        if(type==1){ //  path add
            int u,v,x;
            cin>>u>>v>>x;
            u--;v--;
            hld.updatePath(u,v,x);
        }
        else{ 
            int u,v;
            cin>>u>>v;
            u--;v--;
            cout<<hld.queryPath(u,v)<<'\n';
        }
    }
}
