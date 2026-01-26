#include <bits/stdc++.h>
using namespace std;

int INF = 1e9;

int main() {
   
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<bool> present(n + 1, false);
        vector<int> a(n);
        
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            present[a[i]] = true;
        }

        vector<int> dp(n + 5, INF);

        for (int v = 1; v <= n; v++) {
            if (present[v]) dp[v] = 1;
        }

        for (int v = 1; v <= n; v++) {
            if (!present[v]) continue;
            for (int x = v; x <= n; x += v) {
                if (dp[x / v] != INF) {
                    dp[x] = min(1+dp[x / v],dp[x]);
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            if (dp[i] >= 1e8) cout << -1 << " ";
            else cout << dp[i] << " ";
        }
        cout << endl;
    }
    return 0;
}