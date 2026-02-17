#include <bits/stdc++.h>
#define int long long
using namespace std;

using ll = long long;

struct Query {
    int l, r, id;
};

int BLOCK; // block size

bool cmp(const Query &a, const Query &b) {
    int block_a = a.l / BLOCK;
    int block_b = b.l / BLOCK;
    if (block_a != block_b)
        return block_a < block_b;
    return (block_a & 1) ? (a.r > b.r) : (a.r < b.r);
    // odd-even trick improves constant factor
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int &x : arr) cin >> x;

    BLOCK = sqrt(n);

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; queries[i].r--; // 0-indexed
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end(), cmp);

    vector<ll> ans(q);

    // ---------- YOUR DATA STRUCTURE ----------
    // Example: frequency + current answer
    vector<int>freq(1e6+3,0);
    ll cur = 0;

    auto add = [&](int idx) {
        int x = arr[idx];
        int fr=freq[x];
        cur-=(fr*fr*arr[idx]);
        freq[x]++;
        fr=freq[x];
        cur+=(fr*fr*arr[idx]);
       
    };

    auto remove = [&](int idx) {
        int x = arr[idx];
        int fr=freq[x];
        cur-=(fr*fr*arr[idx]);
        freq[x]--;
        fr=freq[x];
        cur+=(fr*fr*arr[idx]);
    };
   

    int L = 0, R = -1;

    for (auto &qr : queries) {
        while (L > qr.l) add(--L);
        while (R < qr.r) add(++R);
        while (L < qr.l) remove(L++);
        while (R > qr.r) remove(R--);

        ans[qr.id] = cur;
    }

    for (ll x : ans)
        cout << x << '\n';
}
