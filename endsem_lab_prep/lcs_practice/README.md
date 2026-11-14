# LCS practice: 7 problems with a checker

Write each solution in your own file, then run:

```bash
cd sem1/CS506_DSA/labs/endsem_lab_prep/lcs_practice
./check.sh p3 my_p3.cpp        # builds as C++11 with warnings on and runs every test in p3_*/tests
```

The reference solutions are in `solutions/`. Don't open them until you've passed the problem or
are truly stuck. Each one was checked against a brute force on 400 random inputs.

Every problem is the LCS table plus one small change. The table code is the same each time:

```cpp
vector<vector<int> > c(m + 1, vector<int>(n + 1, 0));       // row 0 and column 0 = 0
for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
        if (X[i - 1] == Y[j - 1]) c[i][j] = c[i - 1][j - 1] + 1;   // strings are 0-indexed
        else c[i][j] = max(c[i - 1][j], c[i][j - 1]);
```

| # | Problem | The change from plain LCS | Time |
|---|---|---|---|
| P1 | Print the whole table | only the output | 5 min |
| P2 | One LCS with ties going **left**, plus positions | the traceback rule | 10 min |
| P3 | Fewest deletions + insertions to turn X into Y | m − L and n − L | 3 min |
| P4 | Longest palindromic subsequence, fewest insertions | Y = reverse(X) | 5 min |
| P5 | Longest repeating subsequence | a match also needs i ≠ j | 10 min |
| P6 | LCS of three strings | 3-D table | 10 min |
| P7 | LCS length of two 30 000-character strings | two rows instead of the table | 10 min |

If you only have 20 minutes, do **P2, P5, P7** in that order. They cover the traceback, a
changed recurrence, and memory.

---

## P1. Print the LCS table
**Input:** string X on line 1, string Y on line 2 (1 ≤ |X|, |Y| ≤ 100, no spaces).
**Output:** the table c[0..m][0..n], one row per line (row i = prefix X[1..i]), numbers separated
by one space. Then the LCS length on its own line.

```
Input            Output
ABCBDAB          0 0 0 0 0 0 0
BDCABA           0 0 0 0 1 1 1
                 0 1 1 1 1 2 2
                 0 1 1 2 2 2 2
                 0 1 1 2 2 3 3
                 0 1 2 2 2 3 3
                 0 1 2 2 3 3 4
                 0 1 2 2 3 4 4
                 4
```

## P2. LCS with ties going left, and where it came from
Same input as P1, |X|, |Y| ≤ 1000. Walk back from (m, n):
- if X[i] = Y[j], take it and go diagonally;
- else go **left** (j − 1) when c[i][j−1] ≥ c[i−1][j], otherwise go up (i − 1).

**Output:** line 1 the length, line 2 the LCS. Line 3: the 1-indexed positions in X of the LCS's
characters, in increasing order. Line 4: the same for Y. If the LCS is empty, print only `0` and `-`.

```
Input            Output
ABCBDAB          4
BDCABA           BDAB
                 4 5 6 7
                 1 2 4 5
```
(With ties going **up**, as in dp/03 and Mock 3, the same input gives BCBA.)

## P3. Turn X into Y with deletions and insertions only
Same input, |X|, |Y| ≤ 1000. **Output:** line 1 the fewest deletions, line 2 the fewest insertions.

```
Input            Output
heap             2
pea              1
```
(Delete h and p → ea; insert p at the front → pea.)

## P4. Longest palindromic subsequence
**Input:** one string s, 1 ≤ |s| ≤ 1000. **Output:** line 1 the length of the longest palindromic
subsequence, line 2 the fewest characters to insert (anywhere) to make s a palindrome.

```
Input            Output
BBABCBCAB        7
                 2
```
(BABCBAB is a longest palindromic subsequence.)

## P5. Longest repeating subsequence
**Input:** one string s, 1 ≤ |s| ≤ 1000. Find the longest string that occurs **twice** as a
subsequence of s, where the two occurrences never use the same position for the same character
(they may share positions otherwise).
**Output:** line 1 the length. Line 2 the string, found by the LCS(s, s) walk-back with ties
going **up**; print `-` if the length is 0.

```
Input            Output
AABEBCDD         3
                 ABD
```
(A at 1 and 2, B at 3 and 5, D at 7 and 8.)

## P6. LCS of three strings
**Input:** three strings on three lines, each 1 ≤ length ≤ 100. **Output:** the length of their
longest common subsequence.

```
Input            Output
geeks            5
geeksfor
geeksforgeeks
```

## P7. Very long strings
Same input as P1, but 1 ≤ |X|, |Y| ≤ 30 000. Memory limit 256 MB, time limit 10 s.
**Output:** the LCS length only.

A full `int` table would be 30 001² × 4 bytes ≈ 3.6 GB. Row i needs only row i − 1.

```
Input            Output
ABCBDAB          4
BDCABA
```

---

## Hints (read only if stuck)
- **P2:** collect characters and positions while walking back, then `reverse` all three.
- **P3:** keep the LCS and change everything else.
- **P4:** a palindromic subsequence of s is a common subsequence of s and reverse(s). Every
  character not in it needs one inserted partner.
- **P5:** run LCS of s with itself, but a match must have i ≠ j, otherwise each character
  matches itself and the answer is always n.
- **P6:** c[i][j][k] = c[i−1][j−1][k−1] + 1 if all three characters match, otherwise
  the max of the three tables you get by dropping one character.
- **P7:** `vector<int> prev(n+1, 0), cur(n+1, 0)`; fill `cur` from `prev`, then `swap(prev, cur)`.
  The answer ends up in `prev[n]`.
