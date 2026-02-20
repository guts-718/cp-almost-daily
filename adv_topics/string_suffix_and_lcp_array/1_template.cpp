#include <bits/stdc++.h>
using namespace std;

/*
    SUFFIX ARRAY + LCP TEMPLATE
    ----------------------------
    Build time: O(n log n)
    LCP build:  O(n)

    sa[i]  = starting index of i-th smallest suffix
    lcp[i] = LCP(sa[i], sa[i-1])   (lcp[0] = 0)
*/

struct SuffixArray {
    string s;
    vector<int> sa, lcp;

    SuffixArray(const string& str) {
        s = str;
        buildSA();
        buildLCP();
    }

    void buildSA() {
        int n = s.size();
        sa.resize(n);
        vector<int> rnk(n), tmp(n);

        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rnk[i] = s[i];
        }

        for (int k = 1; k < n; k <<= 1) {
            auto cmp = [&](int a, int b) {
                if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
                int ra = (a + k < n) ? rnk[a + k] : -1;
                int rb = (b + k < n) ? rnk[b + k] : -1;
                return ra < rb;
            };

            sort(sa.begin(), sa.end(), cmp);

            tmp[sa[0]] = 0;
            for (int i = 1; i < n; i++)
                tmp[sa[i]] = tmp[sa[i-1]] + cmp(sa[i-1], sa[i]);

            rnk = tmp;
            if (rnk[sa[n-1]] == n-1) break;
        }
    }

    void buildLCP() {
        int n = s.size();
        lcp.assign(n, 0);
        vector<int> rank(n);

        for (int i = 0; i < n; i++)
            rank[sa[i]] = i;

        int h = 0;
        for (int i = 0; i < n; i++) {
            if (rank[i] == 0) continue;
            int j = sa[rank[i] - 1];
            while (i + h < n && j + h < n && s[i+h] == s[j+h])
                h++;
            lcp[rank[i]] = h;
            if (h > 0) h--;
        }
    }
};


/* 
SuffixArray SA(str);
auto &sa = SA.sa;
auto &lcp = SA.lcp;
*/
int main() {
    string s = "banana";  
    SuffixArray SA(s);

    cout << "Suffix Array:\n";
    for (int i : SA.sa)
        cout << i << " ";
    cout << "\n\n";

    cout << "Suffixes in sorted order:\n";
    for (int i : SA.sa)
        cout << s.substr(i) << "\n";

    cout << "\nLCP Array:\n";
    for (int x : SA.lcp)
        cout << x << " ";
    cout << "\n";

    return 0;
}