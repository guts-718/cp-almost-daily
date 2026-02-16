# Sqrt Decomposition & Mo's Algorithm 

------------------------------------------------------------------------

## 1. Core Idea of √N Techniques

Whenever you see:

-   static queries
-   offline queries
-   range queries
-   constraints \~ 1e5 to 2e5
-   updates rare or absent

**Think:** can I split work into blocks of size √N?

Why √N?

Because:

    N elements
    block size = B
    blocks = N/B
    total work ≈ N/B + B
    minimum when B = √N

------------------------------------------------------------------------

## 2. When √ Tricks Are Useful

### Pattern Recognition Table

  Problem Trait       |  Likely Technique
  --------------------| --------------------
  Range queries       |  Mo's algorithm
  Static array        |  Sqrt decomposition
  Tree path queries   |  Mo on tree
  Heavy updates       |  Sqrt buckets
  Jump queries        |  Sqrt jumping
  Frequency queries   |  Mo
  Offline queries     |  Mo
  Reordering allowed  |  Mo
  Online strict       |  Segment tree

------------------------------------------------------------------------

## 3. Classic Sqrt Decomposition

Split array into blocks.

Precompute block answers.

Example: Range Sum

Precompute:

    block[i] = sum of block i

Query:

    left partial + full blocks + right partial

Complexity:

    Build = O(N)
    Query = O(√N)

------------------------------------------------------------------------

## 4. Sqrt Decomposition with Updates

Used when:

-   many queries
-   few updates

Technique: Rebuild block when updated.

Variants: - Lazy blocks - Rebuild blocks periodically

------------------------------------------------------------------------

## 5. Mo's Algorithm (Offline Query Reordering)

Used when:

-   queries known beforehand
-   array does not change
-   add/remove operations are easy

Complexity:

    O((N + Q) √N)

Core principle: Move two pointers slowly instead of recomputing each
query.

------------------------------------------------------------------------

## 6. How Mo Works Internally

Sort queries by:

    block(l), then r

Maintain window:

    [L, R]

Move window:

    while L > ql → add(--L)
    while R < qr → add(++R)
    while L < ql → remove(L++)
    while R > qr → remove(R--)

Answer always stored in `cur`.

------------------------------------------------------------------------

## 7. Choosing Block Size

Standard:

    √N

Optimized:

    N / √Q

Empirical best:

    max(1, N / sqrt(Q))

------------------------------------------------------------------------

## 8. Common Mo Variants

------------------------------------------------------------------------

### 8.1 Mo with Updates (Time Dimension)

State:

    L, R, T

Need functions:

    add()
    remove()
    apply_update()
    rollback_update()

Used when queries mixed with updates.

------------------------------------------------------------------------

### 8.2 Mo on Trees

Technique:

    Tree → Euler Tour → Array
    Path → Range

Extra trick: Toggle nodes because each appears twice.

Use LCA handling.

------------------------------------------------------------------------

### 8.3 Hilbert Order Mo

Alternative sorting.

Benefits: - better locality - faster in practice

Use when Q large (≥100k).

------------------------------------------------------------------------

## 9. Problems Where √ Tricks Shine

### Arrays

-   distinct in range
-   frequency
-   xor queries
-   pairs count
-   k‑th occurrence

------------------------------------------------------------------------

### Trees

-   distinct on path
-   sum on path
-   color queries
-   subtree queries

------------------------------------------------------------------------

### Strings

Treat string as array.

Works for: - palindrome queries - frequency queries - substring
statistics

------------------------------------------------------------------------

### Graphs

Rare but useful:

-   offline connectivity
-   edge add/remove batches

------------------------------------------------------------------------

## 10. Recognizing Mo‑Friendly Problems

Ask:

1.  Queries offline?
2.  Array static?
3.  Can I update answer when one element added?
4.  Can I undo update?

If all yes → use Mo.

------------------------------------------------------------------------

## 11. Designing add() and remove()

Golden rule:

    add/remove must be O(1)

Typical structures:

  Query      Structure
  ---------- -------------------
  Distinct   freq\[\]
  Mode       freq + freqCount
  Pairs      combinatorics
  Sum        variable
  Majority   bitset / counters

------------------------------------------------------------------------

## 12. Trick Library

### Trick 1 --- Toggle Technique (Trees)

Used when elements appear twice.

    if(vis[x]) remove
    else add

------------------------------------------------------------------------

### Trick 2 --- Contribution Method

Instead of recomputing answer:

Maintain contribution of each element.

Example:

    pairs += freq[x]
    freq[x]++

------------------------------------------------------------------------

### Trick 3 --- Small vs Large Strategy

Split values:

    freq ≤ √N → brute
    freq > √N → precomputed

Used in hybrid problems.

------------------------------------------------------------------------

### Trick 4 --- Offline Reordering

Many problems solvable offline with sorting.

Mo is just one type of offline ordering.

------------------------------------------------------------------------

## 13. Common Pitfalls

❌ Using Mo when updates frequent\
❌ add/remove not O(1)\
❌ forgetting to reset global state\
❌ unordered_map TLE → use vector if values small

------------------------------------------------------------------------

## 14. Complexity Intuition

Why Mo works:

Moving window cost amortized.

Total moves:

    L moves ≈ Q√N
    R moves ≈ Q√N

So total operations:

    ≈ 2Q√N

------------------------------------------------------------------------

## 15. When NOT to Use √ Techniques

Avoid if:

-   online queries required
-   constraints small (\<5000)
-   updates heavy
-   segment tree simpler

------------------------------------------------------------------------

## 16. Mental Checklist During Contest

When seeing query problem:

    Is it offline?
    Is array static?
    Is add/remove easy?
    Is N large?

If YES → try Mo.

If NO → try segment tree.

------------------------------------------------------------------------

## 17. Practice Problem Ladder

Recommended progression:

1.  Distinct in range
2.  Frequency queries
3.  Mode queries
4.  Mo with updates
5.  Mo on trees
6.  Hilbert Mo

------------------------------------------------------------------------

## 18. Cheat Sheet Summary

  Technique      Use When
  -------------- ------------------
  Sqrt Decomp    online queries
  Mo             offline queries
  Mo + Updates   mixed operations
  Mo on Tree     path queries
  Hilbert        Q huge

------------------------------------------------------------------------

## Final Advice

Most strong contestants don't memorize solutions.

They memorize **patterns**.

Sqrt tricks are not one algorithm.

They are a **family of strategies**:

> divide work into √ sized chunks to balance time.

Mastering this mindset unlocks many hard problems.

------------------------------------------------------------------------

# STANDARD 

| Problem Type    | What to Maintain         |
| --------------- | ------------------------ |
| Distinct values | freq + count             |
| Sum             | running sum              |
| Mode            | freq + freqCount         |
| Pairs           | combinatorics using freq |
| XOR queries     | freq xor trick           |



# TREE


| Query Type      | What to Track     |
| --------------- | ----------------- |
| distinct values | freq              |
| sum             | running sum       |
| xor             | xor ^= val[node]  |
| pairs           | freq combinations |
| max freq        | freq + bucket     |

