#include <bits/stdc++.h>
#define int long long
using namespace std;

static const int INF = 1e18;
static const int TIME = 500;

vector<vector<int>> dp;

int helper(vector<int>& a, int tim, int ind) {
    if (tim >= TIME) return INF;
    if (ind >= (int)a.size()) return 0;

    int &res = dp[ind][tim];
    if (res != -1) return res;

    res = INF;

    // Take current element
    res = min(res, llabs(tim - a[ind]) + helper(a, tim + 1, ind + 1));

    // Skip current time
    res = min(res, helper(a, tim + 1, ind));

    return res;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int &x : a) cin >> x;

        sort(a.begin(), a.end());

        dp.assign(n, vector<int>(TIME, -1));

        cout << helper(a, 1, 0) << '\n';
    }
}
