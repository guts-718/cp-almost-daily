#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);
    map<pair<int,int>, int> mp;

    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;

        if(u > v) swap(u, v);
        mp[{u, v}] = i;

        

        adj[u].push_back(v);
        adj[v].push_back(u);

        indegree[u]++;
        indegree[v]++;
    }

    if(n==2){
        cout<<0<<endl;
        continue;
    }
    vector<int> leaves;
    for(int i = 0; i < n; i++){
        if(indegree[i] == 1 && leaves.size() < 3)
            leaves.push_back(i);
    }

    vector<int> ans(n - 1, -1);
    int idx = 0;

    for(auto x : leaves){
        int a = min(x, adj[x][0]);
        int b = max(x, adj[x][0]);

        ans[mp[{a, b}]] = idx++;
        mp[{a, b}] = -1;
    }

    for(auto &[p, val] : mp){
        if(val == -1) continue;
        ans[val] = idx++;
    }

    for(int i = 0; i < n - 1; i++)
        cout << ans[i] << endl;

}