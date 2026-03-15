
struct DSU {
    vector<int> p, sz;
    DSU(int n) {
        p.resize(n);
        sz.assign(n,1);
        iota(p.begin(),p.end(),0);
    }
    int find(int x){
        if(p[x]==x) return x;
        return p[x]=find(p[x]);
    }
    void unite(int a,int b){
        a=find(a), b=find(b);
        if(a==b) return;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a;
        sz[a]+=sz[b];
    }
};

class Solution {
public:
    int maxActivated(vector<vector<int>>& points) {

        unordered_map<long long,int> xid,yid;

        int xi=0, yi=0;

        for(auto &p:points){
            if(!xid.count(p[0])) xid[p[0]]=xi++;
            if(!yid.count(p[1])) yid[p[1]]=yi++;
        }

        DSU dsu(xi+yi);

        for(auto &p:points){
            int a=xid[p[0]];
            int b=yid[p[1]]+xi;
            dsu.unite(a,b);
        }

        unordered_map<int,int> comp;

        for(auto &p:points){
            int r=dsu.find(xid[p[0]]);
            comp[r]++;
        }

        vector<int> sizes;
        for(auto &it:comp) sizes.push_back(it.second);

        sort(sizes.rbegin(),sizes.rend());

        if(sizes.size()==1) return sizes[0]+1;

        return sizes[0]+sizes[1]+1;
    }
};