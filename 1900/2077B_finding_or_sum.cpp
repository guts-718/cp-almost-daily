#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
  Sends a query and reads the response
*/
ll query(ll x) {
    cout << x << '\n';
    cout.flush();
    ll res;
    cin >> res;
    return res;
}

/*
  Ends querying phase and reads final value m
*/
ll end_query() {
    cout << "!" << '\n';
    cout.flush();
    ll res;
    cin >> res;
    return res;
}

void solve() {
    ll mask_even = 0, mask_odd = 0;

    // mask_even: bits set at odd positions
    for (int i = 1; i < 30; i += 2)
        mask_even |= (1LL << i);

    // mask_odd: bits set at even positions
    for (int i = 0; i < 30; i += 2)
        mask_odd |= (1LL << i);

    ll q0 = query(mask_even);
    ll q1 = query(mask_odd);
    ll m  = end_query();

    ll val_and = 0, val_or = 0;

    // Resolve even bit positions
    for (int i = 0; i < 30; i += 2) {
        ll bit_fwd = (q0 >> (i + 1)) & 1;
        ll bit_cur = (q0 >> i) & 1;
        ll pos = (1LL << i);

        if (bit_fwd) {
            // pattern: 10
            val_and |= pos;
            val_or  |= pos;
        } else if (bit_cur) {
            // pattern: 01
            val_or |= pos;
        }

        q0 -= 4 * pos;
    }

    // Resolve odd bit positions
    q1 -= 2;
    for (int i = 1; i < 30; i += 2) {
        ll bit_fwd = (q1 >> (i + 1)) & 1;
        ll bit_cur = (q1 >> i) & 1;
        ll pos = (1LL << i);

        if (bit_fwd && !bit_cur) {
            // pattern: 10
            val_and |= pos;
            val_or  |= pos;
        } else if (!bit_fwd && bit_cur) {
            // pattern: 01
            val_or |= pos;
        }

        q1 -= 4 * pos;
    }

    // Construct final answer
    ll ans = 0;
    for (int i = 0; i < 30; i++) {
        ll bit_m   = (m >> i) & 1;
        ll bit_and = (val_and >> i) & 1;
        ll bit_or  = (val_or >> i) & 1;
        ll pos = (1LL << i);

        if (bit_m || bit_and)
            ans += 2 * pos;
        else if (bit_or)
            ans += pos;
    }

    cout << ans << '\n';
    cout.flush();
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
