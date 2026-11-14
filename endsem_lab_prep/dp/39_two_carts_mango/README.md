# 39. Two Carts in a Mango Orchard

Source: Tutorial 9 Q25. [LeetCode 741 Cherry Pickup](https://leetcode.com/problems/cherry-pickup/) is the same problem
(a round trip = two forward paths).

## Problem

A mango orchard is an `n × n` grid. Cell `(i, j)` contains `m[i][j] ≥ 0` mangoes, or is blocked (`-1`). Two carts
both start at `(1, 1)` and both travel to `(n, n)`, moving only **right** or **down** and never entering a blocked
cell. Mangoes in a cell can be collected only once (if both carts pass a cell, it counts once).
Print the maximum total number of mangoes the two carts can collect, or `-1` if `(n, n)` cannot be reached.

**Input**
Line 1: integer `n`.
Next `n` lines: `n` integers each, the grid.

**Output**
One line: the maximum total, or `-1`.

**Constraints**
1 ≤ n ≤ 100; each cell is −1 or 0 ≤ m[i][j] ≤ 1000

**Sample Input**
```
3
0 3 2
2 0 0
0 3 0
```

**Sample Output**
```
10
```

(Cart 1 goes along the top row and down the right column (3 + 2), cart 2 down the left column and along the bottom
row (2 + 3): 10. Greedy — best single path first, empty it, best path again — takes the middle path 3 + 0 + 3 = 6
first and then only one of the two 2s: 8.)

## Idea

- Why not twice the single-cart DP (Q25a): the first cart's optimal path can be a bad partner for the second (sample).
  We must choose both paths together.
- Move both carts **simultaneously**. After `t` moves (0-based) each cart is on the anti-diagonal `row + col = t`,
  so a cart is described by its row alone: cart 1 at `(r1, t − r1)`, cart 2 at `(r2, t − r2)`.
  Both carts are in the same cell exactly when `r1 = r2` — that is how "count once" is handled.
- Subproblem: `dp[t][r1][r2]` = max mangoes collected so far with the carts at those two cells (−∞ if impossible).
- Each cart's previous cell was either above (row − 1) or to the left (same row) → 4 combinations:
  `dp[t][r1][r2] = gain + max( dp[t−1][r1][r2], dp[t−1][r1−1][r2], dp[t−1][r1][r2−1], dp[t−1][r1−1][r2−1] )`,
  `gain = m[r1][c1] + (r1 ≠ r2 ? m[r2][c2] : 0)`; the state is −∞ if either cell is blocked.
- Base case: `dp[0][0][0] = m[0][0]` (start not blocked). Answer: `dp[2n−2][n−1][n−1]`, or −1 if it is −∞.
- Fill order: `t = 1..2n−2`; only layer `t − 1` is needed, so two `n × n` layers suffice.
- Correctness: any pair of paths gives a sequence of states with these transitions and vice versa; summing per
  diagonal counts every cell visited by at least one cart exactly once (both carts can be in the same cell only at
  the same time `t`, because `t` = row + col).

## Pseudocode

```
function TWO_CARTS(m[0..n-1][0..n-1]):
    if m[0][0] == -1 or m[n-1][n-1] == -1: return -1
    dp[r1][r2] = -INF for all r1, r2
    dp[0][0] = m[0][0]
    for t = 1 to 2n - 2:
        nd[r1][r2] = -INF for all r1, r2
        for r1 = max(0, t-n+1) to min(n-1, t):
            for r2 = max(0, t-n+1) to min(n-1, t):
                c1 = t - r1, c2 = t - r2
                if m[r1][c1] == -1 or m[r2][c2] == -1: continue
                best = max(dp[r1][r2], dp[r1-1][r2], dp[r1][r2-1], dp[r1-1][r2-1])   // skip r-1 < 0
                if best == -INF: continue
                gain = m[r1][c1]
                if r1 != r2: gain = gain + m[r2][c2]
                nd[r1][r2] = best + gain
        dp = nd
    if dp[n-1][n-1] == -INF: return -1
    return dp[n-1][n-1]
```

## Complexity

O(n^3) time (2n − 1 diagonals × n × n row pairs × 4), O(n^2) space with two layers.

## Edge cases / traps

- Counting a shared cell twice — the `r1 ≠ r2` test is the whole trick.
- Start or end blocked, or a wall that cuts them apart → `-1` (−∞ states must never be extended; check before adding).
- `n = 1`: answer `m[0][0]` (no moves, the cell counts once).
- Reset the new layer to −∞ for every `t`; stale values from older diagonals give wrong answers.
- Use `−INF` like `−10^9` (fits `int`); max real answer ≈ 4n · 1000 = 4 × 10^5.

## Variants they might ask

- **Round trip** (go to `(n, n)` and come back up/left, LeetCode 741): the return trip reversed is a second forward
  path, so it is the same DP.
- **Symmetry speed-up**: only states with `r1 ≤ r2` are needed (swap the carts), halving the work.
- **Single cart** max collection → the 2-D DP of 38 with `max`.
- **Three carts**: same diagonal trick with state `(t, r1, r2, r3)`, O(n^4), count a cell once among equal rows.
