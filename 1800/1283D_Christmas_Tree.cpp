#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (auto &x : a) cin >> x;

    sort(a.begin(), a.end());

    queue<int> q;
    set<int> st;

    for (int x : a) {
        q.push(x);
        st.insert(x);
    }

    int cnt = 0;
    int ans = 0;
    int dis = 1;
    vector<int> sol;

    while (!q.empty() && cnt < m) {
        int sz = q.size();
        while (sz-- && cnt < m) {
            int x = q.front();
            q.pop();

            int p1 = x + 1;
            if (!st.count(p1)) {
                st.insert(p1);
                q.push(p1);
                sol.push_back(p1);
                ans += dis;
                cnt++;
                if (cnt == m) break;
            }

            int p2 = x - 1;
            if (!st.count(p2) && cnt < m) {
                st.insert(p2);
                q.push(p2);
                sol.push_back(p2);
                ans += dis;
                cnt++;
            }
        }
        dis++;
    }

    sort(sol.begin(), sol.end());

    cout << ans << "\n";
    for (int x : sol) cout << x << " ";
    cout << "\n";

    return 0;
}
