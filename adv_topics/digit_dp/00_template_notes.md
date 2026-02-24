# Digit DP

## 1. What is Digit DP?

Digit DP is a technique used to count or optimize over numbers in a
range `[L, R]` where: - constraints depend on digits - brute force
iteration is impossible

Instead of iterating numbers, we iterate **digit by digit** and build
numbers respecting constraints.

Typical constraints: 
- digit sum 
- no consecutive equal digits 
- count numbers with k non‑zero digits 
- divisible by m 
- contains pattern 
- digit frequency 
- palindrome conditions

------------------------------------------------------------------------

## 2. Core Idea

We process digits from **most significant → least significant**.

State usually contains:

    pos        → current digit index
    tight      → are we still restricted by prefix of bound?
    state vars → problem specific
    started    → have we placed non‑leading digit yet?

------------------------------------------------------------------------

## 3. Tight Flag Explained

`tight = 1`\
→ current prefix matches bound exactly\
→ next digit ≤ bound\[pos\]

`tight = 0`\
→ already smaller\
→ next digit can be 0--9 freely

Transition:

    limit = tight ? digits[pos] : 9
    for d in 0..limit:
        next_tight = tight && (d == limit)

------------------------------------------------------------------------

## 4. Leading Zero Handling (started flag)

Leading zeros create ambiguity.

Example: counting numbers with digit sum = 5

Number 005 should behave same as 5.

We use:

    started = false → still leading zeros
    started = true  → real number started

Rules: - if not started and digit = 0 → still not started - constraints
apply only when started = true

Sometimes you **do NOT need started**: 
- when leading zeros don't affect logic 
- when digit property unaffected by zeros 
- when length fixed

------------------------------------------------------------------------

## 5. Range Handling

To count for `[L, R]`:

    answer(R) − answer(L−1)

So we write solver for:

    count(x) = numbers from 0 → x satisfying condition

------------------------------------------------------------------------

## 6. Standard Template (Most Problems)

``` cpp
string s;
long long dp[20][2][2][STATE];

long long dfs(int pos, int tight, int started, STATE params) {
    if (pos == s.size())
        return base_case(params, started);

    long long &res = dp[pos][tight][started][params];
    if (res != -1) return res;

    res = 0;
    int limit = tight ? s[pos]-'0' : 9;

    for (int d = 0; d <= limit; d++) {
        int ntight = tight && (d == limit);
        int nstarted = started || (d != 0);

        STATE next = transition(params, d, nstarted);

        if (valid(next, nstarted))
            res += dfs(pos+1, ntight, nstarted, next);
    }

    return res;
}
```

------------------------------------------------------------------------

## 7. When Started Flag NOT Needed

Remove it when: 
- leading zeros behave same as real zeros 
- counting digits independently 
- property unaffected by prefix length

Simpler state:

    dp[pos][tight][state]

------------------------------------------------------------------------

## 8. Alternative Templates

### A. Fixed Length Only

Used when numbers must have exact digits (no leading zero allowed)

    dp[pos][tight][state]

Start from pos=0 with started=true implicitly.

------------------------------------------------------------------------

### B. Digit Sum Only

If only sum tracked:

    dp[pos][tight][sum]

------------------------------------------------------------------------

### C. Modulo Problems

    dp[pos][tight][mod]

Transition:

    new_mod = (old_mod*10 + digit) % m

------------------------------------------------------------------------

### D. Bitmask Tracking Digits

Used when tracking used digits.

    dp[pos][tight][mask]

Mask size = 2\^10

------------------------------------------------------------------------

### E. Pattern Matching (substring)

Use automaton / KMP state:

    dp[pos][tight][kmp_state]

------------------------------------------------------------------------

## 9. Base Case Logic Variants

At end of digits:

Return:

  Problem type          Return
  --------------------- --------------------------
  Count valid numbers   1 if condition satisfied
  Sum digits            return accumulated sum
  Minimum value         return cost
  Maximum value         return best

------------------------------------------------------------------------

## 10. Common Mistakes

-   forgetting L−1
-   incorrect tight propagation
-   not resetting dp between testcases
-   wrong leading zero logic
-   using int instead of long long
-   forgetting modulo

------------------------------------------------------------------------

## 11. 15 Important Problem Types

------------------------------------------------------------------------

### 1. Count numbers with digit sum = S

State: `sum`

------------------------------------------------------------------------

### 2. Count numbers with digit sum divisible by k

State: `sum % k`

------------------------------------------------------------------------

### 3. Count numbers with exactly k non‑zero digits

State: `countNonZero`

------------------------------------------------------------------------

### 4. Count numbers with no adjacent equal digits

State: `lastDigit`

------------------------------------------------------------------------

### 5. Count numbers containing digit d at least once

State: `seen`

------------------------------------------------------------------------

### 6. Count numbers where digits strictly increase

State: `lastDigit`

------------------------------------------------------------------------

### 7. Count numbers divisible by m

State: `mod`

------------------------------------------------------------------------

### 8. Count numbers with digit frequency constraints

State: digit frequency vector

------------------------------------------------------------------------

### 9. Count numbers whose digits XOR = k

State: xor value

------------------------------------------------------------------------

### 10. Count palindromes ≤ N

Construct half digits only.

------------------------------------------------------------------------

### 11. Count numbers with pattern substring

State: KMP index

------------------------------------------------------------------------

### 12. Sum of digits of numbers ≤ N

Return accumulated sum

------------------------------------------------------------------------

### 13. Count numbers with prime digit sum

State: sum

Check prime at end.

------------------------------------------------------------------------

### 14. Count numbers with distinct digits

State: mask of used digits

------------------------------------------------------------------------

### 15. Count numbers with exactly k occurrences of digit d

State: count

------------------------------------------------------------------------

## 12. Optimization Tricks

### State compression

Use bitmask or modulo to shrink dimension.

### Memo only when tight=0

Optimization:

    if (!tight && dp known) return dp

Because tight=1 states unique.

------------------------------------------------------------------------

### Digit vector precomputation

    vector<int> digits;
    while(n){
     digits.push_back(n%10);
     n/=10;
    }
    reverse(digits)

------------------------------------------------------------------------

## 13. Complexity Formula

    O(digits × states × transitions)
    ≈ 19 × state × 10

Usually \< 10 million operations.

------------------------------------------------------------------------

## 14. When Digit DP is Required (Recognition Guide)

If problem contains:

-   range \[L,R\]
-   digit property
-   cannot brute force
-   constraints up to 10\^18

→ Digit DP

------------------------------------------------------------------------

## 15. Mental Checklist Before Coding

✔ convert number → string\
✔ define state\
✔ decide need started flag\
✔ write transition\
✔ write base case\
✔ memo only when tight=0

------------------------------------------------------------------------

## 16. Master Template 
``` cpp
long long solve(string s){
    memset(dp,-1,sizeof(dp));
    return dfs(0,1,0,initial_state);
}
```

Answer for range:

    solve(R) - solve(L-1)

------------------------------------------------------------------------


