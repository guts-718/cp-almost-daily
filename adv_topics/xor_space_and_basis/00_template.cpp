
#include <bits/stdc++.h>
using namespace std;

struct XorBasis {
    static const int LOG = 60;
    long long b[LOG];
    long long inserted = 0; // total inserted elements
    long long mod = 1e9+7;

    XorBasis() {
        memset(b, 0, sizeof(b));
    }

    // fast power
    long long modpow(long long a,long long e){
        long long r=1;
        while(e){
            if(e&1) r=r*a%mod;
            a=a*a%mod;
            e>>=1;
        }
        return r;
    }

    // insert vector
    // When a vector is dependent, it doesn't add new information.
    // Each dependent vector doubles the number of solutions.
    bool insert(long long x){
        inserted++;

        long long v=x;
        for(int i=LOG-1;i>=0;i--){
            if(!(v>>i&1)) continue;

            if(!b[i]){
                b[i]=v;
                return true; // independent
            }
            v^=b[i];
        }
        return false; // dependent
    }

    // check representable
    bool can(long long x) const{
        long long v=x;
        for(int i=LOG-1;i>=0;i--){
            if(!(v>>i&1)) continue;
            if(!b[i]) return false;
            v^=b[i];
        }
        return true;
    }

    // size = rank
    int size() const{
        int s=0;
        for(int i=0;i<LOG;i++)
            if(b[i]) s++;
        return s;
    }

    // maximum subset xor
    long long max_xor(long long x=0) const{
        long long ans=x;
        for(int i=LOG-1;i>=0;i--)
            ans=max(ans, ans^b[i]);
        return ans;
    }

    // minimum xor achievable
    long long min_xor(long long x=0) const{
        long long ans=x;
        for(int i=LOG-1;i>=0;i--)
            if(b[i])
                ans=min(ans, ans^b[i]);
        return ans;
    }

    // merge another basis
    void merge(const XorBasis &other){
        for(int i=0;i<LOG;i++)
            if(other.b[i])
                insert(other.b[i]);
    }

    // reduced basis (sorted, independent minimal form)
    vector<long long> getReducedBasis() const{
        vector<long long> v;
        for(int i=0;i<LOG;i++)
            if(b[i])
                v.push_back(b[i]);

        int n=v.size();

        // eliminate lower bits
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i!=j && ((v[i]^v[j]) < v[i]))
                    v[i]^=v[j];

        sort(v.begin(),v.end());
        return v;
    }

    // kth smallest xor (0-indexed)
    long long kth(long long k) const{
        vector<long long> v=getReducedBasis();
        int n=v.size();

        if(k >= (1LL<<n)) return -1;

        long long ans=0;
        for(int i=0;i<n;i++)
            if(k>>i&1)
                ans^=v[i];
        return ans;
    }

    // count subsets whose xor == x
    long long count(long long x){
        if(!can(x)) return 0;

        long long free_vars = inserted - size();
        return modpow(2, free_vars);
    }
};

int main() {
    XorBasis xb;
    int n,q;
    cin>>n>>q;
    vector<vector<int>>query(q,vector<int>(3));
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<q;i++){
        int l,x;
        cin>>l>>x;
        l--;
        query[i]={l,x,i};
    }
    int j=0;
    vector<int>sol(q,0);
    sort(query.begin(),query.end());
    for(int i=0;i<n;i++){
        xb.insert(a[i]);
        cout<<i<<" ";
        while(j<query.size() && query[j][0]<=i){
            long long ans=xb.count(query[j][1]);
            cout<<query[j][0]<<" ";
            sol[query[j][2]]=ans;
            j++;
        }
        cout<<endl;
        
    }
    for(auto x:sol)cout<<x<<endl;
    cout<<endl;
}