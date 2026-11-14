# 22. Min Cost Climbing Stairs

Source: Practice Set 4 Q2 — [LeetCode 746 Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/)

## Problem

A staircase has `n` stairs numbered `0 .. n-1`; stair `i` has a cost `cost[i]`. When you leave stair `i` you
pay `cost[i]` and climb either 1 or 2 stairs. You may start on stair 0 or on stair 1 without paying anything.
The top is position `n` (just past the last stair). Find the minimum total cost to reach the top.

**Input**
Line 1: integer `n`. Line 2: `n` integers `cost[0] .. cost[n-1]`.

**Output**
A single integer: the minimum cost to reach the top.

**Constraints**
1 ≤ n ≤ 10^5, 0 ≤ cost[i] ≤ 10^4

**Sample Input**
```
10
1 100 1 1 1 100 1 1 100 1
```

**Sample Output**
```
6
```

(Start on stair 0 and pay for stairs 0, 2, 4, 6, 7, 9 — every cost-1 stair; all three 100s are skipped.)

## Idea

- Subproblem: `dp[i]` = minimum cost to **stand on** position `i` (nothing paid for `i` yet).
- The last move into `i` came from `i-1` (paying `cost[i-1]`) or from `i-2` (paying `cost[i-2]`):
  `dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2])`.
- Base cases: `dp[0] = dp[1] = 0` (free start on stair 0 or 1).
- Fill order: `i = 2 .. n`. Answer: `dp[n]` (the top is position `n`, not stair `n-1`).
- Only two previous values are used, so O(1) space is possible.

## Pseudocode

```
function MIN_COST_CLIMB(cost[0..n-1]):
    dp[0] = 0, dp[1] = 0
    for i = 2 to n:
        dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2])
    return dp[n]

Main:
    read n, cost[0..n-1]
    print MIN_COST_CLIMB(cost)
```

## Complexity

O(n) time, O(n) space (O(1) with two variables).

## Edge cases / traps

- The answer is `dp[n]`, **not** `dp[n-1]`: you must step past the last stair.
- n = 1: start on stair 1 = the top, answer 0 (the loop does not run). The dp array has size n+1 ≥ 2.
- Do not add `cost[i]` when you *arrive* at `i` — the cost is paid when you leave a stair.
- Equivalent formulation `f[i] = cost[i] + min(f[i-1], f[i-2])` (cost to leave stair i), answer `min(f[n-1], f[n-2])`;
  be consistent with whichever one you choose.

## Variants they might ask

- **Must start at stair 0**: set `dp[1] = cost[0]` instead of 0.
- **Steps 1..k**: `dp[i] = min over s = 1..min(k,i) of dp[i-s] + cost[i-s]`, O(nk).
- **Print the stairs used**: store `from[i]` = `i-1` or `i-2` (whichever gave the min); walk back from `n` until
  position 0 or 1, then print in reverse.
- **Pay on arrival instead** (cost of the stair you land on, top is free): `dp[i] = cost[i] + min(dp[i-1], dp[i-2])`.
