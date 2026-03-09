#include <bits/stdc++.h>
using namespace std;
const int mxn = 1e5 + 10;
int par[mxn];

int find(int x) {
   if (par[x] == -1)
      par[x] = x;
   if (par[x] == x)
      return x;
   return par[x] = find(par[x]);
}

void solve() {
   memset(par, -1, sizeof(par));
   int n, m, ans = 0;
   cin >> n >> m;
   for (int i = 0; i < m; i++) {
      int r, c;
      cin >> r >> c;
      if (r == c)
         continue;
      if (find(r) == find(c))
         ans++;
      else
         par[r] = c;
      ans++;
   }
   cout << ans << '\n';
}

int main() {
   int t;
   cin >> t;
   while (t--)
      solve();

   return 0;
}