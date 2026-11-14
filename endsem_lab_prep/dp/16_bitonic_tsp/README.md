# 16. Bitonic Euclidean Travelling-Salesman Tour

Source: Tutorial 9 Q9 (CLRS Problem 15-3); the sample is the 7-point example of CLRS Figure 15.11.

## Problem

n points in the plane have distinct x-coordinates. A bitonic tour starts at the leftmost point,
goes strictly left to right to the rightmost point, then strictly right to left back to the
start, visiting every point exactly once. Print the length of the shortest bitonic tour
(Euclidean distances).

**Input**
- Line 1: n
- Next n lines: x_i y_i (integers; the points are NOT necessarily given in x order)

**Output**
- One line: the length of the shortest bitonic tour with exactly 2 decimals

**Constraints**: 2 ≤ n ≤ 1000, |x_i|, |y_i| ≤ 10^6, all x_i distinct.

**Sample Input**
```
7
0 6
1 0
2 3
5 4
6 1
7 5
8 2
```

**Sample Output**
```
25.58
```

## Idea

- Sort by x: p_1, ..., p_n.
- Subproblem (i < j): b[i][j] = minimum total length of two disjoint paths, one from p_1 to p_i
  and one from p_1 to p_j, that together visit every point p_1..p_j exactly once. Think of it as
  the bitonic tour of p_1..p_j "opened" at p_i–p_j.
- Recurrence:
  - b[1][2] = d(1, 2).
  - i < j − 1: p_{j−1} must be the predecessor of p_j on the path ending at p_j (the other path
    ends at p_i < p_{j−1}), so b[i][j] = b[i][j−1] + d(j−1, j).
  - i = j − 1: the predecessor of p_j is some p_k with k < j − 1, so
    b[j−1][j] = min over 1 ≤ k ≤ j − 2 of b[k][j−1] + d(k, j).
- Answer: b[n−1][n] + d(n−1, n) (join the two ends; p_n is adjacent to p_{n−1} in an optimal
  tour).
- Fill order: j = 3..n; within j, any order (row j only reads column j − 1).

## Pseudocode

```
function BITONIC-TSP(p, n):
    sort p by x-coordinate
    b[1][2] = DIST(p1, p2)
    for j = 3 to n:
        for i = 1 to j - 2:
            b[i][j] = b[i][j - 1] + DIST(p[j - 1], p[j])
        b[j - 1][j] = infinity
        for k = 1 to j - 2:
            q = b[k][j - 1] + DIST(p[k], p[j])
            if q < b[j - 1][j]:
                b[j - 1][j] = q
                r[j - 1][j] = k            // only needed to print the tour
    return b[n - 1][n] + DIST(p[n - 1], p[n])
```

## Complexity

O(n^2) time (the k-loop runs only for the n cells b[j−1][j]), O(n^2) space.

## Edge cases / traps

- Sort the points first — the input order is arbitrary.
- n = 2: the tour goes there and back, answer 2·d(1, 2).
- Collinear points: still fine (answer = 2 × (x_n − x_1) when all lie on one horizontal line).
- Coordinates up to 10^6: dx² ≈ 4·10^12 overflows `int`; compute in `double` (or `long long`).
- `printf` after `ios::sync_with_stdio(false)` mixes buffers — use `fixed << setprecision(2)`.

## Variants they might ask

- Print the tour: store r[j−1][j] = best k. Recover the two paths backwards: start with
  (i, j) = (n − 1, n); if i < j − 1, p_{j−1} precedes p_j on j's path, set j = j − 1; if i = j − 1,
  p_k = r[i][j] precedes p_j, then continue with (k, j − 1) (the two path roles swap). Print one
  path left to right and the other right to left.
- Top-down version: memoise b(i, j) with the same three cases (base, i < j − 1, i = j − 1); same
  O(n^2) because each b(j − 1, j) loops over k once.
- Manhattan distance instead of Euclidean: only DIST changes.
