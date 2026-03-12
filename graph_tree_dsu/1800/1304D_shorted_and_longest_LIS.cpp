#include <bits/stdc++.h>

#define int long long
#define F first
#define S second
#define pb push_back
#define pii pair <int,int>

using namespace std;

int32_t main(){
    ios::sync_with_stdio(0);cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        int mx[n],mn[n];
        for(int i=0;i<n;i++) mx[i]=i+1,mn[i]=n-i;
        int j=0;
        for(int i=0;i<n-1;i=j){
            while(j<n &&  s[i]==s[j]) j++;
            if(s[i]=='<') reverse(mn+i,mn+j+1);
            else reverse(mx+i,mx+j+1);
        }
        for(int i=0;i<n;i++) cout<<mn[i]<<" ";
        cout<<endl;
        for(int i=0;i<n;i++) cout<<mx[i]<<" ";
        cout<<endl;
    }
    return 0;
}