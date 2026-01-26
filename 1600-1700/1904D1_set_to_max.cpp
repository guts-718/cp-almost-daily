#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2000005;

int n;
int a[N], b[N];

struct Node {
    int idx, val;
};

bool cmp(const Node &x, const Node &y) {
    return x.val < y.val;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;

        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<Node> v(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            v[i] = {i, b[i]};
        }

        sort(v.begin() + 1, v.end(), cmp);

        bool ok = true;

        for (int i = 1; i <= n; i++) {
            int x = v[i].idx;
            int target = v[i].val;
            bool found = false;

            for (int j = x; j >= 1; j--) {
                if (a[j] > target) break;
                if (b[j] < target) break;
                
                if (a[j] == target) {
                    found = true;
                    for(int k=x;k>=j;k--){
                        a[k]=target;
                    }
                   break;
                }
            }

            for (int j = x; j <= n; j++) {
                if (a[j] > target) break;
                if (b[j] < target) break;
                //a[j]=target;
                if (a[j] == target) {
                    found = true;
                    //found = true;
                    for(int k=x;k<=j;k++){
                        a[k]=target;
                    }
                    break;
                }
            }

            if (found) {
                a[x] = target;
            } else {
                ok = false;
                break;
            }
        }

        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}
