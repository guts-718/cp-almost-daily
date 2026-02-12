#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 1e9 + 7;

int modpow(int a, int b) {
    int ans = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.length();

    vector<int> a(n, 0);
    int cur = 0;
    for (int i = 0; i < n; i++) {
        int dig = s[i] - '0';
        cur = (cur * 10 + dig) % mod;
        a[i] = cur;
        if (i) a[i] = (a[i] + a[i - 1]) % mod;
    }

    vector<int> b(n + 1, 0), c(n + 1, 0);
    int po = 0;
    for (int i = n - 1; i >= 0; i--) {
        int dig = s[i] - '0';
        int pp = modpow(10, po);
        int op = (pp * dig) % mod;

        c[i] = po;
        b[i] = (b[i + 1] + op) % mod;
        po++;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int ox = ((i + 1) % mod * b[i + 1]) % mod;
        int oy = 0;
        if (i) {
            oy = (a[i - 1] * modpow(10, c[i])) % mod;
        }
        ans = (ans + ox + oy) % mod;
    }

    cout << ans << "\n";
    return 0;
}
