# DSU with Rollback 

## 1. What is DSU?

DSU (Disjoint Set Union) or Union-Find is a data structure that tracks
connected components.

Supports: - union(a,b) - find(x)

Used for: - connectivity - components - cycle detection - Kruskal MST

------------------------------------------------------------------------

## 2. Normal DSU vs Rollback DSU

  Feature              | Normal DSU   | Rollback DSU
  ---------------------| ------------ | --------------
  Path compression     | ✔           | ❌
  Union by size/rank   | ✔           | ✔
  Undo operations      | ❌          | ✔
  Persistent states    | ❌          | ✔
  Time travel queries  | ❌          | ✔

Key Difference: Normal DSU is destructive. Rollback DSU is reversible.

------------------------------------------------------------------------

## 3. Why Path Compression Cannot Be Used

Path compression changes many parents during find(). Rollback requires
reverting exactly what changed.

If we used compression: We would need to store every parent update → too
slow.

So rollback DSU uses: \> union by size ONLY

------------------------------------------------------------------------

## 4. Core Idea of Rollback

Store every modification in a stack.

When merging: store old values.

When undo: restore them.

Only store what changes: - parent pointer - size

------------------------------------------------------------------------

## 5. Data Stored Per Merge

We store:

(b_root, old_size_of_a\_root)

Why only this? Because only these change during union.

------------------------------------------------------------------------

## 6. Operations

### Find

No compression → climb parents.

Complexity: O(log n)

------------------------------------------------------------------------

### Unite

Steps: 
- 1. find roots 
- 2. attach smaller to larger 
- 3. push change to stack

Complexity: O(log n)

------------------------------------------------------------------------

### Rollback

Pop last change and restore.

Complexity: O(1)

------------------------------------------------------------------------

### Snapshot

Return stack size.

------------------------------------------------------------------------

### Rollback To Snapshot

Undo until stack size matches snapshot.

------------------------------------------------------------------------

## 7. Complexity Summary

  Operation  | Complexity
  -----------| ------------
  Find       | O(log n)
  Union      | O(log n)
  Rollback   | O(1)
  Snapshot   | O(1)

------------------------------------------------------------------------

## 8. Mental Model

Rollback DSU =

> DSU + Undo Button

------------------------------------------------------------------------

## 9. When Do Problems Need It?

Look for these signals:

### Signal 1 - Edge deletions

Normal DSU cannot delete edges.

If problem has: 
- add edge 
- remove edge 
- query connectivity

→ rollback DSU likely needed.

------------------------------------------------------------------------

### Signal 2 - Offline queries

If queries can be reordered or solved offline.

Example: Queries: Add edge, Remove edge, Check connectivity

We process using divide & conquer or segment tree on time.

------------------------------------------------------------------------

### Signal 3 --- Time dimension

If problem involves: - states - versions - historical queries -
reverting operations

Rollback DSU is ideal.

------------------------------------------------------------------------

### Signal 4 --- Divide & Conquer on Queries

Classic pattern:

solve(l,r): apply operations affecting segment recurse rollback

------------------------------------------------------------------------

## 10. Common Problem Types

------------------------------------------------------------------------

### Type 1 --- Dynamic Connectivity

Graph changes over time.

Queries: - add edge - remove edge - same component?

------------------------------------------------------------------------

### Type 2 --- Offline Edge Removal

Instead of removing edges: Process queries in reverse.

Rollback DSU lets you simulate states.

------------------------------------------------------------------------

### Type 3 --- Queries on Versions

Operations: - merge - revert - query

------------------------------------------------------------------------

### Type 4 --- Segment Tree Over Time

Each edge lives during an interval.

Store edges in segment tree nodes. Traverse tree: - apply edges - answer
queries - rollback

------------------------------------------------------------------------

### Type 5 --- Backtracking Search

Used in: - recursive exploration - branching states

Example: Try union → recurse → rollback.

------------------------------------------------------------------------

## 11. Example Problems

Classic platforms where it appears: - Codeforces dynamic connectivity -
Offline queries with undo - Queries with time dimension

Typical difficulty: \> 1800--2600 rating

------------------------------------------------------------------------

## 12. Example Workflow (Typical CF Problem)

Given queries: Add edge u v\
Remove edge u v\
Ask connectivity u v

Solution outline: 1. Track lifetime of each edge. 2. Map lifetimes to
segment tree. 3. DFS tree: apply edges answer queries rollback

------------------------------------------------------------------------

## 13. Advantages

✔ supports undo\
✔ fast rollback\
✔ easy branching\
✔ clean logic

------------------------------------------------------------------------

## 14. Limitations

✖ cannot use path compression\
✖ slightly slower find\
✖ more memory (history stack)

------------------------------------------------------------------------

## 15. Template Logic Walkthrough

Union(a,b): - find roots - if same → store dummy change - else: store
info merge update size

Rollback(): - restore parent - restore size - increment components

------------------------------------------------------------------------

## 16. Trick to Detect It in Contest

If you see: - dynamic graph - undo operations - revert queries - offline
queries - time ranges - divide & conquer queries

→ Think Rollback DSU immediately.

------------------------------------------------------------------------

## 17. Comparison With Other DSU Variants

  Variant         | Supports Undo  | Supports Fast Find
  ----------------| ---------------| --------------------
  Normal DSU      | ❌            |  ✔
  Rollback DSU    | ✔             |   ❌
  Persistent DSU  | ✔             |  ✔ (complex)

------------------------------------------------------------------------

## 18. Advanced Patterns

------------------------------------------------------------------------

### Pattern A - Divide & Conquer Queries

Recursively split queries and apply only relevant merges.

------------------------------------------------------------------------

### Pattern B - Segment Tree of Time

Most powerful pattern.

Used when edges exist during time intervals.

------------------------------------------------------------------------

### Pattern C - Backtracking DSU

Used in brute force with pruning.

------------------------------------------------------------------------

## 19. Key Insight Summary

Rollback DSU is used when:

> We must simulate multiple possible DSU states efficiently.

------------------------------------------------------------------------

## 20. Practice Problem Ladder

Recommended order:

1.  Simple undo union queries
2.  Dynamic connectivity offline
3.  Segment tree over time
4.  Mixed queries with branching
5.  Hard CF problems

------------------------------------------------------------------------

## Final Intuition

Normal DSU: \> build once and never go back

Rollback DSU: \> explore many timelines efficiently

------------------------------------------------------------------------
