#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    int t=1;
    cin>>t;

    while(t--){
       int n,k;
       cin>>n>>k;
       vector<int>a(k);
       for(int i=0;i<k;i++){cin>>a[i];a[i]--;}
       vector<int>p(n,2e16);
       for(int i=0;i<k;i++){
           int x;
           cin>>x;
           p[a[i]]=x;
       }
       vector<int>pre(n,0),post(n,0);
       int mini=2e16;
       for(int i=0;i<n;i++){
           mini=min(mini,p[i]-i);
           pre[i]=mini;
       }
       mini=2e16;
       for(int i=n-1;i>=0;i--){
           mini=min(mini,p[i]+i);
           post[i]=mini;
       }
       for(int i=0;i<n;i++){
           cout<<min(pre[i]+i,post[i]-i)<<" ";
       }
       cout<<endl;
    }
}