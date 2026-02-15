class Solution {
public:
    vector<vector<int>> g;
    vector<int> parent, depth, heavy, head, pos, sz;
    int curPos=0;
    string s;

    struct SegTree {
        int n;
        vector<int> st,lazy;

        SegTree(int n):n(n){
            st.resize(4*n);
            lazy.resize(4*n);
        }

        void push(int p,int l,int r){
            if(lazy[p]){
                st[p]^=lazy[p];
                if(l!=r){
                    lazy[p<<1]^=lazy[p];
                    lazy[p<<1|1]^=lazy[p];
                }
                lazy[p]=0;
            }
        }

        void build(int p,int l,int r,vector<int>&a){
            if(l==r){ st[p]=a[l]; return; }
            int m=(l+r)>>1;
            build(p<<1,l,m,a);
            build(p<<1|1,m+1,r,a);
            st[p]=st[p<<1]^st[p<<1|1];
        }

        void upd(int p,int l,int r,int i,int val){
            push(p,l,r);
            if(l==r){ st[p]=val; return; }
            int m=(l+r)>>1;
            if(i<=m) upd(p<<1,l,m,i,val);
            else upd(p<<1|1,m+1,r,i,val);
            st[p]=st[p<<1]^st[p<<1|1];
        }

        int query(int p,int l,int r,int i,int j){
            push(p,l,r);
            if(r<i||l>j) return 0;
            if(i<=l&&r<=j) return st[p];
            int m=(l+r)>>1;
            return query(p<<1,l,m,i,j)^query(p<<1|1,m+1,r,i,j);
        }
    };

    int dfs(int v,int p){
        parent[v]=p;
        sz[v]=1;
        int mx=0;
        for(int u:g[v]){
            if(u==p) continue;
            depth[u]=depth[v]+1;
            int s=dfs(u,v);
            sz[v]+=s;
            if(s>mx) mx=s, heavy[v]=u;
        }
        return sz[v];
    }

    void decompose(int v,int h){
        head[v]=h;
        pos[v]=curPos++;
        if(heavy[v]!=-1)
            decompose(heavy[v],h);
        for(int u:g[v]){
            if(u==parent[v]||u==heavy[v]) continue;
            decompose(u,u);
        }
    }

    int queryPath(int a,int b,SegTree& st){
        int res=0;
        while(head[a]!=head[b]){
            if(depth[head[a]]<depth[head[b]]) swap(a,b);
            res^=st.query(1,0,curPos-1,pos[head[a]],pos[a]);
            a=parent[head[a]];
        }
        if(depth[a]>depth[b]) swap(a,b);
        res^=st.query(1,0,curPos-1,pos[a],pos[b]);
        return res;
    }

    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s_, vector<string>& queries) {
        s=s_;
        g.assign(n,{});
        for(auto&e:edges){
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        parent.assign(n,0);
        depth.assign(n,0);
        heavy.assign(n,-1);
        head.assign(n,0);
        pos.assign(n,0);
        sz.assign(n,0);

        dfs(0,-1);
        decompose(0,0);

        vector<int> base(n);
        for(int i=0;i<n;i++)
            base[pos[i]] = 1<<(s[i]-'a');

        SegTree st(n);
        st.build(1,0,n-1,base);

        vector<bool> ans;

        for(auto &q:queries){
            stringstream ss(q);
            string type; ss>>type;

            if(type=="update"){
                int u; char c;
                ss>>u>>c;
                s[u]=c;
                st.upd(1,0,n-1,pos[u],1<<(c-'a'));
            }
            else{
                int u,v;
                ss>>u>>v;
                int mask=queryPath(u,v,st);
                ans.push_back((mask&(mask-1))==0);
            }
        }
        return ans;
    }
};
