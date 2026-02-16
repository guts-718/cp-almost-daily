# Matrix Exponentiation :
## helps optimise TC of constant space dp 
## represent like graph - the states = nodes and the transition = matrix (M[i][j] = number of edges from i → j)
---
- init[i] = number of ways to start in state i.
- in dp recurrance it represents the base case..

| Problem asks       | init should be     |
| ------------------ | ------------------ |
| ways from node s   | only s = 1         |
| ways from any node | all ones           |
| ways from set S    | mark those         |
| probability start  | probability vector |
| DP recurrence      | base cases         |



# 1. WHEN MATRIX EXPONENTIATION SHOULD TRIGGER IN YOUR BRAIN

Use it when:

• N is huge (10^9 – 10^18)  
• Recurrence depth is small
• Transitions are linear  
• State count is fixed  
• Same transition repeated many times  

Strong signals in problems:

- “After k steps…”
- “Nth term…”
- “Length = 10^18…”
- “Apply operation K times”
- “Walk exactly K steps”

---

# 2. CORE MATHEMATICAL FORM

If you can write

S(n) = M × S(n−1)

Then

S(n) = M^(n−1) × S(1)

Matrix exponentiation computes M^n in log(n).

---

# 3. UNIVERSAL DP → MATRIX CONVERSION FRAMEWORK

Follow this **mechanical method**:

STEP 1 — Identify dependency window  
How many previous states needed?

STEP 2 — Define state vector  
Include ALL required values.

STEP 3 — Write equations for each state

STEP 4 — Extract coefficients

STEP 5 — Fill matrix row‑wise

STEP 6 — Add shifting rows

---

# 4. MASTER PATTERNS

---

## Pattern A — Standard Linear Recurrence

dp[n] = a·dp[n−1] + b·dp[n−2]

State:
[dp(n), dp(n−1)]

Matrix:\
|a b|\
|1 0|

---

## Pattern B — k-order recurrence

dp[n] = Σ cᵢ dp[n−i]

State size = k

Matrix structure:

Row1 = coefficients  
Rows 2..k = shifting identity

Example k=4:

|c1 c2 c3 c4|\
|1  0  0  0 |\
|0  1  0  0 |\
|0  0  1  0 |

---

## Pattern C — With Constant Addition

dp[n] = a·dp[n−1] + b

Add constant state.

State:
[dp(n), 1]

Matrix:

|a b|\
|0 1|

---

## Pattern D — Polynomial Recurrence

dp[n] = dp[n−1] + n

Add n and constant.

State:
[dp(n), n, 1]

Transitions:

dp(n) = dp(n−1) + n  
n → n+1  
1 → 1  

Matrix:

|1 1 0|\
|0 1 1|\
|0 0 1|

---

## Pattern E — Quadratic Growth Term

dp[n] = dp[n−1] + n²

Track n² via identity:

(n+1)² = n² + 2n + 1

State:
[dp, n², n, 1]

Matrix:

|1 1 0 0|\
|0 1 2 1|\
|0 0 1 1|\
|0 0 0 1|

---

## Pattern F — Multiple Arrays

a[n] = a[n−1] + 2b[n−1]  
b[n] = 3a[n−1]

State:
[a(n), b(n)]

Matrix:

|1 2|\
|3 0|

---

## Pattern G — Two-step dependency cross relation

a[n] = a[n−1] + b[n−2]  
b[n] = a[n−1]

State:
[a(n), a(n−1), b(n), b(n−1)]

Matrix:

|1 0 0 1|\
|1 0 0 0|\
|1 0 0 0|\
|0 0 1 0|

---

## Pattern H — Prefix Sum Included

dp[n] = dp[n−1] + pref[n−1]  
pref[n] = pref[n−1] + dp[n]

State:
[dp, pref]

Matrix:

|1 1|\
|2 1|

we cant obviously have dp[n] or any term of n on RHS we need things like n-1,n-2.. so we break dp[n]

---

## Pattern I — Sliding Window Sum

dp[n] = dp[n−1] + dp[n−2] + dp[n−3] + dp[n−4]

State size = 4

Matrix first row all ones.

---

## Pattern J — Weighted sliding window

dp[n] = 1·dp[n−1] + 2·dp[n−2] + 3·dp[n−3]

Matrix:

|1 2 3|\
|1 0 0|\
|0 1 0|

---
# Advanced Matrix Exponentiation Patterns — Deep Explanation Guide

