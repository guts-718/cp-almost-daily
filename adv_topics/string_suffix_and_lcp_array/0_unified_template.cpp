/*


| Operation         | Time       |
| ----------------- | ---------- |
| Build SA          | O(n log n) |
| Build LCP         | O(n)       |
| RMQ build         | O(n log n) |
| Pattern search    | O(m log n) |
| kth substring     | O(n)       |
| Substring compare | O(1)       |
| Longest repeat    | O(n)       |

*/


#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    string s;
    int n;
    vector<int> sa, lcp, rankv;
    vector<vector<int>> st; // sparse table for RMQ on LCP
    vector<int> lg;

    SuffixArray(const string& str){
        s=str;
        n=s.size();
        buildSA();
        buildLCP();
        buildRMQ();
    }

    /* ---------- BUILD SA ---------- */
    void buildSA(){
        sa.resize(n);
        vector<int> rnk(n), tmp(n);

        for(int i=0;i<n;i++){
            sa[i]=i;
            rnk[i]=s[i];
        }

        for(int k=1;k<n;k<<=1){
            auto cmp=[&](int a,int b){
                if(rnk[a]!=rnk[b]) return rnk[a]<rnk[b];
                int ra = (a+k<n)?rnk[a+k]:-1;
                int rb = (b+k<n)?rnk[b+k]:-1;
                return ra<rb;
            };

            sort(sa.begin(),sa.end(),cmp);

            tmp[sa[0]]=0;
            for(int i=1;i<n;i++)
                tmp[sa[i]] = tmp[sa[i-1]] + cmp(sa[i-1],sa[i]);

            rnk=tmp;
            if(rnk[sa[n-1]]==n-1) break;
        }

        rankv.resize(n);
        for(int i=0;i<n;i++)
            rankv[sa[i]]=i;
    }

    /* ---------- BUILD LCP ---------- */
    void buildLCP(){
        lcp.assign(n,0);
        int h=0;
        for(int i=0;i<n;i++){
            if(rankv[i]==0) continue;
            int j=sa[rankv[i]-1];
            while(i+h<n && j+h<n && s[i+h]==s[j+h]) h++;
            lcp[rankv[i]]=h;
            if(h>0) h--;
        }
    }

    /* ---------- RMQ FOR LCP ---------- */
    void buildRMQ(){
        lg.resize(n+1);
        for(int i=2;i<=n;i++)
            lg[i]=lg[i/2]+1;

        st.assign(lg[n]+1, vector<int>(n));
        st[0]=lcp;

        for(int k=1;k<=lg[n];k++)
            for(int i=0;i+(1<<k)<=n;i++)
                st[k][i]=min(st[k-1][i],st[k-1][i+(1<<(k-1))]);
    }

    int getLCP(int i,int j){
        if(i==j) return n-i;
        int ri=rankv[i], rj=rankv[j];
        if(ri>rj) swap(ri,rj);
        ri++;
        int k=lg[rj-ri+1];
        return min(st[k][ri], st[k][rj-(1<<k)+1]);
    }

    /* ---------- 1. PATTERN SEARCH ---------- */
    vector<int> findOccurrences(const string& p){
        int m=p.size();
        int l=0,r=n-1;

        // lower bound
        while(l<=r){
            int mid=(l+r)/2;
            if(s.compare(sa[mid],m,p)<0) l=mid+1;
            else r=mid-1;
        }
        int start=l;

        // upper bound
        r=n-1;
        while(l<=r){
            int mid=(l+r)/2;
            if(s.compare(sa[mid],m,p)<=0) l=mid+1;
            else r=mid-1;
        }
        int end=r;

        vector<int> res;
        for(int i=start;i<=end;i++)
            if(i>=0 && i<n) res.push_back(sa[i]);
        return res;
    }

    /* ---------- 2. LONGEST REPEATED SUBSTRING ---------- */
    string longestRepeated(){
        int mx=0,pos=0;
        for(int i=1;i<n;i++)
            if(lcp[i]>mx){
                mx=lcp[i];
                pos=sa[i];
            }
        return s.substr(pos,mx);
    }

    /* ---------- 3. KTH SUBSTRING ---------- */
    string kthSubstring(long long k){
        for(int i=0;i<n;i++){
            long long add = (n-sa[i]) - lcp[i];  // if duplicate substrings allowed then we do: add = n - sa[i];
            if(k<=add)
                return s.substr(sa[i], lcp[i]+k);
            k-=add;
        }
        return "";
    }

    /* ---------- 4. SUBSTRING COMPARE ---------- */
    // compare s[l1..r1] vs s[l2..r2]
    int compareSubstr(int l1,int r1,int l2,int r2){
        int len1=r1-l1+1;
        int len2=r2-l2+1;
        int common=getLCP(l1,l2);

        if(common>=min(len1,len2)){
            if(len1==len2) return 0;
            return len1<len2 ? -1 : 1;
        }
        return s[l1+common] < s[l2+common] ? -1 : 1;
    }
};


int main(){
    string s="banana";
    SuffixArray SA(s);

    // Pattern search
    auto occ = SA.findOccurrences("ana");
    for(int x:occ) cout<<x<<" ";
    cout<<"\n";

    // Longest repeated substring
    cout<<SA.longestRepeated()<<"\n";

    // kth substring
    cout<<SA.kthSubstring(3)<<"\n";

    // substring compare
    cout<<SA.compareSubstr(1,3,3,5)<<"\n"; 
}