# 15. Longest Common Substring (contiguous) — contrast with LCS

Source: exam-style variant of the slides' "Longest Common Subsequence" (same table shape, but the
characters must be consecutive). Sample uses the slides' LCS strings ABCBDAB / BDCABA.

## Problem

Given two strings X and Y, find the length of the longest string that appears as a contiguous
block (substring) in both, and print it. If several common substrings have the maximum length,
print the one that occurs first in X (smallest starting position in X).

**Input**
- Line 1: X
- Line 2: Y
(letters only, no spaces)

**Output**
- Line 1: the length
- Line 2: the substring (an empty line if the length is 0)

**Constraints**: 1 ≤ |X|, |Y| ≤ 1000.

**Sample Input**
```
ABCBDAB
BDCABA
```

**Sample Output**
```
2
AB
```

(The LCS of these strings, problem 03, has length 4 — BCBA — but only 2 consecutive characters
match anywhere: AB, BD.)

## Idea

- Subproblem: dp[i][j] = length of the longest common SUFFIX of X[1..i] and Y[1..j] (a common
  substring that ends exactly at X[i] and Y[j]).
- Recurrence: dp[i][0] = dp[0][j] = 0;
  dp[i][j] = dp[i−1][j−1] + 1 if X[i] = Y[j], else 0.
- Answer: the maximum cell anywhere in the table (NOT dp[m][n]); remember where it ends in X.
- Fill order: row by row, left to right (only the diagonal neighbour is read).
- Reconstruction: no arrows needed — the answer is X[endX − best + 1 .. endX].

LCS vs longest common substring:

| | LCS (03) | Longest common substring (15) |
|---|---|---|
| mismatch X[i] ≠ Y[j] | max(c[i−1][j], c[i][j−1]) | 0 (run is broken) |
| answer | c[m][n] | max over all cells |
| traceback | follow arrows from (m, n) | substring ending at the best cell |

## Pseudocode

```
function LONGEST-COMMON-SUBSTRING(X, Y, m, n):
    for i = 0 to m: dp[i][0] = 0
    for j = 0 to n: dp[0][j] = 0
    best = 0, endX = 0
    for i = 1 to m:
        for j = 1 to n:
            if X[i] == Y[j]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = 0
            if dp[i][j] > best:           // strict: first occurrence in X wins
                best = dp[i][j]
                endX = i
    print best
    print X[endX - best + 1 .. endX]
```

## Complexity

O(m·n) time, O(m·n) space; only the previous row is read, so two rows (or one row updated from
right to left) give O(n) space.

## Edge cases / traps

- No common character: length 0, print an empty line (`substr(0, 0)` is fine).
- Answer is the table maximum, not dp[m][n] (dp[m][n] is 0 whenever the last characters differ).
- Using `>=` instead of `>` returns the LAST occurrence in X — the tie-break flips.
- Off-by-one in substr: start = endX − best (0-based) when endX is 1-based.

## Variants they might ask

- Longest repeated substring of one string: run the same DP on X with itself and only use cells
  with i < j (skip the main diagonal); for non-overlapping repeats also require dp[i][j] ≤ j − i.
- Longest palindromic substring: run it on X and reverse(X) and check the positions line up, or use
  the pal[i][j] table (see 12).
- Only the length with O(n) memory: keep `prev` and `cur` rows, reset cur[j] = 0 on mismatch.
- Huge strings (hashing chapter): binary search on the length L; for a given L put the rolling
  hashes of all length-L substrings of X in an `unordered_set` and look up those of Y —
  O((m + n) log min(m, n)) expected.
