#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<vector<int>>dp;
int helper(string &a,string &b,string &c,int i,int j){
    int k=i+j;
    if(i==a.size()){
        int cnt=0;
        for(int o=k;o<c.size();o++){
            if(c[o]!=b[j]){
                cnt++;
            }
            j++;
        }
        return cnt;
    }
    if(j==b.size()){
        int cnt=0;
        for(int o=k;o<c.size();o++){
            if(c[o]!=a[i]){
                cnt++;
            }
            i++;
        }
        return cnt;
    }
    if(dp[i][j]!=-1)return dp[i][j];
    int ans=2e7;
    if(a[i]==c[k]){
        ans=min(ans,helper(a,b,c,i+1,j));
    }else ans=min(ans,1+helper(a,b,c,i+1,j));
    if(b[j]==c[k]){
        ans=min(ans,helper(a,b,c,i,j+1));
    }else ans=min(ans,1+helper(a,b,c,i,j+1));
    
    return dp[i][j]=ans;
}

int32_t main(){
    int t;
    cin>>t;
    while(t--){
       string a,b,c;
       cin>>a>>b>>c;
        int n=a.length(),m=b.length();
        dp.assign(n+1,vector<int>(m+1,-1));
        cout<<helper(a,b,c,0,0)<<endl;
    }
}