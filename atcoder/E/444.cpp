#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, d;
    cin >> n >> d;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    multiset<int> s;
    int ans = 0;
    int l = 0;

    auto bad = [&](multiset<int>::iterator it) {
        if (it != s.begin()) {
            auto p = prev(it);
            if (*it - *p < d) return true;
        }
        auto nx = next(it);
        if (nx != s.end()) {
            if (*nx - *it < d) return true;
        }
        return false;
    };

    for (int r = 0; r < n; r++) {
        auto it = s.insert(a[r]);

        while (bad(it)) {
            auto rem = s.find(a[l]);
            s.erase(rem);
            l++;
            it = s.find(a[r]);
        }

        ans += (r - l + 1);
    }

    cout << ans << '\n';
    return 0;
}
