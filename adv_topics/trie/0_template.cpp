struct Trie {
    struct Node {
        Node* ch[2];
        int cnt;
        Node() { ch[0]=ch[1]=nullptr; cnt=0; }
    };

    int B;
    Node* root;
    int SZ = 0;

    Trie(int BITS = 31){
        B = BITS;
        root = new Node();
    }

    // ---------- BASIC ----------
    int size() { return SZ; }

    bool exists(int x){
        Node* cur=root;
        for(int i=B;i>=0;i--){
            int b=(x>>i)&1;
            if(!cur->ch[b] || cur->ch[b]->cnt==0)
                return false;
            cur=cur->ch[b];
        }
        return true;
    }

    void insert(int x){
        Node* cur=root;
        for(int i=B;i>=0;i--){
            int b=(x>>i)&1;
            if(!cur->ch[b]) cur->ch[b]=new Node();
            cur=cur->ch[b];
            cur->cnt++;
        }
        SZ++;
    }

    void erase(int x){
        if(!exists(x)) return;
        Node* cur=root;
        for(int i=B;i>=0;i--){
            int b=(x>>i)&1;
            cur=cur->ch[b];
            cur->cnt--;
        }
        SZ--;
    }

    void clear(){
        root=new Node();
        SZ=0;
    }

    // ---------- MAX XOR ----------
    int maxxor(int x){
        Node* cur=root;
        int ans=0;
        for(int i=B;i>=0;i--){
            int b=(x>>i)&1;
            int want=b^1;
            if(cur->ch[want] && cur->ch[want]->cnt){
                ans|=(1<<i);
                cur=cur->ch[want];
            } else cur=cur->ch[b];
        }
        return ans;
    }

    // ---------- MIN XOR ----------
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

    // ---------- COUNT nums with (num XOR x) <= k ----------
    int count_le(int x,int k){
        Node* cur=root;
        int ans=0;
        for(int i=B;i>=0;i--){
            if(!cur) break;

            int xb=(x>>i)&1;
            int kb=(k>>i)&1;

            if(kb){
                if(cur->ch[xb])
                    ans+=cur->ch[xb]->cnt;
                cur=cur->ch[xb^1];
            }
            else{
                cur=cur->ch[xb];
            }
        }
        return ans;
    }

    // ---------- KTH SMALLEST ----------
    int kth(int k){
        Node* cur=root;
        int ans=0;
        for(int i=B;i>=0;i--){
            int left = cur->ch[0] ? cur->ch[0]->cnt : 0;

            if(k<=left){
                cur=cur->ch[0];
            } else{
                k-=left;
                ans|=(1<<i);
                cur=cur->ch[1];
            }
        }
        return ans;
    }

    // ---------- COUNT < x ----------
    int count_less(int x){
        Node* cur=root;
        int ans=0;
        for(int i=B;i>=0;i--){
            if(!cur) break;
            int b=(x>>i)&1;

            if(b){
                if(cur->ch[0])
                    ans+=cur->ch[0]->cnt;
                cur=cur->ch[1];
            }
            else{
                cur=cur->ch[0];
            }
        }
        return ans;
    }

    // ---------- MEX ----------
    int mex(){
        Node* cur=root;
        int ans=0;
        for(int i=B;i>=0;i--){
            int left = cur->ch[0]?cur->ch[0]->cnt:0;
            int limit = 1<<i;

            if(left < limit){
                cur=cur->ch[0];
            } else{
                ans|=(1<<i);
                cur=cur->ch[1];
            }
            if(!cur) break;
        }
        return ans;
    }

    // ---------- MERGE TWO TRIES ----------
    static Node* merge(Node* a, Node* b){
        if(!a) return b;
        if(!b) return a;
        Node* r=new Node();
        r->cnt = a->cnt + b->cnt;
        r->ch[0]=merge(a->ch[0],b->ch[0]);
        r->ch[1]=merge(a->ch[1],b->ch[1]);
        return r;
    }

    // ---------- MAX XOR PAIR ----------
    int max_pair_xor(){
        return dfs_pair(root, root, B);
    }

    int dfs_pair(Node* a, Node* b, int bit){
        if(!a || !b || bit<0) return 0;
        int best=0;

        if(a->ch[0] && b->ch[1])
            best=max(best,(1<<bit)+dfs_pair(a->ch[0],b->ch[1],bit-1));

        if(a->ch[1] && b->ch[0])
            best=max(best,(1<<bit)+dfs_pair(a->ch[1],b->ch[0],bit-1));

        if(best) return best;

        return max(
            dfs_pair(a->ch[0],b->ch[0],bit-1),
            dfs_pair(a->ch[1],b->ch[1],bit-1)
        );
    }
};

class Solution {
public:
 int maxXor(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pref(n + 1);
        for (int i = 0; i < n; i++){
            pref[i + 1] = pref[i] ^ nums[i];
        }
        
        Trie trie;
        int l = 0, ans = 0;
        multiset<int> ms;
        

       
        ms.insert(nums[0]);
        trie.insert(pref[0]);
       

        for (int r = 0; r < n; r++) {
            if (r > 0) ms.insert(nums[r]);

            while (*ms.rbegin() - *ms.begin() > k) {
                ms.erase(ms.find(nums[l]));
                trie.erase(pref[l]);
                l++;
            }

            ans = max(ans, trie.maxxor(pref[r + 1]));
            trie.insert(pref[r + 1]);
        }
        return ans;
    }
};