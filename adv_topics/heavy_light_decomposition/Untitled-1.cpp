
struct HLD {
    int n, timer=0;
    vector<vector<int>>& adj;

    vector<int> parent, depth, heavy, head, pos, subtree;
    vector<long long> base;

    /* ---------- SEGMENT TREE ---------- */

    struct SegTree {
        int n;
        vector<long long> st;

        SegTree(int n=0){ init(n); }

        void init(int n_){
            n=n_;
            st.assign(4*n,0);
        }

        long long merge(long long a,long long b){
            return a ^ b;        // <<< CHANGE OPERATION HERE
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
            if(r<i||l>j) return 0;   // <<< identity value
            if(i<=l&&r<=j) return st[p];
            int m=(l+r)/2;
            return merge(query(p<<1,l,m,i,j),
                         query(p<<1|1,m+1,r,i,j));
        }
    } seg;

    /* ---------- HLD ---------- */

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

    /* ---------- UPDATE NODE ---------- */

    void updateNode(int v,long long val){
        seg.update(1,0,n-1,pos[v],val);
    }

    /* ---------- QUERY PATH ---------- */

    long long queryPath(int a,int b){
        long long res=0;

        while(head[a]!=head[b]){
            if(depth[head[a]]<depth[head[b]])
                swap(a,b);

            res ^= seg.query(1,0,n-1,
                              pos[head[a]],
                              pos[a]);

            a = parent[head[a]];
        }

        if(depth[a]>depth[b]) swap(a,b);

        res ^= seg.query(1,0,n-1,pos[a],pos[b]);
        return res;
    }


    /* -------- LCA (Binary Lifting) -------- */

    int LOG;
    vector<vector<int>> up;

    void buildLCA(int root=0){
        LOG = 1;
        while((1<<LOG) <= n) LOG++;

        up.assign(n, vector<int>(LOG));

        function<void(int,int)> dfs2 = [&](int v,int p){
            up[v][0] = (p==-1? v : p);

            for(int i=1;i<LOG;i++)
                up[v][i] = up[ up[v][i-1] ][i-1];

            for(int u:adj[v]){
                if(u==p) continue;
                depth[u] = depth[v]+1;
                dfs2(u,v);
            }
        };

        depth[root]=0;
        dfs2(root,-1);
    }

    int lca(int a,int b){
        if(depth[a] < depth[b]) swap(a,b);

        int k = depth[a]-depth[b];
        for(int i=LOG-1;i>=0;i--)
            if(k&(1<<i))
                a = up[a][i];

        if(a==b) return a;

        for(int i=LOG-1;i>=0;i--){
            if(up[a][i] != up[b][i]){
                a = up[a][i];
                b = up[b][i];
            }
        }
        return up[a][0];
    }

    int get_len(int u,int v){
    int L = lca(u,v);     // or lca_O1(u,v)
    return depth[u] + depth[v] - 2*depth[L];
    }

};



/* ================= EXAMPLE MAIN ================= */

int main(){
    int n = 5;

    vector<vector<int>> adj(n);

    auto addEdge=[&](int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    addEdge(0,1);
    addEdge(1,2);
    addEdge(1,3);
    addEdge(3,4);

    vector<long long> vals = {1,2,3,4,5};

    HLD hld(n,adj);
    hld.build(vals);

    cout << "Path XOR 2 -> 4 = "
         << hld.queryPath(2,4) << endl;

    hld.updateNode(3,10);

    cout << "After update node3=10\n";

    cout << "Path XOR 2 -> 4 = "
         << hld.queryPath(2,4) << endl;
}