#include <bits/stdc++.h>
using namespace std;

int ask(int i, int j) {
    cout << "? " << i << " " << j << endl;
    cout.flush();
    int x;
    cin >> x;
    return x;
}

void answer(int k) {
    cout << "! " << k << endl;
    cout.flush();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        bool found = false;

        // Step 1: only n-1 pairs
        for (int i = 1; i <= 2*n - 2; i += 2) {
            if (ask(i, i+1) == 1) {
                answer(i);
                found = true;
                break;
            }
        }

        if (found) continue;

        // Step 2: use (1,2) and (2n-1,2n)
        if (ask(1, 2*n) == 1) {
            answer(1);
        } else if (ask(2, 2*n) == 1) {
            answer(2);
        } else {
            answer(2*n - 1);
        }
    }

    return 0;
}