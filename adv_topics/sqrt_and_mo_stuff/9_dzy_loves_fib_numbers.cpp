#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9+9;

vector<int> fib;
vector<int> prefib;

struct SqrtDecomp {
    int n, block_size, num_blocks;
    vector<int> arr;
    vector<int> block_sum;

    // compressed lazy
    vector<int> lazyA;
    vector<int> lazyB;

    SqrtDecomp(vector<int> &input) {
        arr = input;
        n = arr.size();
        block_size = sqrt(n) + 1;
        num_blocks = (n + block_size - 1) / block_size;

        block_sum.assign(num_blocks, 0);
        lazyA.assign(num_blocks,0);
        lazyB.assign(num_blocks,0);

        for (int i = 0; i < n; i++)
            block_sum[i / block_size] = (block_sum[i / block_size] + arr[i]) % mod;
    }

    void push(int b) {
        if(lazyA[b]==0 && lazyB[b]==0) return;

        int start = b * block_size;
        int end = min(n, start + block_size);

        int a = lazyA[b];
        int bv = lazyB[b];

        if(start<n) arr[start]=(arr[start]+a)%mod;
        if(start+1<n) arr[start+1]=(arr[start+1]+bv)%mod;

        for(int j=start+2;j<end;j++){
            int c = a + bv;
            if(c>=mod) c-=mod;
            arr[j]+=c;
            if(arr[j]>=mod) arr[j]-=mod;
            a=bv;
            bv=c;
        }

        int sum=0;
        for(int j=start;j<end;j++){
            sum+=arr[j];
            if(sum>=mod) sum-=mod;
        }
        block_sum[b]=sum;

        lazyA[b]=lazyB[b]=0;
    }

    void range_add(int l, int r) {
        int start_block = l / block_size;
        int end_block = r / block_size;
        int id=0;

        for (int b = start_block; b <= end_block; b++) {
            int start = b * block_size;
            int end = min(n, start + block_size) - 1;

            if (l <= start && end <= r) {
                // compressed lazy
                lazyA[b]+=fib[id];
                if(lazyA[b]>=mod) lazyA[b]-=mod;

                lazyB[b]+=fib[id+1];
                if(lazyB[b]>=mod) lazyB[b]-=mod;

                int len = end-start+1;
                int val = prefib[id+len-1] - (id?prefib[id-1]:0);
                if(val<0) val+=mod;

                block_sum[b]+=val;
                if(block_sum[b]>=mod) block_sum[b]-=mod;

                id+=block_size;
            }
            else {
                push(b);
                for (int i = max(l, start); i <= min(r, end); i++) {
                    arr[i]+=fib[id];
                    if(arr[i]>=mod) arr[i]-=mod;

                    block_sum[b]+=fib[id++];
                    if(block_sum[b]>=mod) block_sum[b]-=mod;
                }
            }
        }
    }

    int range_sum(int l, int r) {
        int ans = 0;

        int start_block = l / block_size;
        int end_block = r / block_size;

        for (int b = start_block; b <= end_block; b++) {
            int start = b * block_size;
            int end = min(n, start + block_size) - 1;

            if (l <= start && end <= r) {
                ans += block_sum[b];
                if(ans>=mod) ans-=mod;
            }
            else {
                push(b);
                for (int i = max(l, start); i <= min(r, end); i++){
                    ans += arr[i];
                    if(ans>=mod) ans-=mod;
                }
            }
        }
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q;
    cin>>n>>q;

    int LIM = n + sqrt(n) + 5;

    fib.resize(LIM);
    prefib.resize(LIM);

    fib[0]=fib[1]=1;
    for(int i=2;i<LIM;i++)
        fib[i]=(fib[i-1]+fib[i-2])%mod;

    prefib[0]=fib[0];
    for(int i=1;i<LIM;i++){
        prefib[i]=prefib[i-1]+fib[i];
        if(prefib[i]>=mod) prefib[i]-=mod;
    }

    vector<int> a(n);
    for(auto &x:a) cin>>x;

    SqrtDecomp ds(a);

    while(q--){
        int type,l,r;
        cin>>type>>l>>r;
        l--; r--;

        if(type==1)
            ds.range_add(l,r);
        else
            cout<<ds.range_sum(l,r)<<"\n";
    }
}
