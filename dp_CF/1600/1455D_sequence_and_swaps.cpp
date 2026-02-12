#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 4e18;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        for (auto &v : a) cin >> v;

        vector<int> b = a;
        sort(b.begin(), b.end());
        if (a == b) {
            cout << 0 << '\n';
            continue;
        }

        const int LIM = 550;
        const int BIG = 2e9;

        // dp[ind+1]
        vector<vector<int>> next(LIM + 1, vector<int>(LIM + 1, 0));
        // for (int i = 0; i <= LIM; i++) {
        //     next[x][i]=0;
        // }
        // dp[ind]
        vector<vector<int>> cur(LIM + 1, vector<int>(LIM + 1, BIG));

        // base case: dp[n][*][*] = 0 already in `next`

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int j = 0; j <= LIM; j++) {
                for (int k = 0; k <= LIM; k++) {
                    cur[j][k] = BIG;

                    if (a[ind] > j && j >= k) {
                        cur[j][k] = min(cur[j][k],
                                         1 + next[a[ind]][j]);
                    }
                    if (a[ind] >= k) {
                        cur[j][k] = min(cur[j][k],
                                         next[j][max(a[ind], k)]);
                    }
                }
            }
            swap(cur, next);
        }

        int ans = BIG;
        for (int j = 0; j <= LIM; j++) {
                ans = min(ans, next[x][j]);
        }
        

        if (ans > 1e5) cout << -1 << '\n';
        else cout << ans << '\n';
    }

    return 0;
}