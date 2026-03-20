#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 500;
int prefSum[MAXN + 1][MAXN + 1];

int n, m, k;

// clamp index within bounds
int clamp(int x, int limit) {
    return min(max(x, 0), limit);
}

// get prefix safely
int getPref(int i, int j) {
    return prefSum[clamp(i, n)][clamp(j, m)];
}

void solve() {
    cin >> n >> m >> k;
    k--;  // important adjustment

    vector<string> grid(n);
    int totalGold = 0;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'g') totalGold++;
        }
    }

    // build prefix sum
    memset(prefSum, 0, sizeof(prefSum));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            prefSum[i + 1][j + 1] =
                prefSum[i + 1][j] +
                prefSum[i][j + 1] -
                prefSum[i][j] +
                (grid[i][j] == 'g');
        }
    }

    int best = totalGold;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                int top = i - k;
                int bottom = i + k + 1;
                int left = j - k;
                int right = j + k + 1;

                int goldInside =
                    getPref(bottom, right) -
                    getPref(top, right) -
                    getPref(bottom, left) +
                    getPref(top, left);

                best = min(best, goldInside);
            }
        }
    }

    cout << totalGold - best << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}