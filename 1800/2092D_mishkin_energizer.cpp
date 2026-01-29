#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> ans;
    int last = -1;

    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) continue;

        int len = i - last;
        int curSize = ans.size();

        for (int k = 0; k < 2 * len; k++) {
            ans.push_back(i + curSize + 1);
        }

        last = i;
    }

    if (last == -1) {
        cout << "-1\n";
        return;
    }

    int len = n - last - 1;
    for (int k = 0; k < 2 * len; k++) {
        ans.push_back(n + ans.size() - len);
    }

    cout << ans.size() << "\n";
    for (int v : ans) {
        cout << v << "\n";
    }
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
