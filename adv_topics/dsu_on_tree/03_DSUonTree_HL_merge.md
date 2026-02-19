
# DSU on Tree (Small-to-Large Merging)
## offline queries with no dynamic updates

## 1. What is DSU on Tree?

DSU on Tree (also called **Sack Technique** or **Small-to-Large merging**) is a technique used to efficiently process **subtree queries** in trees.

It is useful when:
- You need information about every subtree
- Queries depend on subtree frequency / counts
- Brute force merging would be too slow

Typical complexity improvement:
```
Naive → O(N²)
DSU on Tree → O(N log N)
```

---

## 2. When Should You Use It?

Use DSU-on-tree when:
- Queries are on **subtrees**
- You need to maintain a **data structure per subtree**
- You must combine children results
- Merging cost matters

Typical triggers:
```
"for each node, compute something about its subtree"
"count colors in subtree"
"frequency of values"
"distinct values"
"k-most frequent values"
```

---

## 3. Core Idea

Instead of rebuilding subtree data from scratch:

> Always keep the largest child’s data and merge smaller children into it.

This is called:

```
small → large merging
```

---

## 4. Why This Works (Complexity Proof Idea)

Each node’s data moves only when merged into a larger structure.

Each time it moves → container size at least doubles.

So each element moves at most:

```
log N times
```

Total complexity:
```
O(N log N)
```

---

## 5. Algorithm Structure

For each node:

Step 1 - find heavy child  
(the child with largest subtree)

Step 2 - process all light children  
→ compute  
→ then erase their data

Step 3 - process heavy child  
→ keep its data

Step 4 - merge light children into heavy

Step 5 - add current node

Step 6 - answer queries

---

## 6. Terminology

**Heavy child**  
= child with largest subtree

**Light child**  
= all other children

---

## 7. Example Walkthrough

Tree:
```
      1
    / | \
   2  3  4
         |
         5
```

Subtree sizes:
```
2=1
3=1
5=1
4=2
1=5
```

Heavy children:
```
1 → 4
4 → 5
```

Processing node 1:

1) solve 2 → clear  
2) solve 3 → clear  
3) solve 4 → keep  
4) merge 2 + 3  
5) add 1  

Now subtree(1) data is correct.

---

## 8. What Data Structure Do We Maintain?

Depends on problem. Common choices:

| Goal | Structure |
|-----|----------|
count colors | frequency array |
distinct values | set |
kth largest | multiset |
range queries | Fenwick |
mode | map + max tracker |

---

## 9. Classic Problem Types

### Type 1 — Count distinct colors in subtree
Maintain:
```
set or freq array
```

---

### Type 2 — How many colors appear ≥ k times?
Maintain:
```
freq[color]
countFreq[x] = #colors appearing x times
```

---

### Type 3 — Most frequent value in subtree
Maintain:
```
freq + track max
```

---

### Type 4 — Sum of values in subtree satisfying condition
Maintain:
```
running sum
```

---

## 10. Why We Remove Light Subtrees First

Because we only want one structure alive at a time.

If we kept all child data simultaneously:
```
memory → O(N²)
time → too slow
```

Instead:
```
solve light → delete
solve heavy → keep
merge light → final state
```

---

## 11. Visual Intuition

Think of children as bags of marbles.

You always:
```
keep biggest bag
pour smaller bags into it
```

Never:
```
pour big bag into small bag
```

---

## 12. Skeleton Template

```cpp
dfs(node):

    find heavy child

    for each light child:
        dfs(light)
        remove(light)

    dfs(heavy)

    for each light child:
        add(light)

    add(node)

    answer queries
```

---

## 13. Difference vs Other Tree Techniques

| Technique | Best For |
--------|-----------|
Euler Tour | static subtree queries |
Segment Tree | range queries |
HLD | path queries |
DSU on Tree | subtree frequency queries |

---

## 14. When NOT to Use It

Do NOT use DSU on Tree if:
- Queries are on paths instead of subtrees
- Updates happen dynamically
- You need online answers

---

## 15. Common Mistakes

Wrong heavy child selection  
Forgetting to clear light subtree  
Using slow container (multiset/map when array works)  

---

## 16. Practice Problems

Recommended problems to master DSU on Tree:

1. Distinct colors in subtree  
2. Count values ≥ k in subtree  
3. Mode of subtree  
4. Most frequent value per subtree  
5. Subtree XOR frequency  

---

## 17. Recognition Pattern 

If you see:

> For each node, compute something about its subtree

AND merging children results is expensive → think:

```
DSU on Tree
```

---

## 18. Definition

> DSU on Tree is a technique that processes subtrees efficiently by always merging smaller child data into the largest child’s data.

---

## 19. Mental Model

You are building answers bottom up (from leaves to the root).

Each subtree:
- builds data
- passes it upward
- merges efficiently

---

## 20. Final Takeaway

DSU on Tree is one of the most powerful tree techniques because it transforms problems that look quadratic into logarithmic-merging solutions.

If you master:
- heavy child selection
- small-to-large merging

It helps to solve a huge class of subtree problems.

---
