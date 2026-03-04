#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        vector<int>adj[n];
        map<pair<int,int>,int>mp;
        for(int i=0;i<m;i++){
            int a,b;
            cin>>a>>b;
            a--;b--;
            mp[{a,b}]=i;
            mp[{b,a}]=i;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        int mini=2e8,op=-1;
        for(int i=0;i<n;i++){
            if(adj[i].size()<mini){
                mini=adj[i].size();
                op=i;
            }
        }
        int f=1;
        if(mini==n-1)f=-1;
        vector<int>ans(m,1);
        for(auto [x,i]:mp){
            if(ans[i]>=2)continue;
            if(op==x.first || op==x.second){
                if(f==-1){
                    f=1;
                    ans[i]=3;
                }
                else ans[i]=2;
            }
        }
        if(mini==n-1)cout<<3<<endl;
        else cout<<2<<endl;
        
        for(auto x:ans)cout<<x<<" ";
        cout<<endl;
        
    }
}
