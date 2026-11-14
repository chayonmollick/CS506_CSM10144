# 37. CSR Projects (low-effort / high-effort weeks)

Source: Tutorial 9 Q19. Same pattern as Kleinberg–Tardos Ch. 6 Ex. 4 (low-stress / high-stress jobs) and close to
[LeetCode 198 House Robber](https://leetcode.com/problems/house-robber/).

## Problem

A CSR team takes up one village project per week for `n` weeks. In week `i` it may do a low-effort project with value
`l[i] > 0`, a high-effort project with value `h[i] > 0`, or nothing. A high-effort project in week `i` (`i > 1`)
requires that the team does nothing in week `i − 1` (preparation); a high-effort project in week 1 is allowed.
Print the maximum total value of a plan.

**Input**
Line 1: integer `n`.
Line 2: `n` integers `l[1..n]`.
Line 3: `n` integers `h[1..n]`.

**Output**
One line: the maximum total value.

**Constraints**
1 ≤ n ≤ 10^5, 1 ≤ l[i], h[i] ≤ 10^9

**Sample Input**
```
3
1 1 1
1 3 10
```

**Sample Output**
```
11
```

(Optimal plan: low, nothing, high = 1 + 0 + 10 = 11. The senior's greedy from Q19(a) sees `h[2] = 3 > l[1] + l[2] = 2`,
so it does nothing in week 1, high in week 2, then low in week 3: only 4.)

## Idea

- Subproblem: `OPT(i)` = best value of a plan for weeks `1..i`.
- Look at week `i` in an optimal plan:
  - low effort: the rest is any optimal plan for weeks `1..i−1` → `OPT(i−1) + l[i]`;
  - high effort: week `i−1` must be empty, the rest is an optimal plan for `1..i−2` → `OPT(i−2) + h[i]`;
  - nothing: `OPT(i−1)`, but this is never better than low effort because `l[i] > 0`, so it can be dropped.
- Recurrence: `OPT(i) = max( OPT(i−1) + l[i],  OPT(i−2) + h[i] )`.
- Base cases: `OPT(0) = 0` and `OPT(−1) = 0` (this is what allows high effort in week 1).
- Fill order: `i = 1..n`; only the last two values are needed → O(1) extra space.
- Why the greedy fails: it decides week `i` by looking only at week `i + 1`; a big `h` two weeks ahead is invisible.
- Reconstruction: keep the array `OPT[0..n]`; from `i = n` go back: if `OPT(i) = OPT(i−1) + l[i]` week `i` is low
  and go to `i − 1`; else week `i` is high, week `i − 1` is nothing, go to `i − 2`.

## Pseudocode

```
function CSR_PLAN(l[1..n], h[1..n]):
    prev2 = 0                         // OPT(i-2), starts as OPT(-1)
    prev1 = 0                         // OPT(i-1), starts as OPT(0)
    for i = 1 to n:
        cur = max(prev1 + l[i], prev2 + h[i])
        prev2 = prev1
        prev1 = cur
    return prev1

Main:
    read n, l[1..n], h[1..n]
    print CSR_PLAN(l, h)
```

## Complexity

O(n) time, O(1) extra space (O(n) if you keep `OPT[]` to print the plan).

## Edge cases / traps

- `n = 1`: answer `max(l[1], h[1])` — needs `OPT(−1) = 0`, not "high is forbidden in week 1".
- Sum up to 10^5 · 10^9 = 10^14: `long long`.
- The "nothing" option only matters when values can be ≤ 0; then add `OPT(i−1)` as a third term in the `max`.
- Greedy one-week lookahead is wrong (sample).

## Variants they might ask

- **Values may be negative or zero**: `OPT(i) = max(OPT(i−1), OPT(i−1) + l[i], OPT(i−2) + h[i])`.
- **High effort in week 1 not allowed**: set `OPT(−1) = −∞` (equivalently `OPT(1) = l[1]`).
- **High effort needs `d` free weeks before it**: `OPT(i) = max(OPT(i−1) + l[i], OPT(i−d−1) + h[i])` with
  `OPT(≤ 0) = 0`.
- **Print the plan** as a string over {L, H, N}: walk back as described in Idea.
