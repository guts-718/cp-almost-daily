#include <bits/stdc++.h>
using namespace std;

bool ok(const vector<long long>& a, int n, int k, int m){
    vector<bool> s(n+1,false);
    vector<int> cur;
    int mex=0, cnt=0;

    for(auto x:a){
        cur.push_back(x);
        s[x]=1;

        while(mex<=n && s[mex]) mex++;

        if(mex>=m){
            cnt++;
            mex=0;
            for(auto y:cur) s[y]=0;
            cur.clear();
        }
    }
    return cnt>=k;
}

void sol(){
    int n,k; 
    cin>>n>>k;

    vector<long long>a(n);
    for(auto &x:a){
        cin>>x;
        x=min(x,(long long)n);
    }

    int l=0,h=n;
    while(l<h){
        int mid=(l+h+1)/2;
        if(ok(a,n,k,mid)) l=mid;
        else h=mid-1;
    }
    cout<<l<<"\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; 
    cin>>t;
    while(t--) sol();
}