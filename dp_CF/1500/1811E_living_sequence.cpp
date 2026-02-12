#include <bits/stdc++.h>
using namespace std;

#define int long long

int dp[13][2][2];
vector<int> digits;

/*
  Digit DP:
  pos   → current digit index
  tight → prefix is equal to limit
  has4  → whether digit 4 appeared
*/
int dfs(int pos, bool tight, bool has4) {
    if (pos == (int)digits.size()) {
        return has4;
    }

    int &res = dp[pos][tight][has4];
    if (res != -1) return res;

    res = 0;
    int limit = tight ? digits[pos] : 9;

    for (int d = 0; d <= limit; d++) {
        res += dfs(
            pos + 1,
            tight && (d == limit),
            has4 || (d == 4)
        );
    }
    return res;
}

/* count numbers ≤ x that contain digit 4 */
int count_with_4(int x) {
    digits.clear();
    while (x > 0) {
        digits.push_back(x % 10);
        x /= 10;
    }
    reverse(digits.begin(), digits.end());

    memset(dp, -1, sizeof(dp));
    return dfs(0, true, false);
}

void solve() {
    int n;
    cin >> n;

    int low = 0, high = 10 * n, ans = n + 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int valid = mid - count_with_4(mid);

        if (valid >= n) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
