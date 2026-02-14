#include <bits/stdc++.h>
using namespace std;

unordered_map<long long,bool> dp;

long long encode(int f,int tot,int oc,int totodd){
    return (((long long)f<<48) | ((long long)tot<<32) |
            ((long long)oc<<16) | (long long)totodd);
}

bool helper(int n,int odd,int f,int tot,int oc,int totodd){
    int even = n - odd;
    int ec = tot - totodd;

    if(tot == n)
        return oc % 2 == 0;

    long long key = encode(f,tot,oc,totodd);
    if(dp.count(key)) return dp[key];

    bool ans;

    if(f){ // Alice turn
        ans = false;

        if(totodd < odd)
            ans |= helper(n,odd,!f,tot+1,oc+1,totodd+1);

        if(ec < even)
            ans |= helper(n,odd,!f,tot+1,oc,totodd);

    }else{ // Bob turn
        ans = true;

        if(totodd < odd){
            
        }
            ans &= helper(n,odd,!f,tot+1,oc,totodd+1);

        if(ec < even)
            ans &= helper(n,odd,!f,tot+1,oc,totodd);
    }

    return dp[key] = ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--){
        dp.clear();

        int n;
        cin >> n;

        int odd = 0;
        for(int i = 0; i < n; i++){
            int x; cin >> x;
            if(x % 2) odd++;
        }

        if(helper(n,odd,1,0,0,0))
            cout << "Alice\n";
        else
            cout << "Bob\n";
    }
}