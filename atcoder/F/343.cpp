#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

using os = tree<int,null_type,less<int>,
                rb_tree_tag,tree_order_statistics_node_update>;

struct Node {
    int mx1, c1, mx2, c2;
};

Node merge(Node a, Node b) {
    vector<pair<int,int>> v = {
        {a.mx1,a.c1},{a.mx2,a.c2},
        {b.mx1,b.c1},{b.mx2,b.c2}
    };
    sort(v.begin(), v.end(), greater<>());

    Node r;
    r.mx1 = v[0].first;
    r.c1 = 0;
    int i=0;
    while(i<4 && v[i].first==r.mx1){
        r.c1 += v[i].second;
        i++;
    }

    r.mx2 = -1; r.c2 = 0;
    while(i<4){
        if(v[i].first < r.mx1){
            r.mx2 = v[i].first;
            while(i<4 && v[i].first==r.mx2){
                r.c2 += v[i].second;
                i++;
            }
            break;
        }
        i++;
    }
    return r;
}

struct SegTree {
    int n;
    vector<Node> st;

    SegTree(vector<int>& a){
        n=a.size();
        st.resize(4*n);
        build(1,0,n-1,a);
    }

    void build(int p,int l,int r,vector<int>& a){
        if(l==r){
            st[p]={a[l],1,-1,0};
            return;
        }
        int m=(l+r)/2;
        build(p*2,l,m,a);
        build(p*2+1,m+1,r,a);
        st[p]=merge(st[p*2],st[p*2+1]);
    }

    void update(int p,int l,int r,int i,int v){
        if(l==r){
            st[p]={v,1,-1,0};
            return;
        }
        int m=(l+r)/2;
        if(i<=m) update(p*2,l,m,i,v);
        else update(p*2+1,m+1,r,i,v);
        st[p]=merge(st[p*2],st[p*2+1]);
    }

    Node query(int p,int l,int r,int i,int j){
        if(r<i||l>j) return {-1,0,-1,0};
        if(l>=i&&r<=j) return st[p];
        int m=(l+r)/2;
        return merge(query(p*2,l,m,i,j),
                     query(p*2+1,m+1,r,i,j));
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,Q;
    cin>>N>>Q;
    vector<int>a(N);

    unordered_map<int,os> pos;

    for(int i=0;i<N;i++){
        cin>>a[i];
        pos[a[i]].insert(i);
    }

    SegTree seg(a);

    while(Q--){
        int t; cin>>t;
        if(t==1){
            int p,x;
            cin>>p>>x;
            --p;

            int old=a[p];
            pos[old].erase(p);
            if(pos[old].empty()) pos.erase(old);

            a[p]=x;
            pos[x].insert(p);

            seg.update(1,0,N-1,p,x);
        }
        else{
            int l,r;
            cin>>l>>r;
            --l;--r;

            Node res=seg.query(1,0,N-1,l,r);
            int sec=res.mx2;

            if(sec==-1){
                cout<<0<<"\n";
                continue;
            }

            os &s = pos[sec];
            int ans = s.order_of_key(r+1)
                    - s.order_of_key(l);
            cout<<ans<<"\n";
        }
    }
    return 0;
}
