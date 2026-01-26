#include <bits/stdc++.h>
 
#define sz(x) (int)(x.size())
#define pb push_back
 
using namespace std; 
const int N = 2e5 + 12;
 
int n, x, y, a, b;
vector <int> L, g[N];
 
void dfs( int v, int p = 0 )
{
	L.pb(v);
	
	for( auto to : g[v] )
	{
		if( to != p ) dfs(to, v);
	}
}
int ask( int a, int b )
{
	cout << "? " << a << ' ' << b << endl;
	int res; cin >> res; return res;
}
void solve()
{
	cin >> n;
	
	L.clear();
	for( int i = 1; i <= n; i ++ ) g[i].clear();
	
	for( int i = 1; i < n; i ++ )
	{
		cin >> a >> b;
		g[a].pb(b), g[b].pb(a);
	}
	dfs(1, 0);
	
	for( int i = 0; i < sz(L) - 1; i += 2 )
	{
		a = L[i], b = L[i + 1];
		
		if( ask(a, b) == 1 )
		{
			if( ask(a, a) == 1 ) cout << "! " << a << endl;
			else cout << "! " << b << endl;
			return;
		}
	}
	cout << "! " << L.back() << endl;
}
int main()
{
	int t; cin >> t;
	while( t -- ) solve();
}