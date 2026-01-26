#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        vector<int> a(n + 2), b(n + 2);
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];

        vector<bool> ok(n + 2, false);

        for (int pass = 0; pass < 2; pass++) {
            vector<int> nextGreaterA(n + 2);
            vector<int> prevSmallerB(n + 2);
            stack<pair<int,int>> st;

            // next greater element in A
            st.push({INT_MAX, n + 1});
            for (int i = n; i >= 1; i--) {
                while (st.top().first <= a[i]) st.pop();
                nextGreaterA[i] = st.top().second;
                st.push({a[i], i});
            }

            while (!st.empty()) st.pop();

            // previous smaller element in B
            st.push({0, 0});
            for (int i = 1; i <= n; i++) {
                while (st.top().first >= b[i]) st.pop();
                prevSmallerB[i] = st.top().second;
                st.push({b[i], i});
            }

            vector<int> pos(n + 2, 0);

            for (int i = 1; i <= n; i++) {
                pos[a[i]] = i;
                if (a[i] <= b[i] && pos[b[i]]) {
                    int j = pos[b[i]];
                    if (prevSmallerB[i] < j && nextGreaterA[j] > i)
                        ok[i] = ok[i] | true;
                }
            }

            reverse(a.begin() + 1, a.begin() + n + 1);
            reverse(b.begin() + 1, b.begin() + n + 1);
            reverse(ok.begin() + 1, ok.begin() + n + 1);
        }

        bool ans = true;
        for (int i = 1; i <= n; i++)
            ans &= ok[i];

        cout << (ans ? "YES\n" : "NO\n");
    }

    return 0;
}
