#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e9;

// Normal DFS check function
bool dfs(int v, int x, const vector<int>& a,
         const vector<vector<int>>& g) {

    if (x > INF) return false;

    bool isLeaf = true;

    // If not root
    if (v != 0) {
        x+=max(0,x-a[v]);
    }

    for (int child : g[v]) {
        isLeaf = false;
        if (!dfs(child, x, a, g)) {
            return false;
        }
    }

    if (isLeaf) {
        return x <= a[v];
    }

    return true;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int &x : a) {
            cin >> x;
        }

        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            g[p - 1].push_back(i);
        }

        int left = 1, right = INF;
        int ans = 0;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (dfs(0, mid, a, g)) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        cout << a[0] + ans << "\n";
    }

    return 0;
}
