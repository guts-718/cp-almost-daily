#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    

    int t;
    cin >> t;
    while (t--) {
        int n;
        int Ax, Ay, Bx, By;
        cin >> n >> Ax >> Ay >> Bx >> By;

        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++) cin >> x[i];
        for (int i = 0; i < n; i++) cin >> y[i];

        map<int, pair<int,int>> mp;
        for (int i = 0; i < n; i++) {
            if (!mp.count(x[i]))
                mp[x[i]] = {y[i], y[i]};
            else {
                mp[x[i]].second = max(mp[x[i]].second, y[i]);
                mp[x[i]].first = min(mp[x[i]].first, y[i]);
               
            }
        }

        vector<pair<int, pair<int,int>>> v;
        for (auto &p : mp){
            v.push_back({p.first, p.second});
        }

        int dpLow, dpHigh;
        int prevX = Ax;
        int cx = v[0].first;
        int dx = cx - Ax;
        int lo = v[0].second.first,hi = v[0].second.second;
        int span = hi - lo;
       
        prevX = cx;
        dpLow = dx + abs(Ay - hi) + span;
        dpHigh = dx + abs(Ay - lo) + span;
       
        

        for (int i = 1; i < (int)v.size(); i++) {
            cx = v[i].first,lo = v[i].second.first;
            dx = cx - prevX;
            hi = v[i].second.second;
            span = hi - lo;
            

            int phi = v[i-1].second.second;
            int plo = v[i-1].second.first;

            int newLow = min(
                dpLow + abs(plo - hi) + span +dx,
                dpHigh + abs(phi - hi) + span +dx
            );

            int newHigh = min(
                dpLow  + abs(plo - lo) + span+dx,
                dpHigh + abs(phi - lo) + span +dx
            );
            
           prevX = cx;
           dpHigh = newHigh;
           dpLow = newLow;
           
        }

        int lastX;
        lastX= v.back().first,lo = v.back().second.first;
        dx = Bx - lastX, hi = v.back().second.second;;

        int ans = min(
            dpHigh + abs(By - hi) +dx,
            dpLow  + dx + abs(By - lo)
        );

        cout << ans << endl;
    }
    return 0;
}