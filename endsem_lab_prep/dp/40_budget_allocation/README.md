# 40. Budget Allocation among Districts

Source: Tutorial 9 Q21. Exam-style I/O. Pattern: resource allocation = knapsack where each item (district) has
`B + 1` "sizes".

## Problem

The government has a budget of `B` crore rupees to allocate among `k` districts for school infrastructure.
Allocating `x` crores (an integer, 0 ≤ x ≤ B) to district `i` yields an expected benefit `g_i(x)`, given as a table
(arbitrary, not necessarily increasing). The allocations must be integers and their sum must not exceed `B`.
Print the maximum total benefit `g_1(x_1) + ... + g_k(x_k)`.

**Input**
Line 1: two integers `k` and `B`.
Next `k` lines: line `i` has `B + 1` integers `g_i(0) g_i(1) ... g_i(B)`.

**Output**
One line: the maximum total benefit.

**Constraints**
1 ≤ k ≤ 100, 1 ≤ B ≤ 500, 0 ≤ g_i(x) ≤ 10^9

**Sample Input**
```
3 4
0 4 6 7 7
0 1 2 9 10
0 5 6 6 6
```

**Sample Output**
```
14
```

(3 crores to district 2 and 1 crore to district 3: 9 + 5 = 14. The marginal-gain greedy gets only 12 here, because
`g_2` is not concave: its big jump comes at the third crore.)

## Idea

- Subproblem: `f[i][b]` = maximum total benefit of districts `1..i` using at most `b` crores.
- Choice: how much district `i` gets, `x = 0..b`; the remaining `b − x` goes optimally to districts `1..i−1`:
  `f[i][b] = max over 0 ≤ x ≤ b of  f[i−1][b − x] + g_i(x)`.
- Base case: `f[0][b] = 0` for all `b` (no districts, no benefit; unspent budget is allowed).
- Answer: `f[k][B]`. Fill order: `i = 1..k`, any order of `b` (row `i` reads only row `i − 1`) → two rows suffice.
- Correctness (cut-and-paste): in an optimal allocation, if district `i` gets `x`, the allocation of districts
  `1..i−1` must be optimal for budget `b − x`, otherwise replacing it increases the total.
- Reconstruction: keep the table and the best `x` per `(i, b)`; from `(k, B)` read `x_k`, go to `(k−1, B − x_k)`.
- Note: every district contributes `g_i(x_i)` even for `x_i = 0`, so `g_i(0)` counts (it is 0 in the sample).

## Pseudocode

```
function ALLOCATE(k, B, g[1..k][0..B]):
    for b = 0 to B:
        f[b] = 0
    for i = 1 to k:
        for b = 0 to B:
            nf[b] = -INF
            for x = 0 to b:                            // x crores to district i
                nf[b] = max(nf[b], f[b - x] + g[i][x])
        f = nf
    return f[B]

Main:
    read k, B and the k rows of g
    print ALLOCATE(k, B, g)
```

## Complexity

O(k · B^2) time (100 · 500² / 2 ≈ 1.25 × 10^7), O(B) space with two rows (O(k · B) to reconstruct).

## Edge cases / traps

- "At most B" vs "exactly B": with arbitrary tables they differ. For exactly `B` use base `f[0][0] = 0`,
  `f[0][b > 0] = −∞`.
- Tables need not be increasing — giving more can lower the benefit, so do not assume `x = b` is best.
- Total up to 100 · 10^9 = 10^11: `long long`.
- The inner loop runs `x = 0..b` (not `0..B`), otherwise `b − x` is negative.

## Variants they might ask

- **Concave `g_i` (diminishing returns)**: greedy is optimal — hand out the `B` crores one at a time, always to the
  district with the largest next marginal gain `g_i(x_i + 1) − g_i(x_i)`, using a **max-heap**. O(B log k) after
  O(k) heapify. Stop early if the best gain is negative (when "at most B" and gains can be negative).

  ```
  function GREEDY_CONCAVE(k, B, g):
      total = g[1][0] + ... + g[k][0]
      x[1..k] = 0
      H = empty max-heap
      for i = 1 to k: PUSH(H, (g[i][1] - g[i][0], i))
      repeat B times:
          (gain, i) = EXTRACT_MAX(H)
          if gain < 0: break
          total = total + gain
          x[i] = x[i] + 1
          if x[i] < B: PUSH(H, (g[i][x[i] + 1] - g[i][x[i]], i))
      return total
  ```
  It fails without concavity (sample: 12 instead of 14).
- **Each district needs at least `lo_i`**: same base, but let `x` run from `lo_i` to `b`; a state with no valid `x`
  (or only −∞ predecessors) stays −∞, and if `f[k][B]` is −∞ the minimums do not fit in the budget.
- **Print the allocation**: store `argx[i][b]` and walk back from `(k, B)`.
