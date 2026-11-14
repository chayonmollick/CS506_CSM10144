# 35. Cricket Auction (group knapsack)

Source: Tutorial 9 Q23 (short version Q9). Exam-style I/O. Pattern: multiple-choice ("group") 0/1 knapsack.

## Problem

A cricket franchise must sign players for `N` positions with a budget of `X` lakh. For each position there are `P`
available players; player `j` of position `i` costs `c[i][j]` lakh and has value `v[i][j]`. At most one player may be
signed per position (a position may also be left empty), and the total cost must not exceed `X`.
Print the maximum total value.

**Input**
Line 1: three integers `N`, `P`, `X`.
Next `N` lines: line `i` contains `2P` integers `c[i][1] v[i][1] c[i][2] v[i][2] ... c[i][P] v[i][P]`.

**Output**
One line: the maximum total value.

**Constraints**
1 ≤ N ≤ 100, 1 ≤ P ≤ 50, 1 ≤ X ≤ 10^4, 1 ≤ c[i][j] ≤ 10^4, 0 ≤ v[i][j] ≤ 10^6

**Sample Input**
```
3 2 10
4 7 6 9
3 5 5 8
2 3 7 12
```

**Sample Output**
```
17
```

(Leave position 1 empty, sign player 1 of position 2 (cost 3, value 5) and player 2 of position 3 (cost 7, value 12).)

## Idea

- Subproblem: `f[i][b]` = maximum value using positions `1..i` only, with total cost at most `b`.
- Choice for position `i`: leave it empty, or sign exactly one of its `P` players:
  `f[i][b] = max( f[i-1][b],  max over j with c[i][j] ≤ b of  f[i-1][b − c[i][j]] + v[i][j] )`.
- Base case: `f[0][b] = 0` for every `b` (nobody signed). Answer: `f[N][X]`.
- Fill order: `i = 1..N`, any order of `b` — row `i` reads only row `i − 1`. The code keeps two rows `prev`, `cur`.
- Why two rows: every candidate for position `i` must be added to a state that contains **no** player of position `i`.
  With one array updated in place and `b` running upwards, `f[b − c]` may already include a player of position `i`,
  so two players of the same position could be signed. Running `b` downwards fixes that only while every cost is
  ≥ 1 (with cost 0, `f[b − 0] = f[b]` is the entry being updated). Two rows are always safe and easier to argue.
- Correctness (cut-and-paste): in an optimal signing, removing position `i`'s choice leaves an optimal signing of
  positions `1..i−1` for the remaining budget, otherwise it could be improved.
- Reconstruction: keep the full table `f[i][b]`; walk `i = N..1` from `b = X`: if `f[i][b] = f[i−1][b]` position `i`
  is empty, otherwise find `j` with `f[i][b] = f[i−1][b − c[i][j]] + v[i][j]`, record it and set `b −= c[i][j]`.

## Pseudocode

```
function AUCTION(N, P, X, c, v):
    for b = 0 to X:
        prev[b] = 0
    for i = 1 to N:
        for b = 0 to X:
            cur[b] = prev[b]                         // position i left empty
            for j = 1 to P:
                if c[i][j] <= b:
                    cur[b] = max(cur[b], prev[b - c[i][j]] + v[i][j])
        prev = cur
    return prev[X]

Main:
    read N, P, X
    read the N lines of (cost, value) pairs
    print AUCTION(N, P, X, c, v)
```

## Complexity

O(N · P · X) time (5 × 10^7 at the limits), O(X) space with two rows (O(N · X) if you keep the table to reconstruct).

## Edge cases / traps

- "At most one per position" is the whole difference from 0/1 knapsack: do **not** treat the `N · P` players as
  independent items (that may sign two batsmen for one slot).
- Every player too expensive → answer 0 (base row is all zeros, not −∞, because spending less than `X` is allowed).
- Values may be 0; positions may stay empty — so `cur[b]` must start from `prev[b]`.
- Sum of values ≤ 100 · 10^6 fits in `int`, but `long long` costs nothing.

## Variants they might ask

- **Every position must be filled** (exactly one player each): keep base `f[0][b] = 0`, but start
  `cur[b] = −∞` instead of `prev[b]` (no "leave empty" option) and skip `prev[...] = −∞`; print −1 if `f[N][X]` is −∞.
- **Print the chosen player per position** (0 = empty): keep the 2-D table and walk back as described in Idea.
- **Budget must be spent exactly**: base `f[0][0] = 0`, `f[0][b > 0] = −∞`, answer `f[N][X]`.
- **Plain 0/1 knapsack** is the special case `P = 1`; unbounded knapsack would read `cur[b − c]` instead of `prev`.
