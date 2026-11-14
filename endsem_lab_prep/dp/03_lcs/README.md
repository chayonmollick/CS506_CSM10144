# 03. Longest Common Subsequence (length + one LCS)

Source: DP slides, "Longest Common Subsequence" (LCS-LENGTH, PRINT-LCS, CLRS example
X = ABCBDAB, Y = BDCABA); Tutorial 9 Q3.

## Problem

Given two strings X and Y, find the length of their longest common subsequence (characters in
the same order, not necessarily contiguous) and print one LCS.

To make the answer unique, build it with the standard traceback from cell (m, n): if
X[i] = Y[j] take the character and go diagonally; otherwise go up (i − 1) when
c[i−1][j] ≥ c[i][j−1], else go left (j − 1).

**Input**
- Line 1: string X
- Line 2: string Y

**Output**
- Line 1: the LCS length
- Line 2: the LCS (an empty line if the length is 0)

**Constraints**: 1 ≤ |X|, |Y| ≤ 1000, uppercase letters, no spaces.

**Sample Input**
```
ABCBDAB
BDCABA
```

**Sample Output**
```
4
BCBA
```

## Idea

- Subproblem: c[i][j] = LCS length of the prefixes X[1..i] and Y[1..j].
- Recurrence: c[i][0] = c[0][j] = 0;
  if X[i] = Y[j]: c[i][j] = c[i−1][j−1] + 1;
  else c[i][j] = max(c[i−1][j], c[i][j−1]).
- Fill order: row by row, left to right (each cell reads up, left and up-left).
- Reconstruction: PRINT-LCS follows the arrows back from (m, n); every diagonal step is one LCS
  character. No b table is needed: re-test the same three cases using c.

## Pseudocode

```
function LCS-LENGTH(X, Y, m, n):
    for i = 0 to m: c[i][0] = 0
    for j = 0 to n: c[0][j] = 0
    for i = 1 to m:
        for j = 1 to n:
            if X[i] == Y[j]:
                c[i][j] = c[i-1][j-1] + 1;  b[i][j] = "diag"
            else if c[i-1][j] >= c[i][j-1]:
                c[i][j] = c[i-1][j];        b[i][j] = "up"
            else:
                c[i][j] = c[i][j-1];        b[i][j] = "left"
    return c, b

function PRINT-LCS(b, X, i, j):
    if i == 0 or j == 0:
        return
    if b[i][j] == "diag":
        PRINT-LCS(b, X, i-1, j-1)
        print X[i]
    else if b[i][j] == "up":
        PRINT-LCS(b, X, i-1, j)
    else:
        PRINT-LCS(b, X, i, j-1)
```

(sol.cpp does the same walk with a while-loop, collecting characters backwards and then
reversing, so long strings cannot overflow the recursion stack.)

## Complexity

Θ(mn) time and space; traceback O(m + n). Length only: two rows, O(min(m, n)) space
(Tutorial Q3) — but then the LCS itself cannot be recovered without the full table
(or Hirschberg's divide and conquer).

## Edge cases / traps

- No common character: length 0, print an empty line.
- Strings are 0-indexed in C++: compare X[i−1] with Y[j−1] while the table is 1-indexed.
- A different tie rule (left before up) gives a different but equally valid LCS (BDAB instead
  of BCBA on the sample). If the statement fixes the rule, follow it exactly.
- Use `(int)X.size()` to avoid signed/unsigned warnings.

## Variants they might ask

- Print all/lexicographically smallest LCS: much harder; usually not asked. For the
  lexicographically smallest, compute suffix LCS lengths and pick the smallest next character greedily.
- Shortest common supersequence: length m + n − LCS; build it by walking the same table and
  printing non-matched characters too.
- Minimum deletions (+ insertions) to turn X into Y: m − LCS deletions, n − LCS insertions.
- Longest common substring (contiguous): see dp/15 — reset to 0 on a mismatch.
