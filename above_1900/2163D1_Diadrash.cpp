#include <bits/stdc++.h>
using namespace std;
 
int LIM, Q;
 
int ask(int l, int r) {
    Q++;
    assert(Q <= LIM);
    cout << "? " << l << " " << r << endl;
    int ans; cin >> ans;
    return ans;
}
 
bool inside(int l, int r, bool toL, int n) {
    int midL = n / 2;
    if (toL) {
        return l <= midL;
    }
    else return r > midL;
}
 
void solve() {
    int n, q; cin >> n >> q;
    Q = 0;
    LIM = max(30, n / 2 + n % 2 + 5);
    vector<int> maxR(n+1, 0);
    for (int i = 1; i <= q; i++) {
        int l, r; cin >> l >> r;
        maxR[l] = max(maxR[l], r);
    }
    bool toL = (ask(1, n/2) > 0);
    int ans = 0, mx = 0;
    for (int i = 1; i <= n; i++) {
        if (maxR[i] > mx && inside(i, maxR[i], toL, n)) {
            ans = max(ans, ask(i, maxR[i]));
        }
        mx = max(mx, maxR[i]);
    }
    cout << "! " << ans << endl;
}
 
int main() {
    int t; cin >> t;
    while (t--) solve();
    return 0;
}