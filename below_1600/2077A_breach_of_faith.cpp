#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
	// your code goes here
    int t;
    cin>>t;
    while(t--){
       int n;
       cin>>n;
       vector<int>a(2*n);
       for(auto &x:a)cin>>x;
       sort(a.begin(),a.end());
       vector<int>o,e;
       int odd=0,even=0;
       for(int i=0;i<2*n;i++){
           if(i==0){
               odd+=a[i];
               o.push_back(a[i]);
           }else if(i<=n-1){
               even+=a[i];
               e.push_back(a[i]);
           }else{
               odd+=a[i];
               o.push_back(a[i]);
           }
       }
       int j=0,k=0;
       e.push_back(abs(odd-even));
       for(int i=0;i<=2*n;i++){
           if(i%2==0){
               cout<<o[j]<<" ";
               j++;
           }else{
               cout<<e[k]<<" ";
               k++;
           }
       }
       cout<<endl;
    }
}
