#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int a[n];
        int x,y;
        for(int i=0;i<n;i++){
            cin>>a[i];
            if(a[i]==1) x = i;
            if(a[i]==n) y = i;
        }
        string s;
        cin>>s;
        if(s[0]=='1' || s[n-1]=='1' || s[x]=='1'|| s[y]=='1'){
            cout<<-1<<endl;
        }
        else{
            cout<<5<<endl;
            cout<<1<<" "<<x+1<<endl;
            cout<<1<<" "<<y+1<<endl;
            cout<<x+1<<" "<<n<<endl;
            cout<<y+1<<" "<<n<<endl;
            cout<<min(x,y)+1<<" "<<max(x,y)+1<<endl;
        }
    }
    return 0;
}