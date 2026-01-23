// 6 3 4
// 6 0 -5 -1 -2 9

#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    int n,m,d;
	    cin>>n>>m>>d;
	    vector<int>a(n);
	    for(auto &x:a)cin>>x;
	    vector<int>temp(n,-2e18);
	    if(n==1){
	        int o=a[0]-d;
	        o=max(0LL,o);
	        cout<<o<<endl;
	        continue;
	    }
	   
	    int mini=-2e18;
	    for(int i=n-1;i>=0;i--){
	        mini=max(a[i]-d*(i+1),mini);
	        temp[i]=mini;
	    }
	    
	    if(m==1){
	       mini=max(mini,0LL);
	       cout<<mini<<endl;
	       continue;
	    }
	    int ans=max(mini,0LL),cur=0;
	   priority_queue<int, vector<int>, greater<int>> pq;
	    for(int i=0;i<n-1;i++){
	        pq.push(a[i]);
	        cur+=a[i];
	        while(pq.size() && (pq.size()>m-1 || pq.top()<=0)){
	            cur-=pq.top();
	            pq.pop();
	        }
	       
	       ans=max(ans,cur+temp[i+1]);
	       if(i==n-2){
	           while(pq.size()){
	                cur-=pq.top();
	                 pq.pop();
	                 ans=max(ans,cur+temp[i+1]);
	           }
	       }
	        
	    }
	    ans=max(0ll,ans);
	    cout<<ans<<endl;
	}

}

//