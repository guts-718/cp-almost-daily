#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<vector<int>> col;

void dfs(int node,int par,vector<vector<int>>&adj,vector<int>&ans){
    ans.push_back(node);
    for(auto x:adj[node]){
        if(x==par) continue;
        dfs(x,node,adj,ans);
    }
}

vector<int> fin;
vector<vector<vector<int>>> dp;
vector<vector<vector<int>>> choice;

int helper(int idx,vector<int>&a,int c1,int c2){
    if(idx>=a.size()) return 0;

    int &res = dp[idx][c1+1][c2+1];
    if(res!=-1) return res;

    int cur=2e18,clr=-1;

    for(int i=0;i<=2;i++){
        if(c1==i || c2==i) continue;

        int t=col[a[idx]][i] + helper(idx+1,a,i,c1);

        if(t<cur){
            cur=t;
            clr=i;
        }
    }

    choice[idx][c1+1][c2+1]=clr;
    return res=cur;
}

int32_t main() {
    int n;
    cin>>n;

    col.assign(n,vector<int>(3));
    fin.assign(n,-1);

    for(int i=0;i<n;i++) cin>>col[i][0];
    for(int i=0;i<n;i++) cin>>col[i][1];
    for(int i=0;i<n;i++) cin>>col[i][2];

    vector<vector<int>> adj(n);
    vector<int> indegree(n,0);

    int maxi=0;

    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--; v--;

        adj[u].push_back(v);
        adj[v].push_back(u);

        indegree[u]++;
        indegree[v]++;

        maxi=max(indegree[u],maxi);
        maxi=max(indegree[v],maxi);
    }

    if(maxi>=3){
        cout<<-1<<endl;
        return 0;
    }

    int node=-1;
    for(int i=0;i<n;i++){
        if(indegree[i]==1){
            node=i;
            break;
        }
    }

    vector<int> ans;
    dfs(node,-1,adj,ans);

    dp.assign(n,vector<vector<int>>(4,vector<int>(4,-1)));
    choice.assign(n,vector<vector<int>>(4,vector<int>(4,-1)));

    int sol=2e18;
    int best=-1;

    for(int c=0;c<3;c++){
        int val=col[ans[0]][c]+helper(1,ans,c,-1);
        if(val<sol){
            sol=val;
            best=c;
        }
    }

    cout<<sol<<endl;

    fin[ans[0]]=best;

    int c1=best,c2=-1;

    for(int i=1;i<n;i++){
        int clr=choice[i][c1+1][c2+1];
        fin[ans[i]]=clr;
        c2=c1;
        c1=clr;
    }

    for(int i=0;i<n;i++) cout<<fin[i]+1<<" ";
    cout<<endl;
}