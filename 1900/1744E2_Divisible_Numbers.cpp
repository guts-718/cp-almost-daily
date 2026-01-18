#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<int> get_divisors(int n) {
    vector<int> divs;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i * i != n) divs.push_back(n / i);
        }
    }
    return divs;
}

void solve() {
    int A, B, C, D;
    cin >> A >> B >> C >> D;

    vector<int> divA = get_divisors(A);
    vector<int> divB = get_divisors(B);

    for (int a : divA) {
        for (int b : divB) {
            int val1 = a * b;
            int val2 = (A / a) * (B / b);

            int x = A + 1;
            int y = B + 1;

            if (x % val1 != 0)
                x += val1 - (x % val1);

            if (y % val2 != 0)
                y += val2 - (y % val2);

            if (x <= C && y <= D) {
                cout << x << " " << y << "\n";
                return;
            }
        }
    }

    cout << "-1 -1\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