Focus: **how to recognize**, **how to build matrix**, and **why it works**.

---

# Pattern K — Graph Walks

### Recognition Clues
Problems that say:

- number of ways to reach node
- exactly k steps
- walks of length k
- transitions between nodes

---

### Core Idea

Treat each node as a state.

Transition from node i → j exists if edge exists.

Adjacency matrix **is the transition matrix**.

---

### Matrix Definition

Let graph have N nodes.

Matrix M:

M[i][j] = number of edges from i → j

---

### Why M² Works

Multiplying matrices composes transitions.

(M²)[i][j] counts:

number of ways to go  
i → x → j

which is exactly 2-step paths.

So:

M^k → number of walks of length k.

---

### Example

Graph:

1 → 2  
2 → 3  
1 → 3  

Matrix:

|0 1 1|
|0 0 1|
|0 0 0|

M² gives all length‑2 paths.

---

### When To Use

- k is large (1e9)
- graph small (≤50 nodes)
- need exact k steps

---

---

# Pattern L — Automaton / String DP

Used when processing characters sequentially and state depends only on previous state.

---

### Recognition Clues

- number of strings of length k
- forbidden substring
- pattern matching automaton
- KMP / Aho automaton
- next state depends only on current state + char

---

### State

Automaton state.

Example:
Matching pattern "aba"

States:
0 = nothing matched  
1 = matched a  
2 = matched ab  

---

### Matrix Construction

M[i][j] = number of characters that move state i → j.

If alphabet size = 26:

Count how many letters cause each transition.

---

### Example

Binary strings avoiding "11".

States:

0 = last digit 0  
1 = last digit 1  

Transitions:

0 → 0 (add 0)  
0 → 1 (add 1)  
1 → 0 (add 0)  

Matrix:

|1 1|
|1 0|

Answer = M^length × initial.

---

### Why This Works

Processing a string of length k is just:

apply transition k times.

That is repeated multiplication → matrix exponentiation.

---

---

# Pattern M — Digit DP Fixed Length

Matrix expo works when digit DP:

- has fixed number of states
- next state depends only on current state
- no tight constraint

---

### Recognition Clues

- count numbers of length k
- digit transitions only depend on previous digit
- no upper bound constraint

---

### Example

Count length k numbers where adjacent digits differ by ≤2.

State = last digit (0–9).

Transitions:

i → j allowed if |i−j| ≤ 2.

Matrix size = 10×10.

Answer = M^(k−1).

---

### When NOT usable

Digit DP with tight bound (≤N)  
because transitions depend on prefix comparison.

---

---

# Pattern N — Markov Chains

This is probabilistic version of graph walk.

---

### Recognition Clues

- probability after k steps
- random transitions
- stochastic process
- expected state after k operations

---

### Matrix Definition

M[i][j] = probability of moving from i → j.

---

### State Vector

Probability distribution vector:

P(n) = distribution after n steps.

---

### Formula

P(k) = M^k × P(0)

---

### Example

Weather model:

Sunny → Rainy with prob 0.3  
Sunny → Sunny with prob 0.7  

Matrix:

|0.7 0.3|
|0.4 0.6|

Exponentiate to get future distribution.

---

### Important Note

Matrix multiplication rules remain same — only numbers are floating.

---

---

# Pattern O — Repeated Linear Transformation

This is the most general and most powerful pattern.

---

### Recognition Clues

- apply same operation k times
- transform vector repeatedly
- update rule linear

---

### Formal Form

V ← A·V

Repeated k times:

V = A^k V₀

---

### Example

Transform vector:

x' = 2x + y  
y' = x + 3y  

Matrix:

|2 1|
|1 3|

Apply k times → exponentiate matrix.

---

---

# Deep Insight

ALL matrix exponentiation problems reduce to:

> repeated application of same linear transformation.

Whether it is:

- DP recurrence
- graph movement
- probability
- string transitions

They are all identical mathematically.

---

---

# Pattern Comparison Table

| Pattern | State Meaning | Matrix Meaning |
|--------|---------------|----------------|
Graph Walk | current node | edges |
Automaton | pattern state | char transitions |
Digit DP | last digit | allowed digit moves |
Markov | probability state | probability transition |
Transform | vector | linear mapping |

---

---

# Universal Construction Method

If system can be written as:

new_state[i] = Σ coeff * old_state[j]

→ directly becomes matrix row.

