# 14. Unbounded Knapsack (items reusable) + copies of each item

Source: exam-style variant of the slides' "Knapsack Problem" (same items as the slides' 0/1
example, but every item may be taken any number of times); it generalises "Rod Cutting".

## Problem

There are n item types; type i has weight w_i and value v_i, and you may take any number of
copies of each type. Choose copies with total weight at most W and maximum total value. Print
the value and how many copies of each type you take.

If several selections are optimal, build the answer like this: with remaining capacity c (start
with c = W), take one copy of the smallest-index item i for which v_i + (best value for capacity
c − w_i) equals the best value for capacity c, then continue with c − w_i; stop when no item fits.

**Input**
- Line 1: n W
- Next n lines: w_i v_i

**Output**
- Line 1: the maximum total value
- Line 2: n integers — the number of copies of item 1, 2, ..., n

**Constraints**: 1 ≤ n ≤ 100, 1 ≤ W ≤ 10^5, 1 ≤ w_i ≤ 10^5, 1 ≤ v_i ≤ 10^9 (use `long long`).

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
12
4 0 0 0
```

(The 0/1 version of the same input — problem 04 / slides — gives only 10 with items {2, 4}.)

## Idea

- Subproblem: best[c] = maximum value with total weight ≤ c (c = 0..W).
- Recurrence: best[0] = 0; best[c] = max(0, max over i with w_i ≤ c of v_i + best[c − w_i]) —
  "which item do I put in first". Because item i can be used again, we look up best[c − w_i]
  (same table), not a "previous row".
- Fill order: c = 1, 2, ..., W — exactly BOTTOM-UP-CUT-ROD. Rod cutting is the special case
  w_i = i, v_i = p_i, W = n (but there the rod must be used completely; here leftover capacity is
  allowed because best[c] starts at 0).
- Reconstruction: choice[c] = the smallest i achieving the max (strict `>`); walk c = W,
  count choice[c], c = c − w[choice[c]], until choice[c] = 0 (nothing fits).

1-D loop direction (the key contrast with 0/1 knapsack, problem 04/05):

```
0/1:        for each item i:  for c = W downto w_i:  best[c] = max(best[c], v_i + best[c - w_i])
unbounded:  for each item i:  for c = w_i to W:      best[c] = max(best[c], v_i + best[c - w_i])
```

Going DOWN, best[c − w_i] still holds the value from before item i (item used at most once);
going UP it may already include item i (item reused).

## Pseudocode

```
function UNBOUNDED-KNAPSACK(w, v, n, W):
    for c = 0 to W:
        best[c] = 0
        choice[c] = 0
    for c = 1 to W:                          // capacity outer
        for i = 1 to n:
            if w[i] <= c and v[i] + best[c - w[i]] > best[c]:
                best[c] = v[i] + best[c - w[i]]
                choice[c] = i
    return best, choice

function FIND-COPIES(w, choice, n, W):
    cnt[1..n] = 0
    c = W
    while choice[c] != 0:
        cnt[choice[c]] = cnt[choice[c]] + 1
        c = c - w[choice[c]]
    return cnt
```

## Complexity

O(n·W) time, O(W) space (pseudo-polynomial, like 0/1 knapsack).

## Edge cases / traps

- No item fits (all w_i > W): value 0, all counts 0 — choice[W] = 0 stops the walk immediately.
- Value can reach W·max(v) ≈ 10^14: `long long`.
- Using a 2-D table M[i][c] = max(M[i−1][c], v_i + M[i][c − w_i]) also works — note the second
  term reads row i, not i − 1 (that single index is the whole difference from 0/1).
- Greedy by value/weight ratio is not optimal (integer copies): w = (6, 5), v = (13, 10), W = 10
  → greedy takes one item 1 (13), optimum is two of item 2 (20).

## Variants they might ask

- Must fill the knapsack exactly: initialise best[c] = −∞ for c > 0, best[0] = 0, and print −1
  (or "impossible") when best[W] < 0.
- Minimum cost to reach at least / exactly weight W: swap max for min (coin change (a), problem
  13, is the case "every value = 1, minimise").
- Bounded copies (at most k_i of item i): treat as 0/1 knapsack over copies, or split k_i into
  powers of two.
- Cut Ribbon (CF 189A): lengths a, b, c, maximise the number of pieces with exact fill — the
  "exactly" variant with v_i = 1.
