#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--){
	int n;
	cin>>n;
	vector<vector<int>>v(n,vector<int>(n,0));
	if(n%2==0){
	    int p=(n-1)/2;
	    for(int i=0;i<n;i++){
	        int j=(i+1)%n;
	        int cnt=p;
	        while(cnt--){
	            v[i][j]=1;
	            v[j][i]=-1;
	            j=(j+1)%n;
	        }
	    }
	    
	}else{
	    int p=(n-1)/2;
	    for(int i=0;i<n;i++){
	        int j=(i+1)%n;
	        int cnt=p;
	        while(cnt--){
	            v[i][j]=1;
	            v[j][i]=-1;
	            j=(j+1)%n;
	        }
	    }
	    
	}
	for(int i=0;i<n;i++){
	    for(int j=i+1;j<n;j++)cout<<v[i][j]<<" ";
	}
	cout<<endl;
	}

}
