#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    map<long long,long long> f;
    for (auto x : a) f[x]++;

    long long s = 0, c = 0;
    vector<long long> v;

    for (auto &[x,k] : f) {
        long long p = k / 2;
        s += p * 2 * x;
        c += p * 2;
        if (k & 1) v.push_back(x);
    }

    if (s == 0) {
        cout << 0 << '\n';
        return;
    }

    sort(v.begin(), v.end());

    long long ans = 0;

    for (auto x : v)
        if (x < s)
            ans = max(ans, s + x);

    for (int i = 1; i < (int)v.size(); i++)
        if (v[i] - v[i-1] < s)
            ans = max(ans, s + v[i] + v[i-1]);

    if (c > 2)
        ans = max(ans, s);

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
