#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s1, s2;
        cin >> s1 >> s2;
        int n = s1.size();

        int t, q;
        cin >> t >> q;

        s1 = " " + s1;   // 1-indexed
        s2 = " " + s2;

        vector<bool> blocked(n + 1, false);
        vector<vector<int>> unblock_at(q + t + 5);

        int cnt = 0;          // matching & unblocked
        int blocked_cnt = 0;  // number of blocked positions

        for (int i = 1; i <= n; i++) {
            if (s1[i] == s2[i]) cnt++;
        }

        for (int time = 1; time <= q; time++) {

            // ---- unblock expired positions ----
            for (int pos : unblock_at[time]) {
                blocked[pos] = false;
                blocked_cnt--;
                if (s1[pos] == s2[pos]) cnt++;
            }

            int type;
            cin >> type;

            if (type == 1) {
                int pos;
                cin >> pos;

                // guaranteed not blocked
                if (s1[pos] == s2[pos]) cnt--;
                blocked[pos] = true;
                blocked_cnt++;
                unblock_at[time + t].push_back(pos);
            }

            else if (type == 2) {
                int a, p1, b, p2;
                cin >> a >> p1 >> b >> p2;

                // remove old contributions
                if (!blocked[p1] && s1[p1] == s2[p1]) cnt--;
                if (p2 != p1 && !blocked[p2] && s1[p2] == s2[p2]) cnt--;

                // perform swap
                char &c1 = (a == 1 ? s1[p1] : s2[p1]);
                char &c2 = (b == 1 ? s1[p2] : s2[p2]);
                swap(c1, c2);

                // add new contributions
                if (!blocked[p1] && s1[p1] == s2[p1]) cnt++;
                if (p2 != p1 && !blocked[p2] && s1[p2] == s2[p2]) cnt++;
            }

            else { // type == 3
                if (cnt == n - blocked_cnt)
                    cout << "YES\n";
                else
                    cout << "NO\n";
            }
        }
    }
    return 0;
}
