#include <bits/stdc++.h>
using namespace std;

int main(){
        int n;
        cin>>n;
        vector<int> a(n+1);
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }

        for(int i=n;i>=1;i--){
            for(int j=2*i;j<=n;j+=i){
                a[i]=max(a[i],a[j]);
            }
        }

        sort(a.begin()+1,a.end(),greater<int>());

        long long sum=0;
        int mod=998244353;
        for(int i=1;i<=n;i++){
            sum=(2*sum+a[i])%mod;
        }
        cout<<sum<<endl;
}