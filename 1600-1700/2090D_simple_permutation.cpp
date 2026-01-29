#include <bits/stdc++.h>
using namespace std;

vector<int> spf;

// Smallest Prime Factor sieve
void sieve(int N) {
    spf.resize(N + 1);
    for (int i = 0; i <= N; i++) spf[i] = i;

    for (int i = 2; i * i <= N; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= N; j += i) {
                spf[j] = min(spf[j], i);
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;

    int x = n / 3 - 1;
    if (x <= 0) {
        for (int i = 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << "\n";
        return;
    }

    vector<int> ans;

    for (int i = x; i <= n / 2; i++) {
        if (i != 1 && spf[i] == i) {   // i is prime
            for (int j = 1; j <= i; j++) {
                ans.push_back(j);
                if (i != j)
                    ans.push_back(2 * i - j);
            }

            for (int j = 2 * i; j <= n; j++) {
                ans.push_back(j);
            }

            for (int v : ans) {
                cout << v << " ";
            }
            cout << "\n";
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve(200000);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}