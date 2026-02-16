#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9+7; // change if needed

template<int N>
struct Matrix {
    ll m[N][N];

    Matrix(bool ident=false){
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                m[i][j] = (ident && i==j);
    }

    static Matrix multiply(const Matrix& A, const Matrix& B){
        Matrix res;
        for(int i=0;i<N;i++)
            for(int k=0;k<N;k++)
                if(A.m[i][k])
                    for(int j=0;j<N;j++)
                        res.m[i][j] = (res.m[i][j] + A.m[i][k]*B.m[k][j]) % MOD;
        return res;
    }

    static Matrix power(Matrix base, long long exp){
        Matrix res(true);
        while(exp){
            if(exp&1) res = multiply(res, base);
            base = multiply(base, base);
            exp >>= 1;
        }

        return res;
    }

    static array<ll,N> apply(Matrix base, long long exp, array<ll,N> vec){
        Matrix M = power(base, exp);
        array<ll,N> res{};
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                res[i] = (res[i] + M.m[i][j]*vec[j]) % MOD;
        return res;
    }
};



int main(){
    long long n;
    cin >> n;

    if(n==0){
        cout<<0;
        return 0;
    }

    Matrix<2> A;
    A.m[0][0]=1; A.m[0][1]=1;
    A.m[1][0]=1; A.m[1][1]=0;

    array<ll,2> init = {1,0}; // F1, F0

    auto ans = Matrix<2>::apply(A, n-1, init);

    cout << ans[0];
}

/*
How to Use for Any Problem
Step 1 — Choose dimension - Matrix<K> A;

Step 2 — Fill transition matrix - A.m[i][j] = ...

Step 3 — Set initial vector - array<ll,K> init = {...};

Step 4 — Compute - auto ans = Matrix<K>::apply(A, exponent, init);
*/
