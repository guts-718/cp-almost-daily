#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    // Group values by zero count
    vector<vector<int>> groups(m + 1);
    int zeroCount = 0;

    for (int i = 0; i < n; i++) {
        if (v[i] == 0) {
            zeroCount++;
        } else {
            if (zeroCount >= abs(v[i])) {
                groups[zeroCount].push_back(v[i]);
            }
        }
    }

    vector<vector<int>> dp(m + 1, vector<int>(m + 1, 0));
    int ans = 0;

    for (int i = 1; i <= m; i++) {

        vector<int> pos(i + 1, 0), neg(i + 1, 0);

        for (auto &val : groups[i]) {
            if (val < 0)
                neg[abs(val)]++;
            else
                pos[val]++;
        }

        // Prefix sums
        for (int j = 1; j <= i; j++) {
            pos[j] += pos[j - 1];
            neg[j] += neg[j - 1];
        }

        for (int j = 0; j <= i; j++) {

            int takePos = 0, takeNeg = 0;

            if (j > 0)
                takePos = dp[j - 1][i - j];

            if (j < i)
                takeNeg = dp[j][i - j - 1];

            dp[j][i - j] = max(takePos, takeNeg)
                           + pos[j]
                           + neg[i - j];

            ans = max(ans, dp[j][i - j]);
        }
    }

    cout << ans << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
