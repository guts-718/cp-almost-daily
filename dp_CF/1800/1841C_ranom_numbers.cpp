#include <bits/stdc++.h>
using namespace std;

long long p10[5]={1,10,100,1000,10000};

string s;
vector<vector<int>> v;
vector<vector<vector<long long>>> dp;

long long helper(int ind,int f,int g){
    if(ind<0) return 0;

    long long &res = dp[ind][f+1][g+1];
    if(res!=LLONG_MIN) return res;

    long long cur = LLONG_MIN;

    if(f==-1){
        int cnt=0;
        int i=(s[ind]-'A')+1;

        for(int k=i;k<5;k++)
            cnt+=v[ind+1][k];

        if(cnt)
            cur=max(cur,-p10[i-1]+helper(ind-1,f,g));
        else
            cur=max(cur, p10[i-1]+helper(ind-1,f,g));

        for(int x=0;x<5;x++){
            if((s[ind]-'A')==x) continue;

            cnt=0;
            for(int j=x+1;j<5;j++)
                cnt+=v[ind+1][j];

            if(cnt==0)
                cur=max(cur, p10[x]+helper(ind-1,x,s[ind]-'A'));
            else
                cur=max(cur,-p10[x]+helper(ind-1,x,s[ind]-'A'));
        }
    }
    else{
        int cnt=0;
        int i=(s[ind]-'A')+1;

        for(int k=i;k<5;k++){
            cnt+=v[ind+1][k];
            if(f==k) cnt++;
            if(g==k) cnt--;
        }

        if(cnt==0)
            cur=max(cur, p10[i-1]+helper(ind-1,f,g));
        else
            cur=max(cur,-p10[i-1]+helper(ind-1,f,g));
    }

    return res=cur;
}

int main(){
    int t; cin>>t;
    while(t--){
        cin>>s;
        int n=s.size();

        v.assign(n+1,vector<int>(5,0));
        for(int i=n-1;i>=0;i--){
            v[i][s[i]-'A']++;
            for(int j=0;j<5;j++)
                v[i][j]+=v[i+1][j];
        }

        dp.assign(n,vector<vector<long long>>(6,vector<long long>(6,LLONG_MIN)));

        cout<<helper(n-1,-1,-1)<<endl;
    }
}