#include <bits/stdc++.h>
using namespace std;
#define int long long

int lcm(int a, int b) {
    return (a / __gcd(a, b)) * b;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b, c, m;
        cin >> a >> b >> c >> m;  // fixed input

        int ab = m / lcm(a, b);
        int bc = m / lcm(b, c);
        int ca = m / lcm(a, c);
        int abc = m / lcm(lcm(a, b), c);

        int ansa = 6 * (m / a) - 3 * ab - 3 * ca + 2*abc;
        int ansb = 6 * (m / b) - 3 * bc - 3 * ab + 2*abc;
        int ansc = 6 * (m / c) - 3 * ca - 3 * bc + 2*abc;

        cout << ansa << " " << ansb << " " << ansc << endl;
    }
}