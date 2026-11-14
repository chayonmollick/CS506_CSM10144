# 29. Burst Balloons (interval DP)

Source: Practice Set 4 Q11 — [LeetCode 312 Burst Balloons](https://leetcode.com/problems/burst-balloons/).

## Problem

There are `n` balloons in a row with numbers `v[1..n]`. When you burst balloon `i` you earn
`left × v[i] × right` coins, where `left` and `right` are the numbers on the balloons currently adjacent to `i`
(already-burst balloons are gone, so neighbours change). If there is no balloon on a side, treat it as a balloon
with number 1. Burst all balloons and maximise the total coins.

**Input**
Line 1: `n`. Line 2: `n` integers `v[1..n]`.

**Output**
One line: the maximum number of coins.

**Constraints**
1 ≤ n ≤ 300, 0 ≤ v[i] ≤ 100

**Sample Input**
```
4
3 1 5 8
```

**Sample Output**
```
167
```

(Order 1, 5, 3, 8: 3·1·5 + 3·5·8 + 1·3·8 + 1·8·1 = 15 + 120 + 24 + 8 = 167.)

## Idea

- Pad: `v[0] = v[n+1] = 1`. These two are never burst.
- Subproblem: `dp[i][j]` = max coins from bursting **all balloons strictly between `i` and `j`**, while `i` and `j`
  are still present (open interval).
- Key trick: choose the **last** balloon `k` burst in `(i, j)`. When `k` is last, its neighbours are exactly `i` and
  `j`, and the two sides `(i, k)` and `(k, j)` are independent (k separates them the whole time):
  `dp[i][j] = max over i < k < j of dp[i][k] + dp[k][j] + v[i]·v[k]·v[j]`.
  (Choosing the *first* balloon does not work: after it bursts, its two neighbours become adjacent and the sides
  are no longer independent.)
- Base case: `dp[i][i+1] = 0` (nothing between them).
- Fill order: by increasing length `gap = j - i` (2, 3, ..., n+1). Answer `dp[0][n+1]`.
- Reconstruction: store `best_k[i][j]`; the burst order is "solve `(i,k)`, solve `(k,j)`, then burst `k`" (post-order).

## Pseudocode

```
function BURST_BALLOONS(v[1..n]):
    v[0] = 1, v[n+1] = 1
    dp[0..n+1][0..n+1] = 0
    for gap = 2 to n + 1:
        for i = 0 to n + 1 - gap:
            j = i + gap
            for k = i + 1 to j - 1:          // k is burst LAST in (i, j)
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + v[i] * v[k] * v[j])
    return dp[0][n+1]

Main:
    read n, v[1..n]
    print BURST_BALLOONS(v)
```

## Complexity

O(n^3) time (≈ 4.5·10^6 inner steps for n = 300), O(n^2) space.

## Edge cases / traps

- Forgetting the padding 1s, or allocating `dp` of size `n` instead of `n+2`.
- Looping `i` and `j` in plain row order: `dp[i][k]` / `dp[k][j]` would not be ready. Loop by gap (or `i` downwards, `j` upwards).
- Zeros: a `0` balloon makes every product with it 0 — the DP handles it, but greedy "burst smallest first" fails.
- `n = 1`: answer is `1 · v[1] · 1`.
- Use `long long` for safety (max is about 300 · 10^6 = 3·10^8, fits in `int`, but variants with bigger values do not).

## Variants they might ask

- **Print the order**: keep `best_k[i][j]`, then a recursive `PRINT(i, j)`: `PRINT(i,k); PRINT(k,j); print k`.
- **Minimise instead**: same table with `min` and `dp[i][j] = +inf` for `gap ≥ 2`.
- **Same skeleton (interval DP, "which element is last/root")**: matrix-chain multiplication, optimal BST,
  breaking a string (dp/34), polygon triangulation — change only the cost term.
