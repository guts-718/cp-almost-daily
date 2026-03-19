#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> tree;

    SegTree(int size) {
        n = size;
        tree.resize(4 * n, 0);
    }

    void update(int idx, int val, int node, int l, int r) {
        if (l == r) {
            tree[node] += val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(idx, val, 2 * node, l, mid);
        else update(idx, val, 2 * node + 1, mid + 1, r);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int query(int ql, int qr, int node, int l, int r) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];

        int mid = (l + r) / 2;
        return query(ql, qr, 2 * node, l, mid) +
               query(ql, qr, 2 * node + 1, mid + 1, r);
    }

    void add(int idx, int val) {
        update(idx, val, 1, 1, n);
    }

    int sum(int l, int r) {
        if (l > r) return 0;
        return query(l, r, 1, 1, n);
    }
};

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<pair<int,int>> v(n);
        set<int> sst;

        for (int i = 0; i < n; i++) {
            cin >> v[i].first >> v[i].second;
            sst.insert(v[i].first);
            sst.insert(v[i].second);
        }

        map<int,int> mp;
        int ind = 1;
        for (auto x : sst) {
            mp[x] = ind++;
        }

        sort(v.begin(), v.end());

        SegTree st(ind + 2); 

        long long ans = 0;

        for (int i = n - 1; i >= 0; i--) {
            int L = mp[v[i].first];
            int R = mp[v[i].second];

            ans += st.sum(L + 1, R);

            // insert current
            st.add(R, 1);
        }

        cout << ans << "\n";
    }
}