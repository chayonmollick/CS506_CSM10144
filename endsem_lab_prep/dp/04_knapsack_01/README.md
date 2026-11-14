# 04. 0/1 Knapsack (max value + chosen items)

Source: DP slides, "Knapsack Problem" (KNAPSACK(n, W), FIND-ITEMS, worked example W = 8);
course note "Dynamic Programming: 0-1 Knapsack" (greedy counterexample, W = 50).

## Problem

There are n items; item i has weight w_i and value v_i. Each item can be taken at most once.
Choose items with total weight at most W and maximum total value. Print the maximum value and
the chosen items.

Use the FIND-ITEMS rule to pick the items: walk i = n down to 1 and take item i only when the
table row changes (M[i][w] ≠ M[i−1][w]). Print the chosen indices in increasing order.

**Input**
- Line 1: n W
- Next n lines: w_i v_i

**Output**
- Line 1: the maximum total value
- Line 2: the chosen item indices (1-based, increasing), space-separated; an empty line if none

**Constraints**: 1 ≤ n ≤ 100, 0 ≤ W ≤ 10^4, 1 ≤ w_i ≤ 10^4, 0 ≤ v_i ≤ 10^9 (use `long long`).

**Sample Input**
```
4 8
2 3
3 4
4 5
5 6
```

**Sample Output**
```
10
2 4
```

## Idea

- Subproblem: M[i][w] = best value using only items 1..i with capacity w.
- Recurrence: M[0][w] = 0;
  if w_i > w: M[i][w] = M[i−1][w] (cannot fit);
  else M[i][w] = max(M[i−1][w], v_i + M[i−1][w − w_i]) (leave it / take it).
- Fill order: row by row (i = 1..n); row i only reads row i − 1.
- Reconstruction (FIND-ITEMS): start at (n, W). If M[i][w] ≠ M[i−1][w] item i was taken: output
  it and set w = w − w_i; then go to row i − 1. No extra table is needed.

## Pseudocode

```
function KNAPSACK(n, W):
    for w = 0 to W:
        M[0][w] = 0
    for i = 1 to n:                       // one row per item
        for w = 0 to W:
            if wt[i] > w:
                M[i][w] = M[i-1][w]
            else:
                M[i][w] = max(M[i-1][w], val[i] + M[i-1][w - wt[i]])
    return M[n][W]

function FIND-ITEMS(n, W):
    w = W
    for i = n downto 1:
        if M[i][w] != M[i-1][w]:          // item i was taken
            output i
            w = w - wt[i]
```

## Complexity

Θ(nW) time and space — pseudo-polynomial (W is a number: its input size is only log W bits).
Value only: one array of size W + 1 with the inner loop running w = W downto wt[i].

## Edge cases / traps

- Nothing fits (or W = 0): value 0 and an empty second line.
- FIND-ITEMS outputs indices in decreasing order; reverse before printing if the statement
  asks for increasing order.
- 1-D version: the inner loop must go DOWN (w = W..wt[i]); going up reuses item i several times
  and solves the unbounded knapsack instead (dp/14).
- Greedy by value/weight fails: W = 50, items (10, 60), (20, 100), (30, 120) → greedy 160,
  optimum 220 (items 2 and 3) — test 3.
- Do not initialise M with 0 meaning "unknown" in the memoized version if 0 can be a real
  answer — use −1.

## Variants they might ask

- Exactly W (must fill completely): initialise M[0][0] = 0 and M[0][w>0] = −infinity; answer
  M[n][W] (or "impossible").
- Minimum weight / count for a target value: swap the roles — dp over value, minimise weight.
- Group (multiple-choice) knapsack, e.g. one player per position (Tutorial Q23): row i chooses
  at most one item of group i — add an inner loop over the group's items.
- Memoized version: M-KNAPSACK(i, w) with the table initialised to −1.
