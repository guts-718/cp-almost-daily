#include <bits/stdc++.h>
using namespace std;

bool containsSeven(long long n) {
    while (n > 0) {
        if (n % 10 == 7)
            return true;
        n /= 10;
    }
    return false;
}

void solve() {
    long long n;
    cin >> n;

    if (containsSeven(n)) {
        cout << 0 << '\n';
        return;
    }

    long long ans = 9;

    for (long long k = 1; k <= 9; k++) {
        long long temp = n - k;
        long long best = 7;

        while (temp > 0) {
            long long digit = temp % 10;
            best = min(best, (7 - digit + 10) % 10);
            temp /= 10;
        }

        if (best <= k)
            ans = min(ans, k);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}