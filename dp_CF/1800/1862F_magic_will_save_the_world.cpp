#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main(){
    int t; 
    cin >> t;
    while(t--){
        int w, f;
        cin >> w >> f;

        int n;
        cin >> n;

        vector<int> a(n);
        for(auto &x : a) cin >> x;

        int sum = accumulate(a.begin(), a.end(), 0LL);
        int l = 1, h = 1e6;
        int ans = h;
        vector<int>cur(sum+5,0),prev(sum+5,0);
        for(int i=0;i<=sum+3;i++)prev[i]=i;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=sum+3;j++){
                int temp = 2e9;
                temp = min(prev[j], temp);
            
                if(j >= a[i-1])
                    temp = min(prev[j - a[i-1]], temp);
                
                cur[j]=temp;

            }
            swap(prev,cur);
        }
        while(l <= h){
            int mid = l + (h - l) / 2;
            int one = w * mid;
            one=min(one,sum+2);

            int left = prev[one];
            int need = sum - (one - left);

            if(f * mid >= need){
                ans = mid;
                h = mid - 1;
            }
            else l = mid + 1;
        }
        cout << ans << endl;
    }
}