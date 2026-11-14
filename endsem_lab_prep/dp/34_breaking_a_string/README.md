# 34. Breaking a String (minimum total cost of breaks)

Source: Tutorial 9 Q10 (short version Q3). Same problem as [LeetCode 1547 Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/).

## Problem

A string has `n` characters. Breaking any piece of length `len` into two pieces costs `len` time units.
You are given `m` break positions `L[1] < L[2] < ... < L[m]` (break after character `L[i]`). All of them must be
performed, one at a time, in some order, and the order changes the total cost. For example, with `n = 20` and breaks
after 2, 8, 10, the left-to-right order costs 20 + 18 + 12 = 50, whereas the order 10, 2, 8 costs 20 + 10 + 8 = 38.

Print the minimum total cost and an order achieving it. The order to print is fixed as follows: first the break
performed on the whole string, then (recursively) the order for the left piece, then the order for the right piece.
If several breaks give the minimum cost for a piece, use the leftmost one.

**Input**
Line 1: two integers `n` and `m`.
Line 2: `m` integers `L[1] < ... < L[m]` (empty when `m = 0`).

**Output**
Line 1: the minimum total cost.
Line 2: the `m` break positions in the order described above, separated by single spaces (an empty line when `m = 0`).

**Constraints**
2 ≤ n ≤ 10^9, 0 ≤ m ≤ 100, 1 ≤ L[i] ≤ n − 1, strictly increasing

**Sample Input**
```
20 3
2 8 10
```

**Sample Output**
```
38
10 2 8
```

## Idea

- Add the two ends as fake boundaries: `b[0] = 0`, `b[1..m] = L`, `b[m+1] = n`. Every piece that ever exists is
  `(b[i], b[j])` for some `i < j`.
- Subproblem: `cost[i][j]` = minimum cost to perform all breaks strictly inside piece `(b[i], b[j])`.
- Choice: the **first** break done inside this piece, `b[k]` with `i < k < j`. It costs the piece length `b[j] − b[i]`
  (whatever `k` is) and leaves two independent pieces:
  `cost[i][j] = (b[j] − b[i]) + min over i<k<j of (cost[i][k] + cost[k][j])`.
- Base case: `cost[i][i+1] = 0` (no break inside).
- Fill order: by interval length `len = j − i = 2, 3, ..., m+1` (same shape as matrix-chain multiplication).
- Reconstruction: store `split[i][j] = k` (strict `<` keeps the leftmost on ties); print `b[k]`, then recurse on
  `(i, k)` and `(k, j)` — a preorder walk of the split tree.
- Why it is correct (cut-and-paste): after the first break `b[k]`, the breaks on the left and right never interact,
  so an optimal order must do each side optimally; otherwise swapping in a cheaper side order lowers the total.

## Pseudocode

```
function MIN_BREAK_COST(n, L[1..m]):
    b[0] = 0, b[1..m] = L[1..m], b[m+1] = n
    for i = 0 to m:
        cost[i][i+1] = 0
    for len = 2 to m + 1:
        for i = 0 to m + 1 - len:
            j = i + len
            best = INF
            for k = i + 1 to j - 1:
                if cost[i][k] + cost[k][j] < best:
                    best = cost[i][k] + cost[k][j]
                    split[i][j] = k
            cost[i][j] = (b[j] - b[i]) + best
    return cost[0][m+1]

function PRINT_ORDER(i, j):
    if j - i < 2: return
    k = split[i][j]
    print b[k]
    PRINT_ORDER(i, k)
    PRINT_ORDER(k, j)

Main:
    read n, m, L[1..m]
    print MIN_BREAK_COST(n, L)
    PRINT_ORDER(0, m + 1)
```

## Complexity

O(m^3) time (O(m^2) intervals × O(m) choices of `k`), O(m^2) space.

## Edge cases / traps

- The DP is over **break indices** (size m + 2), not over character positions (n can be 10^9).
- Forgetting the fake boundaries `0` and `n` — then the first break on the whole string has no interval.
- `m = 0`: answer 0 and an empty second line (the loops do nothing, `cost[0][1] = 0`).
- The piece length is added once per interval, outside the `min` — it does not depend on `k`.
- Total cost can reach about m · n = 10^11: use `long long`.
- Greedy "break nearest the middle first" or "left to right" is not optimal (sample: 50 vs 38).

## Variants they might ask

- **Only the cost**: drop `split` and `PRINT_ORDER`.
- **Cutting a stick at given points** (LeetCode 1547): identical; the cuts list may be unsorted — sort it first.
- **Print the breaks as a fully parenthesised split tree** (like matrix-chain `PRINT-OPTIMAL-PARENS`): in
  `PRINT_ORDER` print `(` before and `)` after the recursive calls.
- **Break cost depends on the piece differently** (e.g. cost = `c · len` or a fixed cost per break): change only the
  term added outside the `min`.
