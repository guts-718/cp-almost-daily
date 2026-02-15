#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 300000 + 25;

struct Node {
    ll ans = 0;
    ll pref = 0;
    ll suff = 0;
    ll sum = 0;
};

int n, q;
vector<int> graph[MAXN];

int parent[MAXN], depth[MAXN];
int heavy[MAXN], subtreeSize[MAXN];

int head[MAXN];
int startTime[MAXN], finishTime[MAXN];
int nodeAtPos[MAXN];
int timer = 0;

int value[MAXN];
Node segtree[4 * MAXN];
Node EMPTY;

/* ---------- HLD DFS ---------- */
void dfs(int v, int p = 0) {
    parent[v] = p;
    subtreeSize[v] = 1;
    heavy[v] = 0;

    for (int u : graph[v]) {
        if (u == p) continue;
        depth[u] = depth[v] + 1;
        dfs(u, v);

        subtreeSize[v] += subtreeSize[u];
        if (subtreeSize[u] > subtreeSize[heavy[v]])
            heavy[v] = u;
    }
}

/* ---------- HLD Decomposition ---------- */
void decompose(int v, int h) {
    head[v] = h;
    startTime[v] = timer;
    nodeAtPos[timer++] = v;

    if (heavy[v])
        decompose(heavy[v], h);

    for (int u : graph[v]) {
        if (u == parent[v] || u == heavy[v]) continue;
        decompose(u, u);
    }

    finishTime[v] = timer;
}

/* ---------- Segment Tree ---------- */
Node mergeNode(const Node &a, const Node &b) {
    Node c;
    c.sum  = a.sum + b.sum;
    c.pref = max(a.pref, a.sum + b.pref);
    c.suff = max(b.suff, b.sum + a.suff);
    c.ans  = max({a.ans, b.ans, a.suff + b.pref});
    return c;
}

void build(int idx = 0, int l = 0, int r = n) {
    if (r - l == 1) {
        ll x = value[nodeAtPos[l]];
        segtree[idx] = { max(x, 0LL), max(x, 0LL), max(x, 0LL), x };
        return;
    }

    int mid = (l + r) / 2;
    build(2*idx+1, l, mid);
    build(2*idx+2, mid, r);
    segtree[idx] = mergeNode(segtree[2*idx+1], segtree[2*idx+2]);
}

void update(int pos, ll val, int idx = 0, int l = 0, int r = n) {
    if (r - l == 1) {
        segtree[idx] = { max(val,0LL), max(val,0LL), max(val,0LL), val };
        return;
    }

    int mid = (l + r) / 2;
    if (pos < mid) update(pos, val, 2*idx+1, l, mid);
    else update(pos, val, 2*idx+2, mid, r);

    segtree[idx] = mergeNode(segtree[2*idx+1], segtree[2*idx+2]);
}

Node query(int ql, int qr, int idx = 0, int l = 0, int r = n) {
    if (qr <= l || r <= ql) return EMPTY;
    if (ql <= l && r <= qr) return segtree[idx];

    int mid = (l + r) / 2;
    return mergeNode(
        query(ql, qr, 2*idx+1, l, mid),
        query(ql, qr, 2*idx+2, mid, r)
    );
}

/* ---------- Path Query ---------- */
ll queryPath(int u, int v) {
    Node leftRes = EMPTY, rightRes = EMPTY;

    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) {
            swap(u, v);
            swap(leftRes, rightRes);
        }

        leftRes = mergeNode(
            query(startTime[head[u]], startTime[u] + 1),
            leftRes
        );

        u = parent[head[u]];
    }

    if (depth[u] > depth[v]) {
        swap(u, v);
        swap(leftRes, rightRes);
    }

    swap(leftRes.pref, leftRes.suff);

    Node middle = query(startTime[u], startTime[v] + 1);
    return mergeNode( mergeNode(leftRes, middle), rightRes ).ans;
}

/* ---------- Main ---------- */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> value[i];

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    EMPTY = Node();

    dfs(1);
    decompose(1, 1);
    build();

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int v; ll x;
            cin >> v >> x;
            update(startTime[v], x);
        }
        else {
            int u, v;
            cin >> u >> v;
            cout << queryPath(u, v) << '\n';
        }
    }
}
