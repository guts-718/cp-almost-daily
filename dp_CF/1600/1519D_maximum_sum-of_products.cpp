#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    cin >> n;

    vector<ll> A(n + 1), B(n + 1);
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= n; i++) cin >> B[i];

    // Prefix and suffix sums of A[i] * B[i]
    vector<ll> pref(n + 2, 0), suf(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + A[i] * B[i];
    }
    for (int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] + A[i] * B[i];
    }

    // dp[i][j]: best value for reversing subarray [j..i]
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = A[i] * B[i];
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            dp[i][j] =
                dp[i - 1][j + 1] + A[i] * B[j] + A[j] * B[i];
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            ans = max(ans, dp[i][j] + pref[j - 1] + suf[i + 1]);
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
