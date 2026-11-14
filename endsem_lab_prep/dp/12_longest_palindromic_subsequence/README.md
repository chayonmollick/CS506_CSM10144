# 12. Longest Palindromic Subsequence

Source: Tutorial 9 Q12 ("Give an O(n^2) algorithm ... What is the answer for character?").

## Problem

A palindrome reads the same forwards and backwards. Given a string s, find the length of its
longest palindromic subsequence (characters need not be contiguous) and print one.

Build the answer with this rule (it makes the output unique): look at the two ends s[i], s[j]
(start with the whole string). If they are equal, both belong to the answer; move both ends
inward. Otherwise drop the left end if that keeps the best length (dp[i+1][j] ≥ dp[i][j−1]),
else drop the right end.

**Input**
- One line: the string s (lowercase letters, no spaces)

**Output**
- Line 1: the length
- Line 2: the palindromic subsequence

**Constraints**: 1 ≤ |s| ≤ 1000.

**Sample Input**
```
character
```

**Sample Output**
```
5
carac
```

## Idea

- Subproblem: dp[i][j] = length of the longest palindromic subsequence of s[i..j].
- Base cases: dp[i][i] = 1; dp[i][j] = 0 when i > j (empty range).
- Recurrence (i < j):
  - s[i] = s[j]: dp[i][j] = dp[i+1][j−1] + 2 (both ends can always be used together),
  - else: dp[i][j] = max(dp[i+1][j], dp[i][j−1]) (at least one end is not in the answer).
- Fill order: by interval length 2, 3, ..., n (a cell reads only shorter intervals) — the same
  "diagonal by diagonal" order as MATRIX-CHAIN-ORDER and OPTIMAL-BST.
- Reconstruction: walk from (0, n−1) with the rule in the statement, appending s[i] to the left
  half on every match; a single leftover i = j is the middle character; answer =
  left + middle + reverse(left).

## Pseudocode

```
function LPS-LENGTH(s, n):
    for i = 1 to n:
        dp[i][i] = 1
    for len = 2 to n:
        for i = 1 to n - len + 1:
            j = i + len - 1
            if s[i] == s[j]:
                dp[i][j] = dp[i + 1][j - 1] + 2     // dp of an empty range is 0
            else:
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])
    return dp

function PRINT-LPS(s, dp, n):
    left = "", mid = ""
    i = 1, j = n
    while i <= j:
        if i == j:
            mid = s[i]
            break
        if s[i] == s[j]:
            left = left + s[i]
            i = i + 1, j = j - 1
        else if dp[i + 1][j] >= dp[i][j - 1]:
            i = i + 1
        else:
            j = j - 1
    print left + mid + REVERSE(left)
```

## Complexity

O(n^2) time and O(n^2) space (the length alone needs only O(n) with two rows).

## Edge cases / traps

- Length-2 interval with equal ends reads dp[i+1][i], an empty range: it must be 0 (initialise the
  whole table to 0).
- Even-length answer (e.g. `bbbab` → `bbbb`) has no middle character; odd length has one.
- LPS length = LCS(s, reverse(s)) length — correct for the LENGTH, but an arbitrary LCS traceback
  of s and reverse(s) is not always a palindrome, so do not print it blindly.
- Substring vs subsequence (Q12 last part): the longest palindromic SUBSTRING must be contiguous,
  so the recurrence becomes a boolean pal[i][j] = (s[i] = s[j]) and pal[i+1][j−1]; no "drop one
  end" case.

## Variants they might ask

- Minimum insertions (or deletions) to make s a palindrome: n − dp[0][n−1].
- Longest palindromic substring: pal[i][j] as above, track the longest true cell (or expand
  around each centre in O(n^2) with O(1) space).
- Count palindromic subsequences: cnt[i][j] = cnt[i+1][j] + cnt[i][j−1] − cnt[i+1][j−1], plus
  cnt[i+1][j−1] + 1 when s[i] = s[j].