---

---

# Advanced Contest Trick

If constraints say:

K ≤ 50  
N ≤ 10^18  

That is almost guaranteed matrix exponentiation.

---

---

# Common Pitfalls

Wrong direction matrix  
Wrong exponent  
Forgetting initial vector  
Mixing row/column order  
Incorrect state definition  

---

---

# Final Mental Model

Matrix exponentiation is just:

**fast simulation of repeated transitions**

Nothing more.

---


---

# 5. HOW TO BUILD MATRIX FROM EQUATIONS

Example:

dp[n] = 2dp[n−1] + 3dp[n−3]

State:
[dp(n), dp(n−1), dp(n−2)]

Equations:

dp(n)   = 2dp(n−1) + 0dp(n−2) + 3dp(n−3)
dp(n−1) = 1dp(n−1)
dp(n−2) = 1dp(n−2)

Matrix:

|2 0 3|\
|1 0 0|\
|0 1 0|

---

# 6. HARD CONVERSION EXAMPLES

---

### Example 1 — Mixed recurrence

dp[n] = 3dp[n−1] + 4dp[n−2] + 5

State:
[dp, dp(n−1), 1]

Matrix:

|3 4 5|\
|1 0 0|\
|0 0 1|

---

### Example 2 — Recurrence with index multiplier

dp[n] = dp[n−1] + n·dp[n−2]

Need n tracked.

State:
[dp(n), dp(n−1), n, 1]

---

### Example 3 — Sum of previous results

dp[n] = dp[n−1] + sum[n−1]  
sum[n] = sum[n−1] + dp[n]

State:
[dp, sum]

Matrix:
|1 1|\
|1 1|

---

### Example 4 — Fibonacci prefix sum

F[n] = F[n−1] + F[n−2]  
S[n] = S[n−1] + F[n]

State:
[F(n), F(n−1), S(n)]

Matrix:

|1 1 0|\
|1 0 0|\
|1 0 1|

---

### Example 5 — Count binary strings with no consecutive ones

States:

dp0 = ending with 0  
dp1 = ending with 1  

Transitions:

dp0 → dp0 + dp1  
dp1 → dp0  

Matrix:

|1 1|\
|1 0|

---

### Example 6 — Tiling problems

Many tiling DPs depend only on previous states → always convertible.

Example:

dp[n] = dp[n−1] + dp[n−2] + dp[n−3]

---

---

# 7. STATE DESIGN STRATEGIES

Always include:

• any lagging values  
• any running sums  
• any constants  
• any indices (if used)  
• any polynomial terms  

---

# 8. COMMON TRICKS

If recurrence contains:

+ constant → add 1 state  
+ n → add n state  
+ n² → add n² state  
+ prefix sum → add sum state  

---

# 9. COMMON MISTAKES

Most frequent WA causes:

• wrong state ordering  
• incorrect shift rows  
• exponent off by one  
• forgetting base vector  
• not including constants in state  

---

# 10. EDGE CASE EXPONENTS

If problem asks:

nth term → exponent = n−(baseIndex)  

If starting from state 1:

Use exponent n−1.

---

# 11. COMPLEXITY

Time = O(K³ log N)  
Space = O(K²)

K = number of states

---

# 12. WHEN NOT TO USE MATRIX EXPO

Avoid if:

• transitions depend on variable conditions  
• K is large (>100)  
• recurrence not linear  
• transitions depend on previous answers non-linearly  

---

# 13. PROBLEM TYPES WHERE IT OFTEN APPEARS

Very common in:

• linear recurrence problems  
• graph walk counting  
• tiling problems  
• automaton counting  
• DP with huge N  
• probability transitions  

Frequent in:

Codeforces 1500–1900  
LeetCode Hard math/DP  

---

# 14. QUICK RECOGNITION FLOWCHART (MENTAL)

Does state depend on fixed past states?
→ no → not matrix

yes ↓

Is recurrence linear?
→ no → not matrix

yes ↓

Is N huge?
→ yes → MATRIX EXPONENTIATION

---

# 15. MASTER MENTAL TEMPLATE

1. Choose states
2. Write equations
3. Extract coefficients
4. Build matrix
5. Exponentiate
6. Multiply initial vector
7. Return first element

---

# FINAL ADVICE

Matrix exponentiation is NOT a trick.  
It is just fast repeated linear transformation.

Think of it as:

DP loop compressed into log N steps.

---

END
