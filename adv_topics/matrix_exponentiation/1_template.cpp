
/*
to optimise constant space dp... so first write iterative constant space dp.. then create matrix using the transitions...
TC = K^3 log(n) = n is the exponent and k is the dimension of the vector - k^3 for standard matrix product

to change in template - matrix size in main.. ie - Matrix A(k), the transition matrix (A) , exponent(n,n-1...) and we might need to multiply by some initial vector

works for:
- linear recurrences
- transitions
- DP state jumps
- graph walks


whenever we see - dp[i] depends on last k states then we can always convert
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9+7; // change if needed

struct Matrix {
    int n;
    vector<vector<ll>> m;

    Matrix(int _n, bool ident=false) : n(_n) {
        m.assign(n, vector<ll>(n, 0));
        if (ident)
            for(int i=0;i<n;i++)
                m[i][i] = 1;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
        for(int i=0;i<n;i++)
            for(int k=0;k<n;k++)
                if(m[i][k])
                    for(int j=0;j<n;j++)
                        res.m[i][j] = (res.m[i][j] + m[i][k]*other.m[k][j]) % MOD;
        return res;
    }
};

Matrix power(Matrix base, long long exp){
    Matrix res(base.n, true); // identity
    while(exp){
        if(exp&1) res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}


vector<ll> multiply(const Matrix& M, const vector<ll>& v){
    int n = M.n;
    vector<ll> res(n,0);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            res[i] = (res[i] + M.m[i][j]*v[j]) % MOD;
    return res;
}

vector<ll> apply(Matrix base, long long exp, vector<ll> init){
    Matrix M = power(base, exp);
    return multiply(M, init);
}


int main(){
    long long n;
    cin >> n;

    if(n==0){
        cout << 0;
        return 0;
    }

    // Matrix fib(2);
    // fib.m = {
    //     {1,1},
    //     {1,0}
    // };

    // Matrix ans = power(fib, n-1);

    Matrix fib(2);
    fib.m = {{1,1},{1,0}};

    vector<ll> init = {1,0}; // F1, F0

    auto ans = apply(fib, n-1, init);
    cout << ans[0];


    cout << ans.m[0][0]; // nth Fibonacci
}
