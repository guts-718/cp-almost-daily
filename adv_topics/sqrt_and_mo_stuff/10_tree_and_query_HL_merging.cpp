#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int MAXF = 1 << 17;

int n, q;
int color[MAXN];

vector<int> graph[MAXN];
vector<int> children[MAXN];

vector<pair<int,int>> queries[MAXN]; // {query_id , k}
int answer[MAXN];

int subtreeSize[MAXN];


// ---------- Fenwick Tree ----------
int fenwick[MAXF];  // stores how many colors appear X times

void fenwick_add(int idx, int val){
    for(int i = idx; i < MAXF; i |= (i+1))
        fenwick[i] += val;
}

int fenwick_sum(int idx){
    int s = 0;
    for(int i = idx; i > 0; i &= (i-1))
        s += fenwick[i-1];
    return s;
}
// -----------------------------------


// freq[color] = how many times this color appears currently
int freq[MAXN];


// change frequency of a color
void updateColor(int c, int delta){

    // remove old frequency
    fenwick_add(freq[c], -1);

    freq[c] += delta;

    // add new frequency
    fenwick_add(freq[c], +1);
}


// compute subtree sizes and children list
void buildTree(int parent, int node){
    subtreeSize[node] = 1;

    for(int nxt : graph[node]){
        if(nxt == parent) continue;

        children[node].push_back(nxt);

        buildTree(node, nxt);

        subtreeSize[node] += subtreeSize[nxt];
    }
}


// remove subtree contribution
void removeSubtree(int node){
    updateColor(color[node], -1);

    for(int ch : children[node])
        removeSubtree(ch);
}


// add subtree contribution
void addSubtree(int node){
    updateColor(color[node], +1);

    for(int ch : children[node])
        addSubtree(ch);
}


// main DSU-on-tree DFS
void dfs(int node){

    // ---- find heavy child ----
    int heavy = -1;
    int bestSize = -1;

    for(int ch : children[node]){
        if(subtreeSize[ch] > bestSize){
            bestSize = subtreeSize[ch];
            heavy = ch;
        }
    }


    // ---- process light children ----
    for(int ch : children[node]){
        if(ch == heavy) continue;

        dfs(ch);
        removeSubtree(ch);
    }


    // ---- process heavy child ----
    if(heavy != -1)
        dfs(heavy);


    // ---- merge light children into heavy ----
    for(int ch : children[node]){
        if(ch == heavy) continue;
        addSubtree(ch);
    }


    // ---- add current node ----
    updateColor(color[node], +1);


    // ---- answer queries at this node ----
    for(auto &qu : queries[node]){
        int id = qu.first;
        int k  = qu.second;

        // count colors with freq >= k
        answer[id] = -fenwick_sum(k);
    }
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;

    for(int i=0;i<n;i++){
        cin >> color[i];
        color[i]--; // make colors 0-indexed
    }

    // read tree
    for(int i=0;i<n-1;i++){
        int a,b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // read queries
    for(int i=0;i<q;i++){
        int v,k;
        cin >> v >> k;
        v--;
        queries[v].push_back({i,k});
    }


    // build subtree info
    buildTree(-1, 0);

    // process everything
    dfs(0);


    // print answers
    for(int i=0;i<q;i++)
        cout << answer[i] << "\n";
}