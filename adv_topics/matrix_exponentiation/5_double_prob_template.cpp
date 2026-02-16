#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    int n;
    vector<vector<double>> m;

    Matrix(int _n, bool ident=false) : n(_n) {
        m.assign(n, vector<double>(n, 0.0));
        if (ident)
            for(int i=0;i<n;i++)
                m[i][i] = 1.0;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
        for(int i=0;i<n;i++)
            for(int k=0;k<n;k++)
                for(int j=0;j<n;j++)
                    res.m[i][j] += m[i][k]*other.m[k][j];
        return res;
    }
};

Matrix power(Matrix base, long long exp){
    Matrix res(base.n, true);
    while(exp){
        if(exp&1) res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

vector<double> multiply(const Matrix& M, const vector<double>& v){
    int n = M.n;
    vector<double> res(n,0.0);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            res[i] += M.m[i][j]*v[j];
    return res;
}

vector<double> apply(Matrix base, long long exp, vector<double> init){
    Matrix M = power(base, exp);
    return multiply(M, init);
}

int main(){
    long long n;
    double p;
    cin >> n >> p;

    Matrix fib(2);
    fib.m = {{1-p,p},{p,1-p}};

    vector<double> init = {1.0,0.0};

    auto ans = apply(fib, n, init);

    cout << fixed << setprecision(10);
    cout << ans[0] << endl;
}
