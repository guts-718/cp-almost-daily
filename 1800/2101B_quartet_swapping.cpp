#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> fen;

void update(int i) {
    while (i <= n) {
        fen[i]++;
        i += i & -i;
    }
}

int query(int i) {
    int s = 0;
    while (i > 0) {
        s += fen[i];
        i -= i & -i;
    }
    return s;
}

int invCount(const vector<int>& v) {
    fen.assign(n + 1, 0);
    int res = 0;
    for (int i = (int)v.size() - 1; i >= 0; i--) {
        res += query(v[i]);
        update(v[i]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;

        vector<int> odd, even;
        for (int i = 1; i <= n; i++) {
            int x; 
            cin >> x;
            if (i & 1) odd.push_back(x);
            else even.push_back(x);
        }

        bool flip = (invCount(odd) % 2 != invCount(even) % 2);

        sort(odd.begin(), odd.end());
        sort(even.begin(), even.end());

        vector<int> ans(n + 1);
        int i1 = 0, i2 = 0;
        for (int i = 1; i <= n; i++) {
            if (i & 1) ans[i] = odd[i1++];
            else ans[i] = even[i2++];
        }

        if (flip) swap(ans[n], ans[n - 2]);

        for (int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << "\n";
    }
}
