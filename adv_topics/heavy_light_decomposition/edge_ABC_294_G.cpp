 // https://www.spoj.com/problems/QTREE/ - colin galen

// not AC dont know why

#include<bits/stdc++.h>
using namespace std;

inline long long key(int a,int b){ return ((long long)a<<32)|b; }

struct HLD {
    int n, timer=0;
    vector<vector<int>>& adj;

    vector<int> parent, depth, heavy, head, pos, subtree;
    vector<long long> base;

    struct SegTree {
        int n;
        vector<long long> st;

        SegTree(int n=0){ init(n); }

        void init(int n_){
            n=n_;
            st.assign(4*n,0);
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

        void update(int p,int l,int r,int i,long long val){
            if(l==r){ st[p]=val; return; }
            int m=(l+r)/2;
            if(i<=m) update(p<<1,l,m,i,val);
            else update(p<<1|1,m+1,r,i,val);
            st[p]=merge(st[p<<1],st[p<<1|1]);
        }

        long long query(int p,int l,int r,int i,int j){
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

    void updateNode(int v,long long val){
        seg.update(1,0,n-1,pos[v],val);
    }
    
    long long queryPath(int a,int b){
        long long res=0LL;
    
        while(head[a]!=head[b]){
            if(depth[head[a]]<depth[head[b]])
                swap(a,b);
    
            res+=seg.query(1,0,n-1,
                              pos[head[a]],
                              pos[a]);
    
            a = parent[head[a]];
        }
    
        if(depth[a]>depth[b]) swap(a,b);
    
        // FIX: exclude LCA node's stored value as we are storing down. the LCA node's value is outside the path.
        if(a!=b)
            res+= seg.query(1,0,n-1,pos[a]+1,pos[b]);
    
        return res;
    }

};

void help(vector<vector<int>>&adj,unordered_map<long long,int>&mp,int node,int par,vector<long long>&vals){
    vals[node]=mp[key(node,par)];
    for(auto x:adj[node]){
        if(x==par)continue;
        help(adj,mp,x,node,vals);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t=1;
    //cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<vector<int>> adj(n);

        auto addEdge=[&](int u,int v){
            adj[u].push_back(v);
            adj[v].push_back(u);
        };

        unordered_map<long long,int> mp;
        mp.reserve(n*2);

        vector<pair<int,int>> edges(n); 

        for(int i=0;i<n-1;i++){
            int a,b,c;
            cin>>a>>b>>c;
            a--;b--;
            addEdge(a,b);
            mp[key(a,b)]=c;
            mp[key(b,a)]=c;
            edges[i]={a,b}; 
        }

        vector<long long> vals(n);
        vals[0]=0LL;

        for(auto x:adj[0])
            help(adj,mp,x,0,vals);

        string s;

        HLD hld(n,adj);
        hld.build(vals);
        int q;
        cin>>q;
        
        while(q--){
            int x;
            cin>>x;
            int u,v;
            cin>>u>>v;

            if(x==2){
                u--;v--;
                cout<<hld.queryPath(u,v)<<'\n';
            }else{
                u--;                     

                int a=edges[u].first;    
                int b=edges[u].second;   

                int node = (hld.parent[a]==b ? a : b); 

                hld.updateNode(node,v);  
            }
        }
    }
}
