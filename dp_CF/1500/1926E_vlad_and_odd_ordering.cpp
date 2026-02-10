
#include <bits/stdc++.h>

using namespace std;

int main() {
  int tt;
  cin >> tt;
  while (tt--) {
    int n, k;
    cin >> n >> k;
    int x = n;
    int p = 1;
    while (x > 0) {
      int take = x - x / 2;
      if (k <= take) {
        cout << p * (2 * k - 1) << '\n';
        break;
      }
      k -= take;
      p *= 2;
      x /= 2;
    }
  }
  return 0;
}