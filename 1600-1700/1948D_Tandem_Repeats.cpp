#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();

        int ans = 0;

        for (int L = 1; 2 * L <= n; L++) {
            int bad = 0;

            // initial window [0 .. 2L-1]
            for (int i = 0; i < L; i++) {
                char a = s[i];
                char b = s[i + L];
                if (a != b && a != '?' && b != '?') {
                    bad++;
                }
            }

            if (bad == 0) ans = max(ans, 2 * L);

            // slide window
            for (int start = 1; start + 2 * L <= n; start++) {
                // remove left pair
                {
                    char a = s[start - 1];
                    char b = s[start - 1 + L];
                    if (a != b && a != '?' && b != '?') {
                        bad--;
                    }
                }

                // add right pair
                {
                    char a = s[start + L - 1];
                    char b = s[start + 2 * L - 1];
                    if (a != b && a != '?' && b != '?') {
                        bad++;
                    }
                }

                if (bad == 0) ans = max(ans, 2 * L);
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
