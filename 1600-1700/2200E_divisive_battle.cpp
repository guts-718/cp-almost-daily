#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)

int primebase(int x) {
    set<int> s;
    for (int i = 2; i*i <= x; i++) {
        while (x % i == 0) {
            s.insert(i);
            x /= i;
        }
    }
    if (x > 1) s.insert(x);
    if (s.size() > 1) return -1;
    if (s.size() == 0) return 1;
    return *s.begin();
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i: a) cin >> i;
    
    // solve
    vector<int> b(n);
    for (int i = 0; i < n; i++) b[i] = primebase(a[i]);
    if (is_sorted(all(a))) {
        cout << "Bob\n";
    } else if (*min_element(all(b)) == -1) {
        cout << "Alice\n";
    } else if (is_sorted(all(b))) {
        cout << "Bob\n";
    } else {
        cout << "Alice\n";
    }
}

signed main() {
    int t = 1;
    cin >> t;
    while (t--) solve();
}