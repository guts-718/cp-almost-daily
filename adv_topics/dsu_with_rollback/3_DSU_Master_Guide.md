# Disjoint Set Union --- Master Cheat Sheet + Decision Flowchart

------------------------------------------------------------------------

# PART 1 --- DSU VARIANTS CHEAT SHEET

------------------------------------------------------------------------

## 1. Standard DSU

**Features** - Path compression - Union by size/rank - Fastest version

**Complexity** O(α(N)) almost constant

**Use when** - Static graph - Only unions - No undo - No history

**Typical problems** - Connectivity - Cycle detection - Kruskal MST -
Friend groups

------------------------------------------------------------------------

## 2. DSU without Path Compression

**Features** - Union by size only - No compression

**Why exists** Needed when parent structure must remain reversible or
inspectable.

**Used for** - Rollback DSU base - Structural queries

------------------------------------------------------------------------

## 3. Rollback DSU

**Features** - Undo operations - Snapshot states - Revert history

**Complexity** Find = O(log n)\
Union = O(log n)\
Rollback = O(1)

**Use when** - Dynamic graph - Remove edges - Time queries -
Backtracking

------------------------------------------------------------------------

## 4. Persistent DSU

**Features** - Query any past version - Fully persistent structure

**Use when** - Queries ask about old states - Versioned graph

**Difficulty** Hard to implement.

------------------------------------------------------------------------

## 5. Weighted DSU

Stores extra info per node.

Examples: - distance to root - parity - xor value - difference
constraints

**Use when** Relations matter, not just connectivity.

------------------------------------------------------------------------

## 6. Bipartite DSU

Tracks parity of depth.

**Use when** - Checking bipartiteness dynamically - Odd cycle detection

------------------------------------------------------------------------

## 7. DSU on Tree (Small-to-Large)

Not actual DSU, but same merging idea.

**Use when** - subtree queries - colors in subtree - frequency tracking

------------------------------------------------------------------------

## 8. Offline Dynamic Connectivity DSU

Combination of: - rollback DSU - segment tree over time

**Used when** Edges appear/disappear.

------------------------------------------------------------------------

------------------------------------------------------------------------

# PART 2 --- DSU VARIANT COMPARISON TABLE

  Variant      Undo   Version Query   Extra Info   Speed
  ------------ ------ --------------- ------------ ------------
  Standard     ❌     ❌              ❌           ⭐⭐⭐⭐⭐
  Rollback     ✔      Partial         ❌           ⭐⭐⭐
  Persistent   ✔      ✔               ❌           ⭐⭐
  Weighted     ❌     ❌              ✔            ⭐⭐⭐⭐
  Bipartite    ❌     ❌              parity       ⭐⭐⭐⭐

------------------------------------------------------------------------

------------------------------------------------------------------------

# PART 3 --- PROBLEM DECISION FLOWCHART

------------------------------------------------------------------------

## STEP 1 --- Is this connectivity?

If NO → DSU not needed.

If YES → go next.

------------------------------------------------------------------------

## STEP 2 --- Are edges only added?

YES → use Standard DSU

NO → next

------------------------------------------------------------------------

## STEP 3 --- Are edges removed?

YES → next

NO → Standard DSU

------------------------------------------------------------------------

## STEP 4 --- Can queries be offline?

YES → Rollback DSU or Reverse Queries

NO → need dynamic structure (Link Cut Tree etc.)

------------------------------------------------------------------------

## STEP 5 --- Are queries about past states?

YES → Persistent DSU

NO → Rollback DSU

------------------------------------------------------------------------

## STEP 6 --- Do edges exist in time ranges?

YES → Segment Tree + Rollback DSU

------------------------------------------------------------------------

## STEP 7 --- Do relationships have values?

YES → Weighted DSU

------------------------------------------------------------------------

## STEP 8 --- Need bipartite check?

YES → Bipartite DSU

------------------------------------------------------------------------

------------------------------------------------------------------------

# PART 4 --- PATTERN RECOGNITION GUIDE

Recognize DSU problems instantly if you see:

-   groups
-   clusters
-   connectivity
-   components
-   union operations
-   friend relations
-   merging sets

------------------------------------------------------------------------

Recognize ROLLBACK DSU if you see:

-   undo query
-   revert
-   remove edge
-   history
-   version
-   timeline
-   state branching

------------------------------------------------------------------------

Recognize WEIGHTED DSU if you see:

-   difference constraints
-   relative distance
-   xor relation
-   parity relation

------------------------------------------------------------------------

Recognize DSU ON TREE if you see:

-   subtree queries
-   colors in subtree
-   frequency of values

------------------------------------------------------------------------

------------------------------------------------------------------------

# PART 5 --- COMMON TRAPS

------------------------------------------------------------------------

### Trap 1

Trying DSU when graph has deletions online.

Wrong choice.

------------------------------------------------------------------------

### Trap 2

Using path compression in rollback DSU.

Breaks undo.

------------------------------------------------------------------------

### Trap 3

Not storing enough info for rollback.

Must store all changed values.

------------------------------------------------------------------------

### Trap 4

Forgetting offline trick.

Many problems that look impossible online are easy offline.

------------------------------------------------------------------------

------------------------------------------------------------------------

# PART 6 --- ADVANCED COMBINATIONS

Common CF combos:

DSU + segment tree\
DSU + divide & conquer\
DSU + Mo's algorithm on queries\
DSU + binary lifting\
DSU + LCA

Hard problems often mix DSU with another structure.

------------------------------------------------------------------------

------------------------------------------------------------------------

# PART 7 --- CONTEST SPEED IDENTIFICATION TRICK

Fast mental decision:

If you see: - union queries only → DSU - add + remove → rollback DSU -
subtree queries → DSU on tree - relation values → weighted DSU - time
dimension → rollback + segtree

Memorize this mapping.

------------------------------------------------------------------------

------------------------------------------------------------------------

# FINAL INTUITION

DSU problems are about:

> merging information efficiently

All variants are just specialized merging strategies.

Mastering DSU means recognizing **what type of merging problem** you are
facing.

------------------------------------------------------------------------

END
