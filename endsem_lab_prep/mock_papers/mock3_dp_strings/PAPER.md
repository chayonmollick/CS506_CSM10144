# CS 506 — End-semester Lab Exam, Mock 3 (Dynamic Programming on strings)

Time allotted: 2 hours | Max. marks 30 | C/C++ | STL allowed

**Instructions**
1. For parts (a) and (b), write the pseudocode/logic first. For each DP, state:
   - (i) what a subproblem means;
   - (ii) the recurrence with its base cases;
   - (iii) the order in which the table is filled;
   - (iv) how the answer is reconstructed.
2. One source file per part. Print only what is asked.

## Common setup (applies to both parts) [5 marks]
Implement `LCS-LENGTH(X, Y)` that fills the table c[0..m][0..n], where c[i][j] is the length
of a longest common subsequence of X[1..i] and Y[1..j]. Both parts reuse this table.
X and Y are strings of uppercase letters, 1 ≤ |X|, |Y| ≤ 1000, each given on its own line.

## (a) Longest common subsequence [10 marks]
Print the LCS length on the first line. On the second line print one LCS, found by walking back
from c[m][n]:
- if X[i] = Y[j], take the character and move diagonally;
- otherwise move **up** (i−1) when c[i−1][j] ≥ c[i][j−1], else move **left** (j−1).

If the LCS is empty, print `-` on the second line.

Sample Input
```
ABCBDAB
BDCABA
```
Sample Output
```
4
BCBA
```

## (b) Shortest common supersequence [15 marks]
A supersequence of X and Y is a string that contains both X and Y as subsequences. Print the
length of a shortest one, and on the next line the one you get by walking back with the same
rule as (a), outputting every character you step over:
- diagonal: the shared character, once;
- up: X[i];
- left: Y[j];
- when one string runs out: the rest of the other.

Sample Input
```
ABCBDAB
BDCABA
```
Sample Output
```
9
ABDCABDAB
```
