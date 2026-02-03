#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n;
    cin >> n;

    unordered_map<ll, ll> sumCnt, xCnt;

    for (ll i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        sumCnt[x + y]++;
        xCnt[x]++;
    }

    ll sumOdd = 0, xOdd = 0;

    for (auto& [s, c] : sumCnt)
        if (c & 1) {
            sumOdd = s;
            break;
        }

    for (auto& [x, c] : xCnt)
        if (c & 1) {
            xOdd = x;
            break;
        }

    cout << xOdd << ' ' << (sumOdd - xOdd) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
