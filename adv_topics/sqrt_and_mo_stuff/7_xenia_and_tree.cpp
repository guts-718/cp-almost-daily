#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];

int n,m;
int LOG;
vector<vector<int>> up;
vector<int> depth;

void dfs(int v,int p){
    up[v][0]=p;
    for(int i=1;i<=LOG;i++)
        up[v][i]=up[up[v][i-1]][i-1];

    for(int to:adj[v]){
        if(to==p) continue;
        depth[to]=depth[v]+1;
        dfs(to,v);
    }
}

int lca(int a,int b){
    if(depth[a]<depth[b]) swap(a,b);

    int k=depth[a]-depth[b];
    for(int i=LOG;i>=0;i--)
        if(k&(1<<i))
            a=up[a][i];

    if(a==b) return a;

    for(int i=LOG;i>=0;i--){
        if(up[a][i]!=up[b][i]){
            a=up[a][i];
            b=up[b][i];
        }
    }
    return up[a][0];
}

void propagate(vector<int>&slow,vector<int>&ans,vector<int>&vis,int idx){
    queue<int>q;

    for(auto x:slow){
        q.push(x);
        vis[x]=idx;
    }

    int cur=0;
    while(!q.empty()){
        int sz=q.size();
        while(sz--){
            int p=q.front();
            q.pop();
            ans[p]=min(cur,ans[p]);

            for(auto x:adj[p]){
                if(vis[x]!=idx){
                    vis[x]=idx;
                    q.push(x);
                }
            }
        }
        cur++;
    }
}

int main(){
    cin>>n>>m;

    for(int i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    LOG=ceil(log2(n));
    up.assign(n,vector<int>(LOG+1));
    depth.assign(n,0);

    dfs(0,0);

    vector<int>ans(n,2e6);
    ans[0]=0;

    vector<int>slow={0};
    vector<int>vis(n,-1);

    int idx=0;

    while(m--){
        int x,y;
        cin>>x>>y;
        y--;

        idx++;

        if(x==2){
            int sol=ans[y];
            for(auto z:slow){
                sol=min(sol, depth[y]+depth[z]-2*depth[lca(y,z)]);
            }
            cout<<sol<<"\n";
        }
        else{
            ans[y]=0;
            slow.push_back(y);
        }

        if(slow.size()>=sqrt(n)){
            propagate(slow,ans,vis,idx);
            slow.clear();
        }
    }
}
