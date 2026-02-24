#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main(){
    int t; 
    cin >> t;
    while(t--){
       int n;
       cin>>n;
       vector<int>a(n);
       for(int i=0;i<n;i++)cin>>a[i];
       string s;
       cin>>s;
       vector<int>zero(32,0),ones(32,0);
       vector<vector<int>>v(n,vector<int>(32,0));
       for(int i=0;i<n;i++){
           int x=a[i];
           for(int j=0;j<=31;j++){
               if((x>>j)&1){
                   v[i][j]++;
                   if(s[i]=='0'){
                      zero[j]++;
                   }else ones[j]++;
                   
                   zero[j]%=2;
                   ones[j]%=2;
               }
               if(i)v[i][j]+=v[i-1][j];
               
           }
       }
       int q;
       cin>>q;
       while(q--){
           int op;
           cin>>op;
           if(op==1){
               int l,r;
               cin>>l>>r;l--;r--;
            //   vector<int>temp(32,0);
               for(int i=0;i<=31;i++){
                   int x=v[r][i]-(l?v[l-1][i]:0);
                   ones[i]+=x;
                   zero[i]+=x;
                   ones[i]%=2;
                   zero[i]%=2;
               }
               
               
           }else{
               int y;
               cin>>y;
               long long ans=0;
               if(y==0){
                   for(int i=0;i<=31;i++){
                       if(zero[i])ans+=(1LL<<i);
                   }
               }else{
                   for(int i=0;i<=31;i++){
                       if(ones[i])ans+=(1LL<<i);
                   }
               }
               cout<<ans<<" ";
           }
       }
       cout<<endl;
    }
}