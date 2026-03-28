#include<bits/stdc++.h>
#define ld long double
using namespace std;
const int N=1e5+5;
ld c[N],p[N];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int cv,pv;
		cin>>cv>>pv;
		c[i]=cv,p[i]=pv/100.0;
	}
	ld ans=0;
	for(int i=n;i>=1;i--){
		ans=max(ans,ans*(1-p[i])+c[i]);
	}
	cout<<fixed<<setprecision(10)<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	for(int i=1;i<=T;i++) solve();
}