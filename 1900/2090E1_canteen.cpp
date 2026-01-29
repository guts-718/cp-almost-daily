#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    // Prefix sums over doubled array
    vector<long long> pref(2 * n);
    pref[0] = a[0] - b[0];
    for (int i = 1; i < 2 * n; i++) {
        pref[i] = pref[i - 1] + (a[i % n] - b[i % n]);
    }

    stack<pair<long long, int>> st;   // {value, index}
    int ans = 0;

    for (int i = 0; i < 2 * n; i++) {
        while (!st.empty() && st.top().first >= pref[i]) {
            ans = max(ans, i - st.top().second);
            st.pop();
        }
        st.push({pref[i], i});
    }

    cout << ans << "\n";
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
