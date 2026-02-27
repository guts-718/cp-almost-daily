#include <bits/stdc++.h>
using namespace std;

int ceilDiv(int a, int b) {
    return (a + b - 1) / b;
}

int check(const string& a, const vector<bool>& diff, bool target) {
    int total = 0, ones = 0;

    for (int i = 0; i < a.size(); ++i) {
        if (diff[i] == target) {
            total++;
            if (a[i] == '1') ones++;
        }
    }

    if (((total & 1) ^ target) && ones == ceilDiv(total, 2))
        return total;

    return INT_MAX;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        string a, b;
        cin >> n >> a >> b;

        vector<bool> diff(n);
        for (int i = 0; i < n; ++i)
            diff[i] = (a[i] != b[i]);

        int ans = min(check(a, diff, true), check(a, diff, false));
        cout << (ans == INT_MAX ? -1 : ans) << "\n";
    }
}