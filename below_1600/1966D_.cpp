#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main(){
    int t;
    cin >> t;
    while (t--){
        int n, x;
        cin >> n >> x;

        int ans = 0;
        
        for (int a = 1; a <= min(n, x); a++){
            for (int b = 1; a * b <= n and a + b <= x; b++){
                int C = min((n - a * b) / (a + b), x - (a + b));
                ans += C;
            }
        }
        cout << ans << endl;
    }
}