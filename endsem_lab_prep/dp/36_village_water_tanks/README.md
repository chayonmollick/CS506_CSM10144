# 36. Village Water Tanks (k tanks on a line)

Source: Tutorial 9 Q24 (short version Q10). Same problem as [LeetCode 1478 Allocate Mailboxes](https://leetcode.com/problems/allocate-mailboxes/).

## Problem

`n` houses lie along a straight village road at positions `x[1] ≤ x[2] ≤ ... ≤ x[n]`. The panchayat will build `k`
water tanks anywhere on the road; each house uses its nearest tank. Minimise the total distance from the houses to
their tanks and print it.

**Input**
Line 1: two integers `n` and `k`.
Line 2: `n` integers `x[1] ≤ ... ≤ x[n]`.

**Output**
One line: the minimum total distance.

**Constraints**
1 ≤ k ≤ n ≤ 500, 0 ≤ x[i] ≤ 10^9 (positions may repeat)

**Sample Input**
```
5 3
1 4 8 10 20
```

**Sample Output**
```
5
```

(Tanks at 4, 10 and 20 serve {1, 4}, {8, 10} and {20}: 3 + 2 + 0 = 5.)

## Idea

- Two facts (Tutorial Q24a): (1) one tank serving houses `i..j` is best placed at a **median** `x[mid]`,
  `mid = (i + j) / 2` — moving it towards the side with more houses always shortens the total; (2) in some optimal
  solution every tank serves a **contiguous block** of houses (each house goes to its nearest tank, so the sorted
  houses split into consecutive groups).
- So the problem becomes: split `1..n` into at most `k` consecutive blocks, minimising the sum of block costs.
- Block cost with prefix sums `S[i] = x[1] + ... + x[i]`:
  `cost[i][j] = x[mid]·(mid − i + 1) − (S[mid] − S[i−1])  +  (S[j] − S[mid]) − x[mid]·(j − mid)`.
- Subproblem: `f[t][j]` = minimum total distance for houses `1..j` using at most `t` tanks.
- Recurrence (choose where the **last** block starts, at house `i`):
  `f[t][j] = min over 1 ≤ i ≤ j of  f[t−1][i−1] + cost[i][j]`.
- Base cases: `f[t][0] = 0` for every `t`; `f[0][j] = ∞` for `j ≥ 1`. Answer: `f[k][n]`.
- Fill order: `t = 1..k`, then `j = 1..n`.
- Reconstruction: store the best `i` for each `(t, j)`; from `(k, n)` the last block is `i..n`, tank at its median,
  continue from `(k − 1, i − 1)`.

## Pseudocode

```
function BLOCK_COST(i, j):                  // one tank at the median of houses i..j
    mid = (i + j) / 2
    left  = x[mid] * (mid - i + 1) - (S[mid] - S[i - 1])
    right = (S[j] - S[mid]) - x[mid] * (j - mid)
    return left + right

function WATER_TANKS(x[1..n], k):
    S[0] = 0
    for i = 1 to n: S[i] = S[i - 1] + x[i]
    for i = 1 to n:
        for j = i to n:
            cost[i][j] = BLOCK_COST(i, j)
    for t = 0 to k: f[t][0] = 0
    for j = 1 to n: f[0][j] = INF
    for t = 1 to k:
        for j = 1 to n:
            f[t][j] = INF
            for i = 1 to j:                       // last tank serves houses i..j
                f[t][j] = min(f[t][j], f[t - 1][i - 1] + cost[i][j])
    return f[k][n]
```

## Complexity

O(n^2) to precompute all block costs (O(1) each with prefix sums), O(k · n^2) for the DP; O(n^2 + k · n) space.

## Edge cases / traps

- Distances add up to about n · 10^9 = 5 × 10^11: `long long` everywhere, including `x[mid] * count`.
- Do not add `INF` to something (overflow); either check `f[t−1][i−1] < INF` or use a moderate `INF`.
- `k = n` (or more tanks than distinct positions): answer 0.
- Even block size: either middle house works as the median; `(i + j) / 2` (the lower one) is fine.
- Positions must be sorted; if the exam gives them unsorted, `sort` first.

## Variants they might ask

- **Print the tank positions**: keep `arg[t][j]` (best `i`) and walk back as in Idea; print `x[(i + j) / 2]` per block.
- **Exactly k tanks with distinct positions**: same answer as long as `k ≤` number of distinct positions; otherwise
  extra tanks just sit anywhere unused.
- **Facility cost per tank instead of a fixed k** (open a tank for cost `C`): 1-D DP
  `g[j] = min over i of g[i−1] + cost[i][j] + C`, O(n^2).
- **Squared distance** (k-means on a line): the best tank position is the block **mean**, block cost from prefix sums
  of `x` and `x²`; the DP is unchanged.
