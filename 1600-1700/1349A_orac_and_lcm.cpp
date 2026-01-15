#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<long long> a(n);
        for (auto &x : a) cin >> x;

        sort(a.begin(), a.end());

        // global gcd
        long long g = a[0];
        for (auto x : a) g = std::gcd(g, x);

        // normalize
        for (auto &x : a) x /= g;

        vector<long long> pre(n, 0), post(n, 0);

        // prefix gcd
        pre[0] = a[0];
        for (int i = 1; i < n; i++)
            pre[i] = std::gcd(pre[i - 1], a[i]);

        // suffix gcd
        post[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--)
            post[i] = std::gcd(post[i + 1], a[i]);

        long long ans = g;

        for (int i = 0; i < n; i++) {
            long long left = (i > 0) ? pre[i - 1] : 0;
            long long right = (i + 1 < n) ? post[i + 1] : 0;

            long long cur;
            if (left == 0) cur = right;
            else if (right == 0) cur = left;
            else cur = std::gcd(left, right);

            ans *= cur;
        }

        cout << ans << "\n";
    }
    return 0;
}
