# Suffix Array + LCP Array --- Complete Deep Dive Guide

## important points:
 - SA  → sorted list of suffixes
 - rank → tells where each suffix sits in that list
 - LCP → tells similarity between neighbors in that list
 - Rank tells you where a suffix lives in sorted order

 - sorting suffixes = sorting all substrings implicitly
 - LCP\[i\] = longest common prefix of suffix SA\[i\] and SA\[i-1\] (LCP[0]=0)
 - Can solve a large variety of substring related problems...
 - rank maps original index → position in suffix array
 - SA array - [5, 3, 1, 0, 4, 2]
 - rank array - index → rank
                    0 → 3
                    1 → 2
                    2 → 5
                    3 → 1
                    4 → 4
                    5 → 0
  - Longest Common Prefix of two suffixes (getLCP(i, j)) - the minimal value in the lcp for strings corresponding to i and j
  - LCP(A,C) = min(LCP(A,B), LCP(B,C))
------------------------------------------------------------------------

# 1. Intuition

A **suffix** of a string is a substring starting at position `i` and
going to the end.

Example for `"banana"`:

    banana
    anana
    nana
    ana
    na
    a

A **Suffix Array (SA)** is simply the list of starting indices of these
suffixes sorted lexicographically.

Why is this powerful?

Because **sorting suffixes = sorting all substrings implicitly**.

This means once SA is built, you can answer complex string queries
extremely fast.

------------------------------------------------------------------------

# 2. Why Not Just Sort Substrings?

Naively: - There are O(n²) substrings - Comparing them costs O(n)

Total worst case = **O(n³)**

Suffix arrays reduce this to:

-   Build: O(n log n)
-   Queries: O(log n) or O(1)

------------------------------------------------------------------------

# 3. Example Construction

String = `"banana"`

Sorted suffixes:

  index   suffix
  ------- --------
  5       a
  3       ana
  1       anana
  0       banana
  4       na
  2       nana

Suffix Array:

    SA = [5,3,1,0,4,2]

------------------------------------------------------------------------

# 4. Rank Array Concept

Instead of comparing strings, we compare **rank pairs**:

    (rank[i], rank[i + k])

We double `k` each iteration.

Iteration progression:

    k = 1 → compare 1 char
    k = 2 → compare 2 chars
    k = 4 → compare 4 chars
    k = 8 → compare 8 chars

After log(n) rounds → sorted.

------------------------------------------------------------------------

# 5. LCP Array

**LCP\[i\] = longest common prefix of suffix SA\[i\] and SA\[i-1\]**

Example:

Suffixes sorted:

    a
    ana
    anana
    banana
    na
    nana

LCP:

    0 1 3 0 0 2

------------------------------------------------------------------------

# 6. Why LCP Matters

Without LCP:

Comparing suffixes → O(n)

With LCP:

Common prefix info already stored → O(1)

This enables:

-   substring comparison
-   repeated substring detection
-   pattern statistics

------------------------------------------------------------------------

# 7. Kasai Algorithm Idea

Naively computing LCP takes O(n²)

Kasai optimization:

Key trick: \> If LCP of suffix i and j is k,\
\> then LCP of next suffix ≥ k−1

So we reuse previous work.

Total time → **O(n)**

------------------------------------------------------------------------

# 8. Complexity Summary

  Structure      Time         Space
  -------------- ------------ -------
  Suffix Array   O(n log n)   O(n)
  LCP            O(n)         O(n)

------------------------------------------------------------------------

# 9. When Should You Use Suffix Array?

Use it when problem has:

✔ substring queries\
✔ lexicographic ordering\
✔ repeated patterns\
✔ comparison between substrings\
✔ large input strings\
✔ multiple queries

Avoid if:

✘ string length \< 2000\
✘ only single pattern search (use KMP/Z instead)

------------------------------------------------------------------------

# 10. Core Template (Contest Ready)

