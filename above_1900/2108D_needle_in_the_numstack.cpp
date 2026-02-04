#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> left(k), right(k);

    // Query first k
    for (int i = 0; i < k; i++) {
        cout << "? " << i + 1 << endl;
        cin >> left[i];
    }

    // Query last k
    for (int i = 0; i < k; i++) {
        cout << "? " << n - i << endl;
        cin >> right[i];
    }

    if (n == 2 * k) {
        cout << "! " << k << " " << k << endl;
        return;
    }

    int lo = k, hi = n - k - 1;
    int ans = k - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        int mismatchPos = -1;
        for (int j = 0; j < k; j++) {
            int idx = mid - j;
            if (left[idx % k] != right[(n - idx - 1) % k]) {
                mismatchPos = idx;
                break;
            }
        }

        if (mismatchPos == -1) break;

        cout << "? " << mismatchPos + 1 << endl;
        int res;
        cin >> res;

        if (res == left[mismatchPos % k]) {
            ans = mismatchPos;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    int i = ans + 1;
    int v1 = left[i % k];
    int v2 = right[(n - i - 1) % k];

    if (i < n - k && v1 == v2) {
        cout << "! -1" << endl;
    } else {
        int s1 = ans + 1;
        int s2 = n - s1;
        cout << "! " << s1 << " " << s2 << endl;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}