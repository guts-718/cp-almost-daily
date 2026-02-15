#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long val;

    Node(long long v=0):val(v){}
};

Node mergeNode(const Node &a,const Node &b){
    return Node(a.val + b.val); // change operation here
}

struct SegTree {
    int n;
    vector<Node> st;

    SegTree(int n=0){ init(n); }

    void init(int n_){
        n=n_;
        st.assign(4*n, Node());
    }

    void build(int p,int l,int r,vector<Node>&base){
        if(l==r){ st[p]=base[l]; return; }
        int m=(l+r)/2;
        build(p<<1,l,m,base);
        build(p<<1|1,m+1,r,base);
        st[p]=mergeNode(st[p<<1],st[p<<1|1]);
    }

    void update(int p,int l,int r,int i,Node v){
        if(l==r){ st[p]=v; return; }
        int m=(l+r)/2;
        if(i<=m) update(p<<1,l,m,i,v);
        else update(p<<1|1,m+1,r,i,v);
        st[p]=mergeNode(st[p<<1],st[p<<1|1]);
    }

    Node query(int p,int l,int r,int i,int j){
        if(r<i||l>j) return Node(0); // neutral
        if(i<=l&&r<=j) return st[p];
        int m=(l+r)/2;
        return mergeNode(query(p<<1,l,m,i,j),
                         query(p<<1|1,m+1,r,i,j));
    }
};

struct HLD {
    int n,timer=0;
    vector<vector<int>>&adj;

    vector<int> parent,depth,heavy,head,pos,sub;
    vector<Node> base;
    SegTree seg;

    HLD(int n,vector<vector<int>>&adj):n(n),adj(adj){
        parent.resize(n);
        depth.resize(n);
        heavy.assign(n,-1);
        head.resize(n);
        pos.resize(n);
        sub.resize(n);
        base.resize(n);
    }

    int dfs(int v,int p){
        parent[v]=p;
        sub[v]=1;
        int mx=0;

        for(int u:adj[v]){
            if(u==p) continue;
            depth[u]=depth[v]+1;
            int s=dfs(u,v);
            sub[v]+=s;
            if(s>mx) mx=s,heavy[v]=u;
        }
        return sub[v];
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

    void build(vector<Node>&values,int root=0){
        dfs(root,-1);
        decompose(root,root);

        for(int i=0;i<n;i++)
            base[pos[i]]=values[i];

        seg.init(n);
        seg.build(1,0,n-1,base);
    }

    // point update
    void updateNode(int v,Node val){
        seg.update(1,0,n-1,pos[v],val);
    }

    // path query (node version)
    Node queryPathNode(int a,int b){
        Node res;

        while(head[a]!=head[b]){
            if(depth[head[a]]<depth[head[b]])
                swap(a,b);

            res=mergeNode(res,
                seg.query(1,0,n-1,pos[head[a]],pos[a]));

            a=parent[head[a]];
        }

        if(depth[a]>depth[b]) swap(a,b);

        res=mergeNode(res,
            seg.query(1,0,n-1,pos[a],pos[b]));

        return res;
    }

    // path query (edge version)
    Node queryPathEdge(int a,int b){
        Node res;

        while(head[a]!=head[b]){
            if(depth[head[a]]<depth[head[b]])
                swap(a,b);

            res=mergeNode(res,
                seg.query(1,0,n-1,pos[head[a]],pos[a]));

            a=parent[head[a]];
        }

        if(depth[a]>depth[b]) swap(a,b);

        if(a!=b) // exclude LCA
            res=mergeNode(res,
                seg.query(1,0,n-1,pos[a]+1,pos[b]));

        return res;
    }
};
