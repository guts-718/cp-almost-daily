#include<bits/stdc++.h>
using namespace std;
//#define int long long
class Trie {
public:
    struct Node {
        Node* ch[2];
        int cnt;
        Node() {
            ch[0] = ch[1] = nullptr;
            cnt = 0;
        }
    };

    
    int B = 31;
    Node* root = new Node();

    void insert(int x) {
        Node* cur = root;
        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (!cur->ch[b]) cur->ch[b] = new Node();
            cur = cur->ch[b];
            cur->cnt++;
        }
    }

    void erase(int x) {
        Node* cur = root;
        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;
            cur = cur->ch[b];
            cur->cnt--;
        }
    }

    int maxxor(int x) {
        Node* cur = root;
        int ans = 0;
        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;
            int want = b ^ 1;
            
            if (cur->ch[want] && cur->ch[want]->cnt > 0) {
                cur = cur->ch[want];
                ans |= (1 << i);
            } else {
                cur = cur->ch[b];
            }
        }
        return ans;
    }
    int minxor(int x){
        Node* cur=root;
        int ans=0;
        for(int i=B;i>=0;i--){
            int b=(x>>i)&1;
            if(cur->ch[b] && cur->ch[b]->cnt){
                cur=cur->ch[b];
            } else {
                ans|=(1<<i);
                cur=cur->ch[b^1];
            }
        }
        return ans;
    }
};


int32_t main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        vector<int>a(n);
        for(int i=0;i<n;i++)cin>>a[i];
        Trie trie;
        int ans=2e9;
        for(auto x:a)trie.insert(x);
        int d=-1;
        for(int i=0;i<n;i++){
            trie.erase(a[i]);
            int cur=trie.minxor(a[i]);
            if(cur<ans){
                ans=cur;
                d=i;
            }
            trie.insert(a[i]);
        }
        int sol=(ans^a[d]);
        int e=-1;
        for(int i=0;i<n;i++){
            if(a[i]==sol && d!=i){
                e=i;break;
            }
        }
        if(d>e)swap(d,e);
        int n1=a[d],n2=a[e];
        //cout<<n1<<" "<<n2<<endl;
        long long temp=0ll;
        for(int i=k-1;i>=0;i--){
            if(((n1>>i)&1)==((n2>>i)&1)){
                if(!((n1>>i)&1)){
                    temp+=(1<<i);
                }
            }
        }
        cout<<d+1<<" "<<e+1<<" "<<temp<<endl;
    }
}