# Advanced DP Optimizations --- Master Notes

Author: ChatGPT

------------------------------------------------------------------------

# Table of Contents

1.  Knuth Optimization
2.  Convex Hull Trick
3.  Monotonic Queue Optimization
4.  Pattern Recognition Guide
5.  Comparison Table
6.  When NOT to Use Them
7.  Proof Intuition Sections
8.  Practice Roadmap

------------------------------------------------------------------------

# 1. Knuth Optimization

## Definition

Knuth optimization speeds up interval DP of form:

dp\[i\]\[j\] = min over k ( dp\[i\]\[k\] + dp\[k\]\[j\] ) + cost(i,j)

Naive complexity = O(n³)

Knuth reduces → O(n²)

------------------------------------------------------------------------

## Required Conditions

Must satisfy BOTH:

1)  Quadrangle Inequality\
    cost(a,c)+cost(b,d) ≤ cost(a,d)+cost(b,c)

2)  Monotonicity of opt opt\[i\]\[j−1\] ≤ opt\[i\]\[j\] ≤
    opt\[i+1\]\[j\]

------------------------------------------------------------------------

## Intuition

Optimal split point moves only forward. So instead of testing all k ∈
\[i...j\], we test only:

k ∈ \[ opt\[i\]\[j−1\] , opt\[i+1\]\[j\] \]

This shrinks search range drastically.

------------------------------------------------------------------------

## When to Recognize It

Look for: - interval merging - partitioning segments - combining
adjacent blocks - minimizing merge cost

------------------------------------------------------------------------

## 8 Classic Applications

1.  Optimal BST
2.  Matrix chain multiplication (special cases)
3.  Merge stones problems
4.  Optimal file merging
5.  Text justification variants
6.  Polygon triangulation variants
7.  Huffman-like interval merges
8.  Partitioning arrays with additive cost

------------------------------------------------------------------------

## Template

for len in range(2,n+1): for i in range(n-len+1): j = i+len-1 for k in
range(opt\[i\]\[j-1\], opt\[i+1\]\[j\]+1): relax

------------------------------------------------------------------------

## Why It Works (Proof Idea)

Quadrangle inequality guarantees that choosing a farther split never
becomes better again after it stops being optimal.

Equivalent interpretation: The cost function is convex in k.

------------------------------------------------------------------------

------------------------------------------------------------------------

# 2. Convex Hull Trick (CHT)

------------------------------------------------------------------------

## Problem Form

dp\[i\] = min_j ( m\[j\]\*x\[i\] + b\[j\] )

Interpretation: Each j defines a line We query best line at x\[i\].

------------------------------------------------------------------------

## Types

1.  Monotonic slopes + monotonic queries → deque
2.  Only slopes monotonic → Li Chao Tree
3.  Arbitrary → dynamic CHT

------------------------------------------------------------------------

## Recognition Signals

You see:

dp\[i\] = dp\[j\] + A\[j\]\*B\[i\]

or

dp\[i\] = min(dp\[j\] + (i-j)²)

Quadratic or linear separable terms → CHT candidate.

------------------------------------------------------------------------

## Geometry Insight

Each transition = line\
Each state = query x

We maintain lower envelope of lines.

------------------------------------------------------------------------

## 8 Places It Appears

1.  Divide array into segments minimizing squared cost
2.  DP on prefix with linear penalty
3.  Weighted interval DP
4.  Quadratic transition cost
5.  Convex cost functions
6.  DP + slopes monotonic
7.  Optimization after algebraic expansion
8.  Dynamic programming on coordinates

------------------------------------------------------------------------

## Why It Works

We are replacing brute-force min over all lines with geometric structure
storing only relevant ones.

Lines that will never be optimal are removed.

------------------------------------------------------------------------

## Complexity

  Structure      Time
  -------------- ----------------
  Deque CHT      O(n)
  Li Chao        O(n log range)
  Dynamic hull   O(n log n)

------------------------------------------------------------------------

------------------------------------------------------------------------

# 3. Monotonic Queue Optimization

------------------------------------------------------------------------

## DP Form

dp\[i\] = min(dp\[j\]) for j in window \[L(i)...R(i)\]

Naive: O(nk)

Optimized: O(n)

------------------------------------------------------------------------

## Idea

Maintain deque storing candidates in increasing order of dp value.

Front always contains best answer.

------------------------------------------------------------------------

## Recognition Signals

You see: - sliding window constraint - jumps limited to k distance -
"last k elements" - range minimum queries

------------------------------------------------------------------------

## 8 Applications

1.  Jump game DP
2.  Constrained subsequence sum
3.  Shortest path with window restriction
4.  Max sum subarray with length limit
5.  DP with distance constraint
6.  Queue-based BFS DP
7.  Partition with length limits
8.  Range minimum transition DP

------------------------------------------------------------------------

## Template

while deque.front \< window_start: pop_front()

dp\[i\] = dp\[deque.front\]

while deque not empty and dp\[back\] ≥ dp\[i\]: pop_back()

push_back(i)

------------------------------------------------------------------------

## Why It Works

Deque stores only useful candidates. If a state is worse AND older → it
can never win later.

This is a dominance rule.

------------------------------------------------------------------------

------------------------------------------------------------------------

# 4. Pattern Recognition Guide

If you see quadratic inner loop → try CHT or Knuth.

If transition range slides → monotonic queue.

If cost has structure like: A\[j\]\*B\[i\] + C\[j\] → CHT.

If interval splitting → Knuth.

------------------------------------------------------------------------

------------------------------------------------------------------------

# 5. Comparison Table

  Technique   Typical Complexity Drop
  ----------- -------------------------
  Knuth       n³ → n²
  CHT         n² → n log n or n
  Deque       nk → n

------------------------------------------------------------------------

------------------------------------------------------------------------

# 6. When NOT to Use Them

Knuth fails if: - cost not convex - opt not monotonic

CHT fails if: - expression not linearizable

Deque fails if: - window not monotonic

------------------------------------------------------------------------

------------------------------------------------------------------------

# 7. Proof Intuition Summaries

Knuth → convexity of partition point\
CHT → convex hull dominance\
Deque → dominance + sliding window

All three rely on eliminating states that can never be optimal.

------------------------------------------------------------------------

------------------------------------------------------------------------

# 8. Practice Roadmap

Beginner Order 1. Sliding window DP → deque 2. Linear DP → CHT 3.
Interval DP → Knuth

Intermediate 4. Dynamic hull 5. Li Chao tree 6. Knuth proofs

Advanced 7. Combining CHT + divide & conquer 8. Offline convex hull
queries

------------------------------------------------------------------------

------------------------------------------------------------------------

# Final Insight

These optimizations are not tricks. They are all manifestations of one
idea:

REMOVE STATES THAT CAN NEVER BE OPTIMAL.

Master that principle → you recognize them instantly.
