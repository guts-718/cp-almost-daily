#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Apply floor(x / 2) operation `times` times
ll apply_floor(ll x, ll times) {
    while (times--) {
        if (x == 0) return 0;
        x /= 2;
    }
    return x;
}

// Apply ceil(x / 2) operation `times` times
ll apply_ceil(ll x, ll times) {
    while (times--) {
        if (x <= 1) return x;
        x = (x + 1) / 2;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        ll x, n, m;
        cin >> x >> n >> m;

        ll min_value = apply_floor(apply_ceil(x, m), n);
        ll max_value = apply_ceil(apply_floor(x, n), m);

        cout << min_value << " " << max_value << '\n';
    }

    return 0;
}

// below is wrong

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
       int x,n,m;
       cin>>x>>m>>n;
       int X=x,M=m,N=n;
       int ans2=-1;
       while(x!=0 && (m || n)){
           if(x==1){
               if(m){
                   ans2=0;
               }else ans2=1;
               break;
           }
           if(x%2==1){
               if(n){
               x/=2;
               x++;
               n--;
               }else{
                   x/=2;
                   m--;
               }
           }
           else if(x%2==0){
               x/=2;
               if(m){
                   m--;
               }else n--;
              
            }
       }
       
       
       
       if(ans2==-1)ans2=x;
       x=X,m=M,n=N;
       int ans1=-1;
       while(x!=0 && (m || n)){
           if(x==1){
               if(m){
                   ans1=0;
                   
               }else ans1=1;
               break;
               
           }
           if(x%2==0){
              if(n){
               x/=2;
               n--;
               }else if(m){
                  x/=2;
                  m--;
               }
           }
           else if(x%2==1){
               x/=2;
               if(m){
                   m--;
               }else if(n){
                   n--;
                   x++;
               } 
              
            }
       }
       if(ans1==-1)ans1=x;
       cout<<ans1<<" "<<ans2<<endl;
    }
}
