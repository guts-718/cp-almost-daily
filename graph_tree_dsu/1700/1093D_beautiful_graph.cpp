#include <bits/stdc++.h>
#define int long long
using namespace std;

int mod = 998244353;

bool isBipartite(int node, vector<int>& col, int color, vector<vector<int>>& adj){
    col[node] = color;

    for(auto x: adj[node]){
        if(col[x] != 2){
            if(col[x] == col[node]) return true;
            continue;
        }
        if(isBipartite(x, col, !color, adj)) return true;
    }
    return false;
}

int fastpower(int n,int p){
    int ans=1;
    while(p){
        if(p&1) ans = (ans*n)%mod;
        n = (n*n)%mod;
        p/=2;
    }
    return ans;
}

void solve(){
    int n,m;
    cin>>n>>m;

    vector<vector<int>> adj(n);

    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        x--;y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> col(n,2);
    vector<int> vis(n,0);

    int ans = 1;

    for(int i=0;i<n;i++){

        if(vis[i]) continue;

        if(isBipartite(i,col,0,adj)){
            cout<<0<<"\n";
            return;
        }

        queue<int> q;
        q.push(i);
        vis[i]=1;

        int o=0,e=0,d=0;

        while(q.size()){
            int sz=q.size();

            if(d%2==0) o+=sz;
            else e+=sz;

            while(sz--){
                int node=q.front();
                q.pop();

                for(auto x:adj[node]){
                    if(vis[x]) continue;
                    vis[x]=1;
                    q.push(x);
                }
            }
            d++;
        }

        int ways = (fastpower(2,o) + fastpower(2,e)) % mod;
        ans = (ans * ways) % mod;
    }

    cout<<ans<<"\n";
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;

    while(t--){
        solve();
    }
}