#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
	int t;
	cin >> t;
	while (t--) {
		string s;
		cin >> s;
		int sum = 0;
		vector<int> a;
		for (int i = 0; i < int(s.size()); ++i) {
			int x = s[i] - '0';
			sum += x;
			a.push_back(x - (i == 0));
		}
		sort(a.begin(), a.end());
		int ans = 0;
		while (sum > 9) {
			sum -= a.back();
			a.pop_back();
			++ans;
		}
		cout << ans << '\n';
	}
}