# 06. Sequence Alignment / Edit Distance (cost + alignment)

Source: DP slides, "Sequence Alignment" (ALIGNMENT(X, Y), FIND-ALIGNMENT, worked example
GATCGG vs GATTACA with δ = 2, α = 1); Tutorial 9 Q7 (SUNDAY → SATURDAY) and Q26.

## Problem

Align string X with string Y. A gap (a character of either string placed against `-`) costs δ.
Placing two different characters in the same column costs α; two equal characters cost 0.
Find the minimum total cost and print an optimal alignment.

Reconstruct with FIND-ALIGNMENT from cell (m, n), testing the options in this order:
(1) pair x_i with y_j, (2) x_i against a gap, (3) y_j against a gap — take the first option
whose cost matches the table value.

**Input**
- Line 1: string X
- Line 2: string Y
- Line 3: δ α

**Output**
- Line 1: the minimum alignment cost
- Line 2: X with `-` inserted at its gaps
- Line 3: Y with `-` inserted at its gaps (same length as line 2)

**Constraints**: 1 ≤ |X|, |Y| ≤ 1000, uppercase letters; 0 ≤ δ, α ≤ 1000.

**Sample Input**
```
GATCGG
GATTACA
2 1
```

**Sample Output**
```
5
GA-TCGG
GATTACA
```

## Idea

- Subproblem: A[i][j] = min cost to align X[1..i] with Y[1..j].
- The last column of an optimal alignment is (x_i, y_j), (x_i, −) or (−, y_j), so
  A[i][j] = min( α(x_i, y_j) + A[i−1][j−1], δ + A[i−1][j], δ + A[i][j−1] ),
  with α(a, a) = 0. Base cases: A[i][0] = i·δ, A[0][j] = j·δ.
- Fill order: row by row or column by column — each cell reads up, left and up-left.
- Reconstruction (FIND-ALIGNMENT): from (m, n) check which option produced A[i][j], emit that
  column, move to the cell it came from; when i or j reaches 0 the rest is gaps. Columns come
  out backwards, so reverse at the end.
- Edit distance is the special case δ = α = 1: a column (a, b) with a ≠ b is a substitution,
  (a, −) deletes a from X, (−, b) inserts b.

## Pseudocode

```
function ALIGNMENT(X, Y, m, n, delta, alpha):
    for i = 0 to m: A[i][0] = i * delta
    for j = 0 to n: A[0][j] = j * delta
    for i = 1 to m:
        for j = 1 to n:
            cost = 0 if X[i] == Y[j] else alpha
            A[i][j] = min(cost + A[i-1][j-1],
                          delta + A[i-1][j],
                          delta + A[i][j-1])
    return A[m][n]

function FIND-ALIGNMENT(i, j):
    if i == 0 and j == 0:
        return
    if i > 0 and j > 0 and A[i][j] == cost(X[i], Y[j]) + A[i-1][j-1]:
        FIND-ALIGNMENT(i-1, j-1);  output (X[i], Y[j])
    else if i > 0 and A[i][j] == delta + A[i-1][j]:
        FIND-ALIGNMENT(i-1, j);    output (X[i], -)
    else:
        FIND-ALIGNMENT(i, j-1);    output (-, Y[j])
```

## Complexity

Θ(mn) time and space; the traceback is O(m + n). Cost only: keep two rows → O(min(m, n))
space (Tutorial Q7(c), Q26). Hirschberg recovers the alignment in O(m + n) space.

## Edge cases / traps

- Identical strings: cost 0, both lines equal to the input.
- When α ≥ 2δ a mismatch is never better than two gaps; with δ = 1 and α "infinite" the cost is
  m + n − 2·LCS (test 5).
- The traceback must handle i = 0 or j = 0 (only one kind of move is possible); the
  `i > 0` / `j > 0` guards do this.
- Compare the traceback against the SAME cost expression used to fill the table, or ties will
  silently pick an option that is not optimal.
- Ties between options produce different (equally cheap) alignments — follow the stated order.

## Variants they might ask

- Plain edit distance (Levenshtein): read no costs, set δ = α = 1 (Tutorial Q7(b):
  SUNDAY → SATURDAY = 3, test 2).
- Print the edit operations instead of the alignment: for each column print `MATCH a`,
  `SUB a b`, `DEL a` (a, −) or `INS b` (−, b).
- Per-pair mismatch costs α_ab (e.g. vowel–vowel 1, vowel–consonant 3): replace the line
  `cost = ...` by a lookup in a 26×26 table read from input.
- Different insert and delete costs: use δ_del in the (x_i, −) case and δ_ins in the (−, y_j)
  case (and in the base row/column).
