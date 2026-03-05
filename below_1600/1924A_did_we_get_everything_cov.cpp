#include <bits/stdc++.h>
#define int long long
using namespace std;


int32_t main() {
    int t;
    cin >> t;

    while(t--){
     int n,k,m;
     cin>>n>>k>>m;
     string s;
     cin>>s;
     set<char>st;
     int cnt=0;
     string ans="";
     for(auto x:s){
         st.insert(x);
         if(st.size()==k){
             st.clear();
             cnt++;
             ans+=x;
         }
     }
     if(ans.size()>=n){
         cout<<"YES"<<endl;
         
     }else{
        //  string ans="";
         for(int i=0;i<k;i++){
             if(st.find(i+'a')==st.end()){
                 ans+=char(i+'a');
                 break;
             }
             
         }
         if(ans.size()==0){
             ans+='a';
             while(cnt--)ans+='a';
         }else{
         while(ans.size()<n)ans+=ans.back();
         }
         cout<<"NO"<<endl;
         cout<<ans<<endl;
     }
     
       
    }
}