# Mock 3 — solution

Code: [`a/sol.cpp`](a/sol.cpp), [`b/sol.cpp`](b/sol.cpp). Tests: `../../test.sh mock_papers/mock3_dp_strings`.

## Common setup
- **Subproblem:** c[i][j] = LCS length of the prefixes X[1..i] and Y[1..j].
- **Recurrence:**
  - c[i][j] = 0 if i = 0 or j = 0;
  - c[i][j] = c[i−1][j−1] + 1 if X[i] = Y[j];
  - c[i][j] = max(c[i−1][j], c[i][j−1]) otherwise.
- **Order:** row by row, i = 1..m, and in each row j = 1..n. Every entry reads only the cells above, to the left, and up-left.
```
function LCS-LENGTH(X, Y):
    m = |X|, n = |Y|
    for i = 0 to m: c[i][0] = 0
    for j = 0 to n: c[0][j] = 0
    for i = 1 to m:
        for j = 1 to n:
            if X[i] == Y[j]: c[i][j] = c[i-1][j-1] + 1
            else: c[i][j] = max(c[i-1][j], c[i][j-1])
    return c
```
Time and space: Θ(mn).

## (a) Reconstruction (PRINT-LCS without the b table)
```
function PRINT-LCS(c, X, Y, i, j):
    if i == 0 or j == 0: return
    if X[i] == Y[j]:
        PRINT-LCS(c, X, Y, i-1, j-1); print X[i]
    else if c[i-1][j] >= c[i][j-1]:
        PRINT-LCS(c, X, Y, i-1, j)
    else:
        PRINT-LCS(c, X, Y, i, j-1)
```
The code walks back iteratively and reverses the string, which avoids recursion 2000 deep.

## (b) Shortest common supersequence
- **Length:** |SCS| = m + n − LCS. The characters of an LCS are shared, so they are written once; every other character of X and Y is written once.
- **Reconstruction:** walk back exactly as in (a), but also output the characters the LCS skips:
```
while i > 0 and j > 0:
    if X[i] == Y[j]:              out X[i]; i--; j--
    else if c[i-1][j] >= c[i][j-1]: out X[i]; i--
    else:                         out Y[j]; j--
while i > 0: out X[i]; i--
while j > 0: out Y[j]; j--
print reverse(out)
```

**Variants (same table):**
- Minimum insertions plus deletions to turn X into Y: (m − LCS) + (n − LCS).
- Longest palindromic subsequence: the LCS of X and reverse(X).
- Edit distance: a different recurrence (substitution costs 1).
- Print all LCSs: branch on ties, but the count can be exponential.
