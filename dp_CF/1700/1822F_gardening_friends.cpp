#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include<map>
#include<queue>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans;

void dfs1(const vector<vector<ll>>& graph, ll node, ll par, ll d, vector<ll>& height, vector<ll>& depth) {
    depth[node] = d;
    for (auto it : graph[node]) {
        if (it == par) continue;
        dfs1(graph, it, node, d + 1, height, depth);
        height[node] = max(height[node], 1 + height[it]);
    }
}

void dfs2(const vector<vector<ll>>& graph, ll k, ll c, ll node, ll par, vector<ll>& height, vector<ll>& depth) {
    ans = max(ans, k * height[node] - c * depth[node]);
    ll mx = -1, secmx = -1;
    for (auto it : graph[node]) {
        if (it == par) continue;
        if (height[it] > mx) {
            secmx = mx;
            mx = height[it];
        } else if (height[it] > secmx) {
            secmx = height[it];
        }
    }
    for (auto it : graph[node]) {
        if (par == it) continue;
        ll temp1 = height[node], temp2 = height[it];
        if (height[it] + 1 == height[node]) height[node] = secmx + 1;
        height[it] = max(height[it], 1 + height[node]);
        dfs2(graph, k, c, it, node, height, depth);
        height[it] = temp2;
        height[node] = temp1;
    }
}

void solve() {
    ll n, k, c;
    cin >> n >> k >> c;
    vector<vector<ll>> graph(n + 1);
    for (int i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<ll> height(n + 1, 0), depth(n + 1, 0);
    ans = 0;
    dfs1(graph, 1, -1, 0, height, depth);
    dfs2(graph, k, c, 1, -1, height, depth);
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t;
    cin >> t;
    while (t--) solve();
    return 0;
}




#include <bits/stdc++.h>
using namespace std;

#define iofast() ios_base::sync_with_stdio(false); cin.tie(NULL);
#define ff first
#define ss second
#define all(v) v.begin(),v.end()
#define bipc(x) __builtin_popcountll(x)

#define yes cout << "YES\n"
#define no cout << "NO\n"
#define ccase(t) "Case #" << t << ": "
#define clz(x) __builtin_clz(x);
using ll = long long;

using vi = vector<int>;
template<class A>ostream&operator<<(ostream&out,const vector<A>&a){for(const A &it:a)out<<it<<" ";return out;}
template<class A>istream&operator>>(istream&in,vector<A>&a){for(A &i:a)in>>i;return in;}

const int N = (int)2e5 + 10;
const ll inf = (ll)1e18+10;
const int M = (int)1e9 + 7;

vi adj[N];
int sz;

vector<pair<int,int>> vec;
int dist[N];

void inline reset(){
  for(int i=1;i<=sz;++i) adj[i].clear();
  vec.clear();
}

int bfs(int ver, bool f = 0){
  queue<pair<pair<int,int>,int>> q;
  q.push({{ver,ver}, 0});
  
  int last = ver;
  while(!q.empty()){
    auto cur = q.front();
    q.pop();
    
    int v = cur.ff.ff, par = cur.ff.ss, d = cur.ss;
    
    last = v;
    
    if(!f) dist[v] = d;
    else if(d > dist[ver]) vec.push_back({v,d});
    
    for(int &ch: adj[v])
      if(ch != par) q.push({{ch,v}, d+1});
  }
  return last;
}

void solve(int t,bool kavya2719 = 1){
   ll k,c; cin >> sz >> k >> c;
   for(int i=0;i<sz-1;++i){
     int x,y; cin >> x >> y;
     adj[x].push_back(y);
     adj[y].push_back(x);
   }
   
   int last = bfs(1);
   bfs(last,1);
   
   ll mx = 0, ans = k*dist[last];
   for(auto &[v,d]: vec){
     int extra = d - dist[last];
     
     ll profit = k*extra - c*dist[v];
     mx = max(mx,profit);
   }
   
   cout << ans + mx << "\n";
   reset();
}


void phle_ka_kaam(){
   
}


int main()
{
    iofast();
   
    
    int TTTT=1;
    cin >> TTTT;
    for(int i=1;i<=TTTT;i++)
       solve(i);
}