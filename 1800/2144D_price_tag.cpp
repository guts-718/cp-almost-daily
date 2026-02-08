#include <algorithm>
#include <iostream>
#include <vector>
#define SZ(X) (int)(X).size()
using namespace std;
const int MAX_V = 200'001;
using ll = long long;
void solve() {
    int n, y;
    cin >> n >> y;
    vector<int> cnt(MAX_V), dp(MAX_V);
    vector<int> mi(n + 1, MAX_V);
    vector<ll> award(MAX_V);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        cnt[c]++;
        dp[c]++;
    }
    for (int i = 1; i < MAX_V; i++) dp[i] += dp[i - 1];
    auto get_sum = [&](int l, int r) -> ll {
        if (r >= MAX_V) r = MAX_V - 1;
        if (l <= 0) return dp[r];
        return dp[r] - dp[l - 1];
    };
    for (int x = 2; x < MAX_V; x++) {
        int same_cnt = 0;
        for (int i = 1; i * x - x + 1 < MAX_V; i++) {
            ll num = get_sum(i * x - x + 1, i * x);
            award[x] += num * i;
            same_cnt += min<ll>(cnt[i], num);
        }
        if (mi[same_cnt] == MAX_V) mi[same_cnt] = x;
    }
    ll ans = -1e18;
    for (int i = 0; i <= n; i++) {
        if (mi[i] == MAX_V) continue;
        ans = max(ans, award[mi[i]] - (ll)(n - i) * y);
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) solve();
}