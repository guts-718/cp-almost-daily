#include <bits/stdc++.h>
using namespace std;

int helper(int node,int par,vector<pair<int,int>>adj[],vector<int>&ans){
    int cur=1;
    int lst=-1;
    for(auto x:adj[node]){
        int nxt=x.first;
        if(nxt==par){
            lst=x.second;
            continue;
        }
        int tmp=helper(nxt,node,adj,ans);
        if(tmp==-1)return -1;
        cur+=tmp;
    }
    if(cur==3){
        ans.push_back(lst);
        return 0;
    }else if(cur<3){
        return cur;
    }else return -1;
}

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n;
	    cin>>n;
	    vector<pair<int,int>>adj[n];
	    for(int i=0;i<n-1;i++){
	        int u,v;
	        cin>>u>>v;
	        u--;v--;
	        adj[u].push_back({v,i});
	        adj[v].push_back({u,i});
	    }
	    if(n==3){
	        cout<<0<<endl;
	        cout<<endl;
	        continue;
	    }else if(n<3){
	        cout<<-1<<endl;
	        continue;
	    }
	    vector<int>ans;
	    int cop=helper(0,-1,adj,ans);
	    if(cop!=0){
	        cout<<-1<<endl;
	    }else{
	        cout<<ans.size()-1<<endl;
	        if(ans.size()==1){
	            cout<<" "<<endl;
	            continue;
	        }
	        sort(ans.begin(),ans.end());
	        for(auto x:ans){
	            if(x==-1)continue;
	            cout<<x+1<<" ";
	        }
	        cout<<endl;
	    }
	    
	}

}
