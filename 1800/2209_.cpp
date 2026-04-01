#include "bits/stdc++.h"

using namespace std;

#define ll long long
const int MAXP = 150;
const ll INF = 1e18;

int prime[MAXP];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

	fill(prime, prime + MAXP, 1);
	vector<ll> ps = {-1, 1};
	for (int i = 2; i < MAXP; i++) {
		if (!prime[i]) continue;
		ps.push_back(i);
		for (int j = i * 2; j < MAXP; j += i) {
			prime[j] = 0;
		}
	}

	int P = ps.size();
	// cerr << P << endl;

	int t; cin >> t;
	while (t--) {
	
		int n; cin >> n;

		vector<ll> a(n), b(n);
		for (ll &i : a) {
			cin >> i;
		}
		for (ll &i : b) {
			cin >> i;
		}

		vector<ll> need(n, 1);
		for (int i = 0; i < n; i++) {
			if (i) need[i] = lcm(need[i], gcd(a[i], a[i - 1]));
			if (i + 1 < n) need[i] = lcm(need[i], gcd(a[i], a[i + 1]));
		}

		vector<ll> dp(P, -INF);
		dp[0] = 0;
		for (int i = 1; i < P; i++) {
			if (need[0] * ps[i] <= b[0] && need[0] * ps[i] != a[0]) {
				dp[i] = 1;
			}
		}

		for (int i = 1; i < n; i++) {
			vector<ll> nd(P, -INF);
			ll goal = gcd(a[i - 1], a[i]);
			// keep
			for (int j = 0; j < P; j++) {
				ll val = (j == 0 ? a[i - 1] : need[i - 1] * ps[j]);
				if (gcd(val, a[i]) == goal) {
					nd[0] = max(nd[0], dp[j]);
				}
			}

			// chg?
			for (int j = 1; j < P; j++) {
				if (need[i] * ps[j] > b[i]) continue;
				if (need[i] * ps[j] == a[i]) continue;
				for (int k = 0; k < P; k++) {
					ll pv = (k == 0 ? a[i - 1] : need[i - 1] * ps[k]);
					if (gcd(need[i] * ps[j], pv) == goal) {
						nd[j] = max(nd[j], dp[k] + 1);
					}
				}
			}
			dp = nd;
		}
		
		ll ans = *max_element(dp.begin(), dp.end());

		cout << ans << "\n";

	}
  
}

