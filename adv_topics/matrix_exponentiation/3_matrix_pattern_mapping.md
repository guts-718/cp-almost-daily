# Matrix Exponentiation — Problem → Pattern Recognition Table

A fast lookup guide to instantly identify which matrix structure to use based on problem statement patterns.

---

# HOW TO USE THIS TABLE

When reading a problem:

1. Scan recurrence
2. Match pattern description
3. Use corresponding matrix structure

---

# CORE PATTERN TABLE

| Problem Clue | Pattern Type | State Size | Matrix First Row | Notes |
|--------------|-------------|------------|------------------|------|
Nth term depends on last 2 | Fibonacci | 2 | [1 1] | Classic |
Nth depends on last k | k-order recurrence | k | coefficients | Most common |
Linear combination | Weighted recurrence | k | weights | Standard |
Constant added each step | Constant recurrence | +1 | append constant | Add 1 state |
Contains n | Index dependent | +1 | track n | Add index state |
Contains n² | Polynomial | +2 | track n²,n | Expand state |
Contains prefix sum | Prefix DP | +1 | add sum | Track running sum |
Sum of last k | Sliding window | k | all 1s | Window sum |
Two sequences interact | Multi-state | variables | per equation | Combine states |
Transitions between states | Graph walk | nodes | adjacency row | M^k |
Probabilities | Markov chain | states | probabilities | Double precision |
String transitions | Automaton | states | transitions | Aho/KMP |
Fixed length string count | Automaton DP | states | transitions | Typical CF |

---

# RECURRENCE → MATRIX MAPPING

---

## 1. Linear Recurrence

dp[n] = a·dp[n−1] + b·dp[n−2]

Matrix:

|a b|
|1 0|

---

## 2. k-step recurrence

dp[n] = Σ cᵢ dp[n−i]

Matrix:

Row1 = coefficients  
Rows below = shift identity

---

## 3. Add constant

dp[n] = dp[n−1] + C

Add state = 1

---

## 4. Depends on index

dp[n] = dp[n−1] + n

Track n as state.

---

## 5. Depends on polynomial

dp[n] = dp[n−1] + n²

Track:
n²  
n  
1

---

## 6. Cross recurrence

a[n] = a[n−1] + b[n−1]  
b[n] = a[n−1]

State:
[a,b]

---

## 7. Lag mismatch

dp[n] = dp[n−1] + dp[n−3]

State size = 3

---

## 8. Prefix accumulation

dp[n] = dp[n−1] + pref[n−1]  
pref[n] = pref[n−1] + dp[n]

State:
[dp,pref]

---

## 9. Sliding window sum

dp[n] = dp[n−1] + dp[n−2] + … + dp[n−k]

Matrix row1 = all ones

---

## 10. Graph walk

Ways to go from node u → v in k steps

Matrix = adjacency

Answer = M^k

---

## 11. Walk with weights

Weighted transitions.

Matrix entry = weight.

---

## 12. Exact step transitions

“If after K moves…”

→ exponent = K

---

## 13. Repeated operations

Apply same transformation K times.

→ matrix exponentiation

---

## 14. Digit DP with fixed length

If next state depends only on current state

→ automaton matrix

---

## 15. Tiling DP

Most tiling recurrences depend on small fixed previous states.

→ always check matrix possibility

---

# ADVANCED PATTERN DETECTION

---

### If you see:

depends on n
→ add n state

depends on n²
→ add n² and n

depends on cumulative sum
→ add prefix state

depends on two arrays
→ merge states

depends on constant
→ add 1 state

depends on dp[i−k]
→ state size ≥ k

---

# MATRIX SHAPE CHEATSHEET

| Situation | Matrix Shape |
|--------|-------------|
k recurrence | k × k |
with constant | (k+1) × (k+1) |
with n | (k+1) × (k+1) |
with n² | (k+2) × (k+2) |
two arrays | variables × variables |
graph | nodes × nodes |

---
---

# HARD CASE PATTERNS (CF 1700–1900 LEVEL)

---

### Pattern — Multiple dependencies

dp[n] = a·dp[n−1] + b·dp[n−3] + c

State = 3 + constant

---

### Pattern — Running weighted sum

dp[n] = dp[n−1] + 2*sum[n−1]

Track sum state.

---

### Pattern — Two independent recurrences

Solve separately or merge matrices.

---

### Pattern — Recurrence with alternating sign

dp[n] = dp[n−1] − dp[n−2]

Matrix:

|1 −1|
|1 0|

---

### Pattern — Modulo cycles

Sometimes recurrence cycles with matrix exponentiation.

---
---

# MASTER DECISION TREE

Does state depend on fixed past states?

No → not matrix  
Yes ↓

Is transition linear?

No → not matrix  
Yes ↓

Is N large?

No → simple DP  
Yes → MATRIX EXPONENTIATION

---

# FINAL QUICK LOOKUP GRID

| If you see | Use |
|-----------|-----|
linear recurrence | standard matrix |
constant addition | add 1 dimension |
index involved | add n |
polynomial term | add polynomial states |
multiple sequences | multi-state matrix |
walk problems | adjacency power |
string transitions | automaton matrix |
repeated operations | transformation matrix |

---

