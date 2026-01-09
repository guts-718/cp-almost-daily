// try to connect all to 1. as thats always optimal - also [i*j >= i+j] use this to simplify and also take i=1

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    int n;
    ll c;
    cin>>n>>c;

    vector<ll> a(n + 1),p(n);
    for (int i = 1; i <= n; i++) cin >> a[i];
   
    iota(p.begin(), p.end(), 1);

    sort(p.begin(), p.end(), [&](int i, int j) {
        return i * c - a[i] < j * c - a[j];
    });

    ll sum = a[1];
    for (int i = 0; i < n; i++) {
        int u = p[i];
        if (u == 1) continue;

        if (u * c > sum + a[u]) {
            cout << "No" << "\n";
            return;
        }
        sum += a[u];
    }

    cout << "Yes" << "\n";
}

int main() {
 
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}