``` cpp
struct SuffixArray {
    string s;
    vector<int> sa,lcp;

    SuffixArray(string str){
        s=str;
        buildSA();
        buildLCP();
    }

    void buildSA(){
        int n=s.size();
        sa.resize(n);
        vector<int> rnk(n),tmp(n);

        for(int i=0;i<n;i++){
            sa[i]=i;
            rnk[i]=s[i];
        }

        for(int k=1;k<n;k<<=1){
            auto cmp=[&](int a,int b){
                if(rnk[a]!=rnk[b]) return rnk[a]<rnk[b];
                int ra=(a+k<n)?rnk[a+k]:-1;
                int rb=(b+k<n)?rnk[b+k]:-1;
                return ra<rb;
            };

            sort(sa.begin(),sa.end(),cmp);

            tmp[sa[0]]=0;
            for(int i=1;i<n;i++)
                tmp[sa[i]]=tmp[sa[i-1]]+cmp(sa[i-1],sa[i]);

            rnk=tmp;
            if(rnk[sa[n-1]]==n-1) break;
        }
    }

    void buildLCP(){
        int n=s.size();
        lcp.assign(n,0);
        vector<int> rank(n);

        for(int i=0;i<n;i++)
            rank[sa[i]]=i;

        int h=0;
        for(int i=0;i<n;i++){
            if(rank[i]==0) continue;
            int j=sa[rank[i]-1];
            while(i+h<n && j+h<n && s[i+h]==s[j+h]) h++;
            lcp[rank[i]]=h;
            if(h>0) h--;
        }
    }
};
```

------------------------------------------------------------------------

# 11. 15 Problems + Detailed Logic

------------------------------------------------------------------------

## 1. Pattern Search

Binary search suffix array.

Compare pattern with suffix at SA\[mid\].

Time:

    O(m log n)

------------------------------------------------------------------------

## 2. Count Pattern Occurrences

Find lower bound and upper bound of pattern range.

Answer:

    upper − lower

------------------------------------------------------------------------

## 3. Longest Repeated Substring

Largest value in LCP array.

Why?

Because LCP measures prefix match between adjacent suffixes → repeated
substring length.

------------------------------------------------------------------------

## 4. Longest Common Substring of Two Strings

Combine:

    s1 + # + s2

Build SA.

Check adjacent suffixes from different strings.
Take max LCP.
```cpp
for i = 1 … n-1
    if sa[i] and sa[i-1] belong to different strings
        ans = max(ans, lcp[i])
```
------------------------------------------------------------------------

## 5. Number of Distinct Substrings

Total substrings:

    n(n+1)/2

Subtract duplicates:

    answer = n(n+1)/2 − sum(LCP)

Reason: LCP counts shared prefixes → duplicates.

------------------------------------------------------------------------

## 6. Lexicographically Smallest Rotation

Double string:

    s + s

Smallest suffix starting \< n is answer.

------------------------------------------------------------------------

## 7. Fast Substring Comparison

Precompute RMQ on LCP.

Then compare any substrings in O(1).

------------------------------------------------------------------------

## 8. K‑th Lexicographic Substring

Each suffix contributes:

    len − LCP

Traverse suffixes subtracting until k fits.

------------------------------------------------------------------------

## 9. Longest Palindromic Substring

Build SA on:

    s + # + reverse(s)

Palindrome = common substring between original and reversed.

------------------------------------------------------------------------

## 10. Substring Appearing ≥ K Times

Sliding window of size K over suffix array.

Minimum LCP in window = answer candidate.

------------------------------------------------------------------------

## 11. Total Common Prefix Sum

Sum of all LCP values.

Represents how much overlap exists globally.

------------------------------------------------------------------------

## 12. Substrings Appearing at Least K Times

Same as #10 but accumulate all valid ranges using segment tree or stack.

------------------------------------------------------------------------

## 13. Minimal Cyclic Shift

Same logic as rotation problem.

Important trick: don't forget modulo.

------------------------------------------------------------------------

## 14. Plagiarism Detection

Given two texts:

Find longest common substrings.

Long match → copied segment.

Used in real plagiarism checkers.

------------------------------------------------------------------------

## 15. Longest Substring Common to ALL Strings

Generalized suffix array:

Join strings with separators:

    A#B$C%

Maintain which string each suffix belongs to.

Sliding window until all strings represented.

Take minimum LCP.

------------------------------------------------------------------------

# 12. Common Tricks

Sentinel char:

    append '$'

Ensures no suffix is prefix of another.

------------------------------------------------------------------------

Rank compression: use int not char

------------------------------------------------------------------------

Avoid mistakes: 
- forgetting separator when joining strings\
- not handling edge suffixes\
- not resetting arrays between testcases

------------------------------------------------------------------------

# 13. SA vs Other String Algorithms

  Tool           Strength         Weakness
  -------------- ---------------- ------------------
  Z algo         single pattern   limited use
  KMP            exact match      no ordering
  Hashing        easy             collisions
  Suffix Tree    fastest          huge memory
  Suffix Array   balanced         needs build time

------------------------------------------------------------------------

