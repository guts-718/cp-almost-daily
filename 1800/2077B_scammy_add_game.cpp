#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    cin >> n;

    // mult[i][j] = multiplier for side j at step i (default 1)
    vector<array<ll, 2>> mult(n, {1, 1});
    // add[i] = total '+' contribution at step i
    vector<ll> add(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            char op;
            ll x;
            cin >> op >> x;
            if (op == 'x')
                mult[i][j] = x;
            else
                add[i] += x;
        }
    }

    // dp[i][j] = best possible value from step i if we choose side j
    vector<array<ll, 2>> dp(n + 1, {1, 1});

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 2; j++) {
            ll best = 0;
            ll a = mult[i][j];
            for (ll k = 1; k <= a; k++) {
                best = max(best,
                            k * dp[i + 1][j] +
                            (a - k) * dp[i + 1][j ^ 1]);
            }
            dp[i][j] = best;
        }
    }

    ll left = 1, right = 1;

    for (int i = 0; i < n; i++) {
        ll gain = add[i]
                + left  * (mult[i][0] - 1)
                + right * (mult[i][1] - 1);

        if (dp[i + 1][0] >= dp[i + 1][1])
            left += gain;
        else
            right += gain;
    }

    cout << left + right << '\n';
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














#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    cin >> n;

    vector<array<char, 2>> op(n + 1);
    vector<array<ll, 2>> val(n + 1);

    for (int i = 1; i <= n; i++) {
        char o1, o2;
        ll v1, v2;
        cin >> o1 >> v1 >> o2 >> v2;
        op[i] = {o1, o2};
        val[i] = {v1, v2};
    }
    op[0] = {'+', '+'};
    val[0] = {1, 1};

    vector<array<ll, 2>> dp(n + 2);
    dp[n + 1] = {1, 1};

    for (int i = n; i >= 1; i--) {
        ll mx = max(dp[i + 1][0], dp[i + 1][1]);

        if (op[i][0] == 'x')
            dp[i][0] = dp[i + 1][0] + (val[i][0] - 1) * mx;
        else
            dp[i][0] = dp[i + 1][0];

        if (op[i][1] == 'x')
            dp[i][1] = dp[i + 1][1] + (val[i][1] - 1) * mx;
        else
            dp[i][1] = dp[i + 1][1];
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll add = 0;
        if (op[i][0] == '+') add += val[i][0];
        if (op[i][1] == '+') add += val[i][1];
        ans += add * max(dp[i + 1][0], dp[i + 1][1]);
    }

    ans += dp[1][0] + dp[1][1];

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
