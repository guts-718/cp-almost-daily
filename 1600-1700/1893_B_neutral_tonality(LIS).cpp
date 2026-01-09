#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin>>n>>m;

    vector<int> a(n);
    vector<int> b(m);

    for(auto &x:a)cin>>x;
    for(auto &x:b)cin>>x;

    sort(b.rbegin(), b.rend());

    vector<int> combined;
    int i = 0,j = 0; 

    
    while (i < n && j < m) {
        if (a[i] >= b[j]) {
            combined.push_back(a[i]);
            i++;
        } else {
            combined.push_back(b[j]);
            j++;
        }
    }

   
    while (i < n) {
        combined.push_back(a[i]);
        i++;
    }

    while (j < m) {
        combined.push_back(b[j]);
        j++;
    }

   
    for (int k = 0; k < combined.size(); k++) {
        cout << combined[k] << (k == combined.size() - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}



/*

- the below logic also works . just need to handle the case when lis(A)=1 [1. when len(A)=1 AND when a is decreasing type array]
#include<bits/stdc++.h>
using namespace std;

int cnt_lis(vector<int>&a){
    vector<int>temp;

        for(auto x:a){
            if(temp.size()==0 || temp.back()<x){
                temp.push_back(x);
            }else *lower_bound(temp.begin(),temp.end(),x)=x;
        }
        return temp.size();
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        vector<int>a(n),b(m);
        for(auto &x:a)cin>>x;
        for(auto &x:b)cin>>x;
        vector<int>temp;
        vector<int>aa=a;
        for(auto &x:aa)x*=-1;
        int A=cnt_lis(a);
        sort(b.rbegin(),b.rend());
        deque<int>dq;
        
        
        if(A==1){
            int sm=a[0];
            for(auto x:b){
                if(x>=sm){
                    dq.push_back(x);
                }else break;
            }
            for(auto x:a){
                dq.push_back(x);
            }
            for(auto x:b){
                if(x<=dq.back()){
                    dq.push_back(x);
                }
            }
            for(auto x:dq){
                cout<<x<<" ";
                
            }
            cout<<endl;
            vector<int>o;
            for(auto x:dq){
                o.push_back(x);
            }
            int B=cnt_lis(o);
            cout<<"lis a: "<<A<<"  LIS b "<<B<<endl;
            continue;
        }
        for(auto x:a){
            if(temp.size()==0 || temp.back()<x){
                temp.push_back(x);
            }else *lower_bound(temp.begin(),temp.end(),x)=x;
        }
        int bac=temp.back();
        temp.clear();
        for(int i=n-1;i>=0;i--){
            int x=aa[i];
            if(temp.size()==0 || temp.back()<x){
                temp.push_back(x);
            }else *lower_bound(temp.begin(),temp.end(),x)=x;
        }
        int fron=-temp.back();
        for(auto x:a){
            dq.push_back(x);
        }
      
        for(auto x:b){
            if(x<=fron){
                dq.push_back(x);
            }else dq.push_front(x);
        }
        vector<int>o;
        for(auto x:dq){
            cout<<x<<" ";
            o.push_back(x);
        }
        
        int B=cnt_lis(o);
        
        cout<<endl;
        cout<<"lis a "<<A<<" lis c "<<B<<endl;
    }
}
    
*/