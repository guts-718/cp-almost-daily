#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Segment = pair<ll, ll>;

vector<Segment> makeZero(string s) {
    vector<Segment> operations;

    string compressed = s;
    compressed.erase(unique(compressed.begin(), compressed.end()), compressed.end());

    if (compressed.size() == s.size()) {
        operations.emplace_back(0, 2);
        for (int i = 0; i < 3; i++)
            s[i] = '0' + '1' - s[i];
    }

    ll n = s.size();
    ll left = -1, right = -1;

    for (ll i = 0; i + 1 < n; i++) {
        if (s[i] == s[i + 1]) {
            left = i;
            right = i + 1;
            break;
        }
    }

    while (right + 1 < n && s[right + 1] == s[left]) right++;

    while (left != 0 || right != n - 1) {
        operations.emplace_back(left, right);

        for (ll i = left; i <= right; i++)
            s[i] = '0' + '1' - s[i];

        while (right + 1 < n && s[right + 1] == s[left]) right++;
        while (left > 0 && s[left - 1] == s[left]) left--;
    }

    if (s[left] == '1') {
        operations.emplace_back(0, n - 1);
    }

    return operations;
}

void solve() {
    ll n;
    cin >> n;

    string s, t;
    cin >> s >> t;

    auto opsS = makeZero(s);
    auto opsT = makeZero(t);

    if (!opsS.empty() && !opsT.empty() && opsS.back() == opsT.back()) {
        opsS.pop_back();
        opsT.pop_back();
    }

    cout << opsS.size() + opsT.size() << '\n';

    for (auto [l, r] : opsS)
        cout << l + 1 << " " << r + 1 << '\n';

    for (int i = (int)opsT.size() - 1; i >= 0; i--)
        cout << opsT[i].first + 1 << " " << opsT[i].second + 1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
