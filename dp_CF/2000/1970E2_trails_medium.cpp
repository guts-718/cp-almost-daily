#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1e9 + 7;

using Matrix = vector<vector<ll>>;

/* Matrix multiplication */
Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<ll>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (A[i][k] == 0) continue;
            for (int j = 0; j < n; j++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

/* Matrix exponentiation */
Matrix matrix_power(Matrix base, long long exp) {
    int n = base.size();
    Matrix result(n, vector<ll>(n, 0));

    // Identity matrix
    for (int i = 0; i < n; i++)
        result[i][i] = 1;

    while (exp > 0) {
        if (exp & 1)
            result = multiply(result, base);
        base = multiply(base, base);
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    ll n;
    cin >> m >> n;

    vector<ll> a(m), b(m);
    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    // Build transition matrix T
    Matrix T(m, vector<ll>(m, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            ll val = 0;
            val = (val + a[i] * b[j]) % MOD;
            val = (val + a[i] * a[j]) % MOD;
            val = (val + b[i] * a[j]) % MOD;
            T[i][j] = val;
        }
    }

    // T^n
    Matrix Tn = matrix_power(T, n);

    // dp_n = vector of all 1s
    ll ans = 0;
    for (int j = 0; j < m; j++) {
        ans = (ans + Tn[0][j]) % MOD;
    }

    cout << ans << '\n';
    return 0;
}
