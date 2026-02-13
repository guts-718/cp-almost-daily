#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> p(n), q(n), invp(n), invq(n);

    for (int i = 0; i < n; i++) {
        cin >> p[i];
        --p[i];
        invp[p[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        cin >> q[i];
        --q[i];
        invq[q[i]] = i;
    }

    int leftBound = n;
    int rightBound = -1;
    ll ans = 0;

    for (int mex = 1; mex <= n; mex++) {
        leftBound  = min(leftBound,  invp[mex - 1]);
        rightBound = max(rightBound, invp[mex - 1]);
        leftBound  = min(leftBound,  invq[mex - 1]);
        rightBound = max(rightBound, invq[mex - 1]);

        int L = 0;
        int R = n - 1;

        if (mex < n) {
            if (invp[mex] < leftBound)
                L = max(L, invp[mex] + 1);
            else
                R = min(R, invp[mex] - 1);

            if (invq[mex] < leftBound)
                L = max(L, invq[mex] + 1);
            else
                R = min(R, invq[mex] - 1);
        }

        if (L <= leftBound && rightBound <= R) {
            ans += 1LL * (leftBound - L + 1) * (R - rightBound + 1);
        }
    }

    int leftLen  = min(invp[0], invq[0]);
    int rightLen = min(n - 1 - invp[0], n - 1 - invq[0]);
    int midLen   = abs(invp[0] - invq[0]) - 1;

    ans += 1LL * leftLen  * (leftLen + 1)  / 2;
    ans += 1LL * rightLen * (rightLen + 1) / 2;
    ans += 1LL * midLen   * (midLen + 1)   / 2;

    cout << ans << "\n";
    return 0;
}
