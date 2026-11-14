# 23. House Robber (line and circle)

Source: Practice Set 4 Q3 — [LeetCode 198 House Robber](https://leetcode.com/problems/house-robber/); part (b) is
[LeetCode 213 House Robber II](https://leetcode.com/problems/house-robber-ii/).

## Problem

There are `n` houses; house `i` holds `a[i]` money. A robber cannot rob two **adjacent** houses (the alarm goes off).

(a) The houses stand in a line (house 1 and house n are not adjacent). Find the maximum money he can rob.
(b) The houses stand in a circle (house 1 and house n are also adjacent). Find the maximum money he can rob.

Robbing no house at all is allowed.

**Input**
Line 1: integer `n`. Line 2: `n` integers `a[1] .. a[n]`.

**Output**
Line 1: the answer to (a). Line 2: the answer to (b).

**Constraints**
1 ≤ n ≤ 10^5, 0 ≤ a[i] ≤ 10^4

**Sample Input**
```
5
2 7 9 3 1
```

**Sample Output**
```
12
11
```

(Line: houses 1, 3, 5 → 2 + 9 + 1 = 12. Circle: houses 1 and 5 are now neighbours, best is houses 1, 3 → 11.)

## Idea

- Subproblem (line): `best[i]` = max loot using only houses `1..i`.
- House `i` is either skipped (`best[i-1]`) or robbed, and then house `i-1` must be skipped (`best[i-2] + a[i]`):
  `best[i] = max(best[i-1], best[i-2] + a[i])`.
- Base cases: `best[0] = 0` (no houses), `best[-1] = 0`; equivalently `best[1] = a[1]`.
- Fill order `i = 1..n`; only two previous values are needed → two variables.
- Circle: houses 1 and n cannot both be robbed, so **at least one of them is skipped**. Run the line DP twice —
  on houses `1..n-1` (house n skipped) and on houses `2..n` (house 1 skipped) — and take the max.
  Special case n = 1: the single house has no neighbour, answer `a[1]`.

## Pseudocode

```
function ROB_LINE(a, lo, hi):
    prev2 = 0, prev1 = 0                  // best[i-2], best[i-1]
    for i = lo to hi:
        cur = max(prev1, prev2 + a[i])
        prev2 = prev1
        prev1 = cur
    return prev1

function ROB_CIRCLE(a[1..n]):
    if n == 1:
        return a[1]
    return max(ROB_LINE(a, 1, n-1), ROB_LINE(a, 2, n))

Main:
    read n, a[1..n]
    print ROB_LINE(a, 1, n)
    print ROB_CIRCLE(a)
```

## Complexity

O(n) time, O(1) extra space (two passes for the circle).

## Edge cases / traps

- n = 1 in the circle: `ROB_LINE(1, 0)` and `ROB_LINE(2, 1)` would both be empty (= 0) — handle it separately.
- n = 2 in the circle: answer is `max(a[1], a[2])`, never `a[1] + a[2]`.
- Greedy "take every other house" or "take the largest first" is wrong (e.g. `10 1 1 10` → 20 = houses 1 and 4).
- `long long` is not needed for these limits (≤ 5·10^8), but it costs nothing.

## Variants they might ask

- **Print the houses robbed**: keep the full array `best[0..n]`; walk back from `i = n`: if `best[i] == best[i-1]`,
  skip house i (`i--`), else house i is robbed (`i -= 2`); print the robbed list reversed.
- **Houses on a tree** (no parent–child pair): that is the company-party DP, see `33_company_party`.
- **At least k apart** (no two robbed houses within distance k): `best[i] = max(best[i-1], best[i-k-1] + a[i])`.
- **Negative values allowed**: the same recurrence works (skipping is always an option, so the answer ≥ 0).
