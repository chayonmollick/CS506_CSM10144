# 08. Optimal Binary Search Tree (expected cost + tree)

Source: DP slides, "Optimal Binary Search Trees" (recurrence for e[i, j], OPTIMAL-BST, BUILD-TREE,
CLRS example with expected cost 2.75 and root k2; three-key chain counter-example, cost 1.70);
Tutorial 9 Q8.

## Problem

Keys k_1 < k_2 < ... < k_n are searched with probabilities p_1..p_n. A search for a value between
k_i and k_{i+1} (or outside all keys) ends at dummy leaf d_i, with probability q_i (i = 0..n).
The expected search cost of a BST T is

E = Σ (depth(k_i) + 1) · p_i + Σ (depth(d_i) + 1) · q_i   (the root has depth 0).

Build a BST of minimum expected cost. Print the cost with exactly 2 decimals, and the tree as the
preorder sequence of key indices (dummy leaves are not printed). If several roots give the
minimum for a range of keys, use the smallest index (the first minimum found).

**Input**
- Line 1: n
- Line 2: p_1 ... p_n
- Line 3: q_0 ... q_n
  (real numbers with at most 2 decimal places; together they sum to 1)

**Output**
- Line 1: the minimum expected search cost, 2 decimals
- Line 2: preorder of the optimal tree (key indices), space-separated

**Constraints**: 1 ≤ n ≤ 300.

**Sample Input**
```
5
0.15 0.10 0.05 0.10 0.20
0.05 0.10 0.05 0.05 0.05 0.10
```

**Sample Output**
```
2.75
2 1 5 4 3
```

## Idea

- Subproblem: e[i][j] = expected cost of an optimal BST on keys k_i..k_j (with dummies
  d_{i−1}..d_j), for 1 ≤ i ≤ n + 1, i − 1 ≤ j ≤ n. Answer e[1][n].
- w(i, j) = p_i + ... + p_j + q_{i−1} + ... + q_j. Making k_r the root pushes every node of both
  subtrees one level deeper, which adds exactly their total probability, and the root adds p_r.
- Recurrence: e[i][i−1] = q_{i−1} (only the dummy leaf);
  e[i][j] = min over i ≤ r ≤ j of e[i][r−1] + e[r+1][j] + w(i, j).
  Keep w in a table: w[i][i−1] = q_{i−1}, w[i][j] = w[i][j−1] + p_j + q_j.
- Fill order: by number of keys l = 1..n (diagonal by diagonal, like matrix chain).
- Reconstruction: root[i][j] = the r that gave the minimum. The tree is root[1][n] with left
  subtree (1, r − 1) and right subtree (r + 1, n), built recursively (BUILD-TREE); printing it
  in preorder is the same recursion.

## Pseudocode

```
function OPTIMAL-BST(p, q, n):
    for i = 1 to n + 1:                  // empty ranges
        e[i][i-1] = q[i-1]
        w[i][i-1] = q[i-1]
    for l = 1 to n:                      // number of keys
        for i = 1 to n - l + 1:
            j = i + l - 1
            e[i][j] = infinity
            w[i][j] = w[i][j-1] + p[j] + q[j]
            for r = i to j:
                t = e[i][r-1] + e[r+1][j] + w[i][j]
                if t < e[i][j]:
                    e[i][j] = t
                    root[i][j] = r
    return e, root

function PRINT-PREORDER(root, i, j):
    if j == i - 1:                       // dummy leaf d_{i-1}
        return
    r = root[i][j]
    print r
    PRINT-PREORDER(root, i, r - 1)
    PRINT-PREORDER(root, r + 1, j)
```

## Complexity

Θ(n^3) time, Θ(n^2) space. (Knuth's observation root[i][j−1] ≤ root[i][j] ≤ root[i+1][j]
gives Θ(n^2), not needed here.)

## Edge cases / traps

- Tables need row n + 1 and column 0: e[n+1][n] = q_n and e[1][0] = q_0. Allocate
  (n + 2) × (n + 1).
- Floating ties: on the sample r = 2 and r = 4 both give 2.75. In doubles two equal sums can
  come out 1e-16 apart and flip the chosen root — without EPS, test 6 prints a different tree.
  Compare with `t < e[i][j] - EPS` to keep the first minimum. Safer
  alternative: read each probability, store `llround(x * 100)` as an integer, run the DP on
  integers and print cost / 100 with 2 decimals.
- Greedy "most probable key at the root" is wrong (k5 has the largest p in the sample, yet
  the root is k2); a balanced tree is not optimal either (test 2: chain 1.70 beats balanced 2.15).
- Print with `cout << fixed << setprecision(2)`; do not mix printf with cout after
  `sync_with_stdio(false)`.

## Variants they might ask

- Only key frequencies, no dummy keys (common "freq[]" version): set all q = 0. Then cost is
  Σ (depth + 1) · freq, usually integers — use `long long` and print as an integer.
- Print the structure in CLRS style ("k2 is the root", "k1 is the left child of k2",
  "d0 is the left child of k1", ...): recurse like PRINT-PREORDER, passing the parent and side;
  an empty range (j = i − 1) prints the dummy d_j.
- Return only the root table / the root of the whole tree: print root[1][n].
- Memoized version: OBST-AUX(i, j) with e initialised to −1.
