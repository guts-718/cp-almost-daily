#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    // pq0 stores: {cost, X, Y}
    // pq1 stores: {cost, real_x, real_y}
    set<vector<int>> pq0, pq1;
    set<pair<int, int>> used;

    auto push = [&](int X, int Y) {
        if (used.count({X, Y})) return;

        int base = 3 * X + 3 * Y + 2;
        pq0.insert({base, X, Y});

        pq1.insert({base,     3 * X + 1, 3 * Y + 1});
        pq1.insert({base + 1, 3 * X + 2, 3 * Y + 1});
        pq1.insert({base + 1, 3 * X + 1, 3 * Y + 2});
        pq1.insert({base + 4, 3 * X + 2, 3 * Y + 2});

        used.insert({X, Y});
    };

    push(0, 0);
    push(0, 1);
    push(1, 0);

    for (int i = 0; i < n; i++) {
        if (t[i] == 0) {
            auto v = *pq0.begin();
            int X = v[1], Y = v[2];

            pq1.erase({3 * X + 3 * Y + 2, 3 * X + 1, 3 * Y + 1});
            pq0.erase(v);

            cout << 3 * X + 1 << " " << 3 * Y + 1 << "\n";

            push(X + 1, Y);
            push(X + 2, Y);
            push(X, Y + 1);
            push(X, Y + 2);
            push(X + 1, Y + 1);
        } else {
            auto v = *pq1.begin();
            int X = v[1] / 3;
            int Y = v[2] / 3;

            pq0.erase({3 * X + 3 * Y + 2, X, Y});
            pq1.erase(v);

            cout << v[1] << " " << v[2] << "\n";

            push(X + 1, Y);
            push(X + 2, Y);
            push(X, Y + 1);
            push(X, Y + 2);
            push(X + 1, Y + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
