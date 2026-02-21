# XOR Space & XOR Basis --- Complete Guide

Source inspiration: Codeforces blog "A Beautiful Technique for Some XOR
Related Problems".

------------------------------------------------------------------------

## 1. Core Idea

Bitwise XOR behaves exactly like **vector addition modulo 2**.

For each bit independently:

  a  | b  | a XOR b  | (a+b) mod 2
  ---| ---| ---------| -------------
  0  | 1  |   1      | 1
  1  | 1  |   0      | 0

So XOR = addition in **Z₂**.

Thus any integer can be treated as a vector of bits, meaning all XOR
problems can be interpreted as problems in a vector space over **Z₂**.

------------------------------------------------------------------------

## 2. XOR as Vector Space

A number with `d` bits → vector in:

    Z₂^d

Meaning: - Coordinates ∈ {0,1} - Arithmetic is modulo 2 - XOR = vector
addition

This mapping lets us solve bitwise problems using linear algebra tools.

------------------------------------------------------------------------

## 3. Linear Independence (XOR Version)

A set of numbers is **independent** if no number can be made by XORing
others. 

Example:

    [1,2,3] → dependent
    because 1 ⊕ 2 = 3

------------------------------------------------------------------------

## 4. Basis

A **basis** is the smallest set of independent numbers that can generate
all XOR combinations. 

Properties:

-   Basis vectors are independent
-   Any vector can be uniquely expressed using them
-   Size ≤ number of bits
-   If you already have d independent vectors, they form a basis
   

------------------------------------------------------------------------

## 5. Why XOR Basis Is Powerful

If basis size = k

→ Number of distinct XOR values possible =

    2^k

Because each basis vector can be either chosen or not. citeturn1view0

------------------------------------------------------------------------

## 6. Constructing XOR Basis (Algorithm)

Goal: insert vector if it is not representable.

Process:

    for each bit from low → high:
        if bit set:
            if no basis vector uses that bit:
                add to basis
                stop
            else:
                mask ^= basis[bit]

Runs in:

    O(n * d)

Where:

-   n = number of vectors
-   d = number of bits citeturn1view0

This is basically Gaussian elimination over GF(2).

------------------------------------------------------------------------

## 7. Mental Model

Think of basis like:

> "Minimal generators of all XOR results."

Instead of storing all numbers, store only independent ones.

------------------------------------------------------------------------

## 8. Types of Problems XOR Basis Solves

------------------------------------------------------------------------

### A. Count distinct XOR values

Answer:

    2^(basis size)

------------------------------------------------------------------------

### B. Maximum subset XOR

Greedy:

-   start ans = 0
-   iterate basis from highest bit to lowest
-   if improves → apply XOR

------------------------------------------------------------------------

### C. K‑th smallest XOR value

Sort combinations using basis ordering.

------------------------------------------------------------------------

### D. Check representability

Given x:

Try reducing with basis.

If becomes 0 → possible.

Else → impossible.

------------------------------------------------------------------------

### E. Count subsets with XOR = X

If X representable:

    2^(n − basis size)

Otherwise:

    0

------------------------------------------------------------------------

### F. Online insert queries

Maintain dynamic basis as elements added.

------------------------------------------------------------------------

### G. Graph problems

If edges defined by:

    u XOR v = w

Then connectivity can be analyzed via basis.

------------------------------------------------------------------------

### H. Segment / prefix XOR problems

Using prefix XOR:

    pref[i] = a1 ⊕ a2 ⊕ ... ⊕ ai

Then independence of segments ↔ independence of prefix vectors.


------------------------------------------------------------------------

### I. Partitioning problems

Max segments such that no subset XOR = 0

→ Answer = basis size of prefix XORs.

------------------------------------------------------------------------

### J. Square‑product subset problems

Convert prime parity to bitmask → XOR = parity sum.

------------------------------------------------------------------------

## 9. Recognizing When to Use XOR Basis

Look for clues:

-   subset XOR questions
-   maximize/minimize XOR
-   count distinct XORs
-   XOR constraints between nodes
-   representability queries
-   linear equations mod 2
-   parity masks
-   bitmask independence

If numbers behave like vectors → use basis.

------------------------------------------------------------------------

## 10. Template Implementation (C++)

``` cpp
struct XorBasis {
    static const int LOG = 60;
    long long b[LOG] = {};

    void insert(long long x){
        for(int i=LOG-1;i>=0;i--){
            if(!(x>>i&1)) continue;
            if(!b[i]){ b[i]=x; return; }
            x ^= b[i];
        }
    }

    bool can(long long x){
        for(int i=LOG-1;i>=0;i--)
            if(x>>i&1){
                if(!b[i]) return false;
                x ^= b[i];
            }
        return true;
    }

    long long max_xor(){
        long long ans=0;
        for(int i=LOG-1;i>=0;i--)
            ans=max(ans,ans^b[i]);
        return ans;
    }

    int size(){
        int s=0;
        for(int i=0;i<LOG;i++) if(b[i]) s++;
        return s;
    }
};
```

------------------------------------------------------------------------

## 11. Intuition Trick

Instead of:

> subset XOR problem

Translate to:

> linear algebra dimension problem

Then everything becomes easy.

------------------------------------------------------------------------

## 12. Common Mistakes

-   inserting 0 into basis
-   iterating bits wrong direction
-   not normalizing vector before insert
-   forgetting duplicates don't change basis
-   confusing subset count with distinct XOR count

------------------------------------------------------------------------

## 13. Complexity Summary

  Operation             Complexity
  --------------------- ------------
  Insert                O(d)
  Query representable   O(d)
  Max XOR               O(d)
  Build basis           O(n·d)

------------------------------------------------------------------------

## 14. Use case :

it converts exponential subset problems into linear ones.

Typical transformation:

    Brute force: O(2^n)
    XOR basis: O(n log A)

------------------------------------------------------------------------



