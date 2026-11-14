# 31. Egg Drop (table method and moves method)

Source: Practice Set 4 Q13 — [LeetCode 887 Super Egg Drop](https://leetcode.com/problems/super-egg-drop/); Tutorial 9 Q17 (short version Q7).

Two programs, same input/output: `sol.cpp` = part (b) moves method (use this one), `sol_table.cpp` = part (a) O(kN²) table.

## Problem

You have `k` identical eggs and a building with floors `1..N`. There is an unknown floor `F` with `0 ≤ F ≤ N`:
an egg dropped from a floor `> F` breaks, from a floor `≤ F` it survives (and can be reused). A broken egg cannot be
used again. Find the minimum number of drops that guarantees finding `F` in the **worst case**.

(a) Solve it with the O(kN²) dynamic program for `T(k, N)`.
(b) Let `g(k, m)` be the maximum number of floors that can be fully resolved with `k` eggs and `m` drops. Use
`g(k, m) = g(k-1, m-1) + g(k, m-1) + 1` and print the smallest `m` with `g(k, m) ≥ N`.

**Input**
One line with two integers `k` and `N`.

**Output**
One line: the minimum worst-case number of drops.

**Constraints**
1 ≤ k ≤ 100, 1 ≤ N ≤ 10^4 (the O(kN²) table is meant for N up to a few thousand; the moves method handles all).

**Sample Input**
```
2 100
```

**Sample Output**
```
14
```

## Idea

**(a) Table.** `T[e][n]` = minimum worst-case drops with `e` eggs and `n` floors still possible.
- First drop from floor `x` (1 ≤ x ≤ n):
  - breaks → `F` is below `x`: `x-1` floors left, `e-1` eggs → `T[e-1][x-1]`;
  - survives → `F ≥ x`: `n-x` floors left, `e` eggs → `T[e][n-x]`.
  - The adversary picks the worse outcome; we pick the best `x`:
    `T[e][n] = 1 + min over x of max(T[e-1][x-1], T[e][n-x])`.
- Base cases: `T[e][0] = 0` (nothing to test), `T[1][n] = n` (one egg: must go floor 1, 2, 3, ... upwards).
- Fill order: `e = 2..k`, `n = 1..N`. Answer `T[k][N]`.

**(b) Moves.** Turn the question around: with `e` eggs and `m` drops, how many floors `g(e, m)` can we handle?
- Make the first drop at floor `g(e-1, m-1) + 1`.
  - Breaks: the floors below it — exactly `g(e-1, m-1)` of them — are solved with `e-1` eggs and `m-1` drops.
  - Survives: above it we still have `e` eggs and `m-1` drops, enough for `g(e, m-1)` more floors.
  - Plus the floor we dropped from: `g(e, m) = g(e-1, m-1) + g(e, m-1) + 1`.
- Base cases: `g(e, 0) = 0`, `g(0, m) = 0`.
- Increase `m` until `g(k, m) ≥ N`; that `m` is the answer. Keep one array `g[0..k]` and update `e` **downwards** so
  `g[e-1]` still holds the value for `m-1`.
- `k = 2`: `g(2, m) = m(m+1)/2`, and `13·14/2 = 91 < 100 ≤ 105 = 14·15/2`, so 14 drops
  (first drop from floor 14, then 27, 39, ...: each step one floor less).

## Pseudocode

```
function EGG_DROP_TABLE(k, N):              // part (a)
    T[0..k][0..N] = 0
    for n = 1 to N: T[1][n] = n
    for e = 2 to k:
        for n = 1 to N:
            T[e][n] = n
            for x = 1 to n:
                T[e][n] = min(T[e][n], 1 + max(T[e-1][x-1], T[e][n-x]))
    return T[k][N]

function EGG_DROP_MOVES(k, N):              // part (b)
    g[0..k] = 0                             // g[e] = g(e, m) for the current m
    m = 0
    while g[k] < N:
        m = m + 1
        for e = k down to 1:
            g[e] = g[e-1] + g[e] + 1
    return m

Main:
    read k, N
    print EGG_DROP_MOVES(k, N)              // or EGG_DROP_TABLE(k, N)
```

## Complexity

- (a) O(kN²) time, O(kN) space (only rows `e-1`, `e` are needed → O(N)). Binary search on `x` gives O(kN log N).
- (b) O(k·m) time where `m` = answer ≤ N, O(k) space. For `k ≥ log2(N+1)` the answer is just `⌈log2(N+1)⌉`
  (binary search), so m is small; worst case is `k = 1` (m = N). Measured: `100 10000` and `1 10000` both run in ~0.01 s.

## Edge cases / traps

- One egg: answer is `N` (linear scan) — no binary search possible.
- Many eggs: answer is `⌈log2(N+1)⌉` (N+1 possible values of F), e.g. `20 1000` → 10.
- In (a) it is `T[e-1][x-1]` (floors **below** x) and `T[e][n-x]` (floors **above** x) — mixing them up still compiles.
- In (b) update `e` from `k` down to 1 (upwards would use `g(e-1, m)` instead of `g(e-1, m-1)`).
- `g` grows like `2^m`; `long long` avoids overflow when N is large.

## Variants they might ask

- **Print the first floor to drop from**: (b) it is `min(N, g(k-1, m-1) + 1)`; (a) store the `x` achieving the min.
- **Given k and m, how many floors?** Print `g(k, m)` directly (that is the inner array after `m` rounds).
- **Huge N (10^9)**: only (b) works; special-case `k = 1` (answer N) to avoid N iterations.
- **Count probabilities / expected drops**: different DP (average instead of max), same subproblem shape.
