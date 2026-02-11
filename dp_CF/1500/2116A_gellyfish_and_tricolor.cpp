#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 4e18;
const int MAXA = 5000;

int G[MAXA + 1][MAXA + 1];   

vector<int> factors(int o) {
    vector<int> ans;
    for (int i = 1; i * i <= o; i++) {
        if (o % i == 0) {
            ans.push_back(i);
            if (i * i != o)
                ans.push_back(o / i);
        }
    }
    return ans;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   
    for (int i = 1; i <= MAXA; i++) {
        for (int j = 1; j <= MAXA; j++) {
            G[i][j] = std::gcd(i, j);
        }
    }

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        sort(a.begin(), a.end());

        set<int> s(a.begin(), a.end());
        vector<int> b(s.begin(), s.end());

        int maxVal = b.back();
        vector<int> dp(maxVal + 5, INF);

        for (auto x : b) dp[x] = 1;

        // sort(b.rbegin(), b.rend());

        
            for (int i = maxVal; i >= 1; i--) {
                for (auto val : b) {
                if (dp[i] == INF) continue;
                int g = G[i][val];        
                dp[g] = min(dp[g], dp[i] + 1);
            }
        }

        int overall_gcd = b[0];
        for (auto x : b)
            overall_gcd = G[overall_gcd][x];

        map<int,int> mp;
        for (auto x : a) mp[x]++;

        int ans = INF;
        vector<int> divisors = factors(overall_gcd);

        for (auto x : divisors) {
            if (mp.count(x)) {
                ans = min(ans, n - mp[x]);
            } else if (dp[x] != INF) {
                ans = min(ans, dp[x] - 1 + n - 1);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}