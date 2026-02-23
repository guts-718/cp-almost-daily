#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> dp;

int helper(int ind,vector<vector<int>>&help,vector<int>&a,int f){
    if(ind>=a.size())return 0;
    if(dp[ind][f]!=-1) return dp[ind][f];

    int ans=0;

    ans=helper(ind+1,help,a,0);

    int nxt=lower_bound(help[a[ind]].begin(),help[a[ind]].end(),ind+1)
            -help[a[ind]].begin();

    if(nxt < help[a[ind]].size()){
        int pos = help[a[ind]][nxt];
        if(f){
            ans=max(ans,pos-ind+helper(pos,help,a,1));
        }else{
            ans=max(ans,1+pos-ind+helper(pos,help,a,1));
        }
    }
    
    return dp[ind][f]=ans;
}

int main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int>a(n);
        for(auto &x:a){cin>>x;x--;}

        vector<vector<int>>help(n);
        for(int i=0;i<n;i++){
            help[a[i]].push_back(i);
        }

        dp.assign(n,vector<int>(2,-1));
        cout<<helper(0,help,a,0)<<endl;
    }
}