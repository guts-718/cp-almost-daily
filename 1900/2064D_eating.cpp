#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Interval = pair<ll,ll>;

/* Merge overlapping intervals */
vector<Interval> mergeIntervals(vector<Interval> v) {
    if (v.empty()) return {};
    sort(v.begin(), v.end());

    vector<Interval> res;
    res.push_back(v[0]);

    for (int i = 1; i < (int)v.size(); i++) {
        if (v[i].first <= res.back().second + 1) {
            res.back().second = max(res.back().second, v[i].second);
        } else {
            res.push_back(v[i]);
        }
    }
    return res;
}

/* Intersection of two interval sets */
vector<Interval> intervalIntersection(vector<Interval> &a,
                                      vector<Interval> &b) {
    vector<Interval> res;
    int i = 0, j = 0;

    while (i < (int)a.size() && j < (int)b.size()) {
        ll L = max(a[i].first, b[j].first);
        ll R = min(a[i].second, b[j].second);
        if (L <= R) res.push_back({L, R});
        if (a[i].second < b[j].second) i++;
        else j++;
    }
    return res;
}

/* Build all x such that (prev XOR x) >= curr */
vector<Interval> valid_range(ll prev, ll curr) {
    vector<Interval> res;
    ll val = 0;

    for (int i = 29; i >= 0; i--) {
        int cb = (curr >> i) & 1;
        int pb = (prev >> i) & 1;

        if (cb == 1) {
            val |= ((1 - pb) << i);
        } else {
            ll L = val | ((1 - pb) << i);
            ll R = L;
            for (int j = i - 1; j >= 0; j--)
                R |= (1LL << j);
            res.push_back({L, R});
            val |= (pb << i);
        }
    }
    res.push_back({val, val});
    return res;
}

/* Binary search x in intervals */
bool inIntervals(const vector<Interval> &v, ll x) {
    int l = 0, r = (int)v.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (v[m].first <= x && x <= v[m].second) return true;
        if (v[m].second < x) l = m + 1;
        else r = m - 1;
    }
    return false;
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    reverse(v.begin(), v.end());

    ll prev = 0;
    vector<Interval> full = {{0, (1LL<<30)-1}};
    vector<vector<Interval>> possible(n);

    for (int i = 0; i < n; i++) {
        auto cur = valid_range(prev, v[i]);
        cur = mergeIntervals(cur);
        cur = intervalIntersection(cur, full);
        full = cur;
        possible[i] = cur;
        prev ^= v[i];
    }

    while (q--) {
        ll x;
        cin >> x;

        int lo = 0, hi = n, ans = n;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (mid == n) break;

            if (inIntervals(possible[mid], x))
                lo = mid + 1;
            else {
                ans = mid;
                hi = mid - 1;
            }
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
