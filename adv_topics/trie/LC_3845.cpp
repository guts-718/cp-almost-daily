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