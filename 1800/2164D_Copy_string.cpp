#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n, k;
    cin >> n >> k;

    string s, t;
    cin >> s >> t;

    // og[i] = position in s used for t[i]
    vector<ll> og(n);
    ll p = n - 1;

    for (ll i = n - 1; i >= 0; i--) {
        while (p >= 0 && (p > i || s[p] != t[i])) {
            p--;
        }

        if (p < 0 || i - p > k) {
            cout << -1 << '\n';
            return;
        }
        og[i] = p;
    }

    ll steps = 0;
    for (ll i = 0; i < n; i++) {
        steps = max(steps, i - og[i]);
    }

    cout << steps << '\n';

    // spread[pos] = rightmost index in t that uses pos
    vector<ll> spread(n, -1);
    for (ll i = 0; i < n; i++) {
        spread[og[i]] = i;
    }

    vector<ll> cur(n);
    iota(cur.begin(), cur.end(), 0);

    for (ll step = 0; step < steps; step++) {
        vector<ll> nxt(n);
        nxt[0] = cur[0];

        for (ll i = 1; i < n; i++) {
            if (spread[cur[i - 1]] >= i)
                nxt[i] = cur[i - 1];
            else
                nxt[i] = cur[i];
        }

        cur.swap(nxt);

        for (ll idx : cur) {
            cout << s[idx];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
