#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n), b(n, 0);
        for (int i = 0; i < n; i++) cin >> a[i];

        int ans = 0;

        for (int i = 0; i < n; i++) {
            int maxi = min(n - 1, i + a[i]);

            if (a[i] >= b[i]) {
                for (int j = i + 1; j <= maxi; j++) {
                    b[j]++;
                }
                ans += max(a[i] - b[i], 0LL);
            } else {
                for (int j = i + 1; j <= maxi; j++) {
                    b[j]++;
                }
                if (i + 1 < n) {
                    b[i + 1] += (b[i] - a[i]);
                }
            }
        }

        cout << ans - 1 << '\n';
    }

    return 0;
}
