# 01. Rod Cutting (revenue + pieces)

Source: DP slides, "Rod Cutting" (BOTTOM-UP-CUT-ROD, the s[j] reconstruction slide); DP tutorial
"Coding" Q1–Q2 (EXTENDED-BOTTOM-UP-CUT-ROD, return the actual cuts).

## Problem

A steel rod of length n can be cut into pieces of integer length. A piece of length i sells for
p_i. Find the maximum revenue obtainable, and one way of cutting that achieves it.

If several cuttings give the maximum revenue, print the one whose first piece is as short as
possible; for the remaining rod apply the same rule again (this is exactly what the extended
bottom-up algorithm produces when it keeps the first best i).

**Input**
- Line 1: n
- Line 2: n integers p_1 ... p_n

**Output**
- Line 1: the maximum revenue
- Line 2: the piece lengths in the order they are cut off, space-separated

**Constraints**: 1 ≤ n ≤ 1000, 0 ≤ p_i ≤ 10^9 (use `long long`).

**Sample Input**
```
8
1 5 8 9 10 17 17 20
```

**Sample Output**
```
22
2 6
```

## Idea

- Subproblem: r[j] = best revenue for a rod of length j (j = 0..n).
- Recurrence: r[0] = 0; r[j] = max over 1 ≤ i ≤ j of (p_i + r[j − i]) — i is the first piece cut off.
- Fill order: j = 1, 2, ..., n (r[j] only reads shorter lengths).
- Reconstruction: store s[j] = the i that gave the max. Walk j = n, print s[j], set j = j − s[j],
  until j = 0. Pieces always sum to n.

## Pseudocode

```
function EXTENDED-BOTTOM-UP-CUT-ROD(p, n):
    r[0] = 0
    for j = 1 to n:
        q = -infinity
        for i = 1 to j:
            if p[i] + r[j - i] > q:      // strict: keep the smallest i on ties
                q = p[i] + r[j - i]
                s[j] = i
        r[j] = q
    return r, s

function PRINT-CUT-ROD-SOLUTION(p, n):
    (r, s) = EXTENDED-BOTTOM-UP-CUT-ROD(p, n)
    print r[n]
    j = n
    while j > 0:
        print s[j]
        j = j - s[j]
```

## Complexity

O(n^2) time, O(n) space. The naive recursion CUT-ROD makes 2^n calls.

## Edge cases / traps

- n = 1: answer is p_1, pieces "1".
- All prices 0: revenue 0; with the strict `>` and q starting below 0 the output is "1 1 ... 1".
  If q started at 0 with `>`, s[j] would stay 0 and the traceback would loop forever.
- Revenue can exceed 2^31 (n · 10^9): use `long long`.
- Greedy by density p_i / i is wrong (Tutorial 9 Q1(b)), e.g. p = (1, 20, 33, 36), n = 4:
  density picks 3 then 1 (33 + 1 = 34), but 2 + 2 gives 40.

## Variants they might ask

- Fixed cost c per cut (Tutorial Q1(c)): r[j] = max(p_j, max over i < j of p_i + r[j − i] − c).
  Treat i = j (no cut) separately.
- Memoized (top-down) version: MEMOIZED-CUT-ROD with r[] initialised to −1; same s[] trick.
- Minimum number of pieces among optimal cuts: keep a second array cnt[j] and break revenue
  ties by smaller cnt.
- Limit on pieces of each length (Tutorial Q1(d)): optimal substructure breaks — the state would
  need the remaining limits, so plain rod-cutting DP no longer applies.
