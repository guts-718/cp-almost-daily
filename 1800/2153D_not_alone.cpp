#include <bits/stdc++.h>
#define int long long
using namespace std;

int get3(int x, int y, int z) {
    return max({x, y, z}) - min({x, y, z});
}

// Memoized helper
int helper(int idx, int final, const vector<int>& a, vector<int>& dp) {
    if (idx >= final) return 0;
    if (dp[idx] != -1) return dp[idx];

    int res = 1e18;

    // Case 1: Pair
    if (idx + 1 < final) {
        res = min(res, abs(a[idx] - a[idx + 1]) + helper(idx + 2, final, a, dp));
    }

    // Case 2: Triplet
    if (idx + 2 < final) {
        res = min(res, get3(a[idx], a[idx + 1], a[idx + 2]) + helper(idx + 3, final, a, dp));
    }

    return dp[idx] = res;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 2);
        for (int i = 0; i < n; i++) cin >> a[i];
        a[n] = a[0];
        a[n + 1] = a[1];

        int ans = 1e18;

        for (int l = 0; l < 3; l++) {
            vector<int> sub(a.begin() + l, a.begin() + l + n + 2);
            vector<int> dp(n + 5, -1);
            ans = min(ans, helper(0, n, sub, dp));
        }

        cout << ans << "\n";
    }
    return 0;
}
