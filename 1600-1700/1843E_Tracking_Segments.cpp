#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<pair<int,int>> segs(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--;                 // convert to 0-based
        segs[i] = {l, r};
    }

    int q;
    cin >> q;
    vector<int> ord(q);
    for (int i = 0; i < q; i++) {
        cin >> ord[i];
        ord[i]--;            // convert to 0-based
    }

    int l = 0, r = q + 1;

    while (r - l > 1) {
        int mid = (l + r) / 2;

        vector<int> cur(n, 0);
        for (int i = 0; i < mid; i++) {
            cur[ord[i]] = 1;
        }

        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + cur[i];
        }

        bool ok = false;
        for (auto &seg : segs) {
            int L = seg.first;
            int R = seg.second;
            if (pref[R] - pref[L] > (R - L) / 2) {
                ok = true;
                break;
            }
        }

        if (ok)
            r = mid;
        else
            l = mid;
    }

    if (r == q + 1) r = -1;
    cout << r << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
