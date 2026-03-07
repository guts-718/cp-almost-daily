#include <bits/stdc++.h>
#define int long long
using namespace std;

int MOD = 10007;

int modpow(int a,long long b,int mod){
    int r=1;
    while(b){
        if(b&1) r=(r*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return r;
}

pair<int,int> geom(long long n,int mod){
    if(n==0) return {1,0};

    auto p=geom(n/2,mod);

    int pow=p.first;
    int sum=p.second;

    int sum2=(sum + pow*sum%mod)%mod;
    int pow2=(pow*pow)%mod;

    if(n%2==0) return {pow2,sum2};

   
    int sum3=(sum2 + pow2)%mod;
    int pow3=(pow2*10)%mod;

    return {pow3,sum3};
}

int32_t main(){

    int K,M;
    int Nm=0,Nm2=0;
    cin>>K>>M;

    int mod2=M*MOD;
    for(int i=0;i<K;i++){
        long long c, l;
        cin>>c>>l;

        auto p1=geom(l,M);
        auto p2=geom(l,mod2);
        
        int sumM2=p2.second;
        int p10m2=p2.first;
        
        int sumM=p1.second;
        int p10m=p1.first;
        
        Nm=(Nm*p10m + c*sumM)%M;
        Nm2=(Nm2*p10m2 + c*sumM2)%mod2;
    }

    int invM=modpow(M,MOD-2,MOD);
    int diff=(Nm2-Nm+mod2)%mod2;
    int ans=(diff%MOD*invM)%MOD;

    cout<<ans<<endl;
}