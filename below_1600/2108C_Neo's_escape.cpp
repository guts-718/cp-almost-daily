#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {

        int n;                      // FIXED
        cin >> n;

        vector<int> a(n);
        for (auto &x : a) cin >> x;

        vector<int> vis(n, 0);

        map<int, vector<array<int,2>>> mp;   // ADDED
        int maxi = -1;
        int cnt = 0;                          // ADDED

        for (int i = 0; i < n; ) {
            int cur = a[i];
            int j = i;
            while (j < n && a[i] == a[j]) j++;

            mp[a[i]].push_back({i, j-1});
            maxi = max(maxi, cur);           // FIXED
            i = j;
        }

        for (auto x : mp[maxi]) {
            int l = x[0], r = x[1];
            for (int i = l; i <= r; i++) {
                vis[i] = 1;
            }
            cnt++;
        }

        for (auto it = mp.rbegin(); it != mp.rend(); it++) {
            if (it->first == maxi) continue;

            for (auto y : it->second) {
                int l = y[0], r = y[1];

                if (!((l > 0 && vis[l-1]) || (r < n-1 && vis[r+1]))) {
                    cnt++;
                }

                for (int i = l; i <= r; i++) {
                    vis[i] = 1;
                }
            }
        }

        cout << cnt << endl;
    }
}