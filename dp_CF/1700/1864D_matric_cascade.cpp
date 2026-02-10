#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 3001;

int n;
string s[MAXN];
vector<vector<int>> v;

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < 3 * n;
}

void solve() {
    v.assign(n, vector<int>(3 * n, 0));

    for (int i = 0; i < n; i++) {
        s[i] = string(n, '0') + s[i] + string(n, '0');
    }

    int ans = 0;

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < (int)s[x].size(); y++) {

            if (valid(x - 1, y + 1))
                v[x][y] ^= v[x - 1][y + 1];

            if (valid(x - 1, y - 1))
                v[x][y] ^= v[x - 1][y - 1];

            if (valid(x - 2, y))
                v[x][y] ^= v[x - 2][y];

            int cur = s[x][y] - '0';

            if (v[x][y] != cur && y >= n && y < 2 * n) {
                v[x][y] ^= 1;
                if (valid(x + 1, y))
                    v[x + 1][y] ^= 1;
                ans++;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        solve();
    }

    return 0;
}