# 09. Segmented Least Squares

Source: DP slides, "Segmented Least Squares" (SEGMENTED-LEAST-SQUARES, FIND-SEGMENTS). The slides'
worked example (7 points, C = 2) is re-created here with our own points, since the slide gives
them only as a picture.

## Problem

You are given n points (x_1, y_1), ..., (x_n, y_n) with x_1 < x_2 < ... < x_n and a penalty C.
Partition the points into consecutive segments (each segment is a run j..i of points) and fit one
least-squares line to each segment. The cost of a partition is

  (sum of the squared errors of all segments) + C × (number of segments).

The squared error of segment j..i is sum over k = j..i of (y_k − a·x_k − b)^2 for the best line
y = a·x + b through those points (a single point has error 0). Find the minimum cost and one
optimal partition. If several partitions are optimal, the last segment should start as early as
possible; apply the same rule to the remaining points.

**Input**
- Line 1: n C (C is a real number)
- Next n lines: x_i y_i (integers, x strictly increasing)

**Output**
- Line 1: the minimum cost with exactly 2 decimals
- Line 2: k, the number of segments
- Next k lines: `j i` — first and last point (1-based) of each segment, left to right

**Constraints**: 1 ≤ n ≤ 300, 0 ≤ C ≤ 10^6, |x_i|, |y_i| ≤ 10^4.

**Sample Input**
```
7 2
1 1
2 3
3 4
4 9
5 8
6 6
7 5
```

**Sample Output**
```
4.37
2
1 3
4 7
```

(Segment 1..3 has error 0.17, segment 4..7 error 0.20, plus 2 × C = 4. One line through all
seven points would cost 29.57 + 2 = 31.57.)

## Idea

- Precompute e[j][i] = least-squares error of points j..i with the closed form
  a = (N·Σxy − Σx·Σy) / (N·Σx² − (Σx)²), b = (Σy − a·Σx) / N, N = i − j + 1.
- Subproblem: M[i] = minimum cost for points 1..i.
- Recurrence: M[0] = 0; M[i] = min over 1 ≤ j ≤ i of (e[j][i] + C + M[j − 1]) — j is where the
  LAST segment starts (multi-way choice, like rod cutting).
- Fill order: all e first (any order), then M[1], M[2], ..., M[n].
- Reconstruction: first[i] = the j that gave the min. From i = n: segment first[i]..i, then
  i = first[i] − 1, until i = 0. Segments come out right-to-left, so reverse before printing.

## Pseudocode

```
function SEGMENTED-LEAST-SQUARES(n, C):
    for j = 1 to n:                     // stage 1: errors
        for i = j to n:
            e[j][i] = error of the best line through points j..i
    M[0] = 0
    for i = 1 to n:                     // stage 2: left to right
        M[i] = infinity
        for j = 1 to i:
            t = e[j][i] + C + M[j - 1]
            if t < M[i] - EPS:          // keep the smallest j on ties
                M[i] = t
                first[i] = j
    return M[n]

function FIND-SEGMENTS(i):
    if i == 0:
        return
    j = first[i]
    FIND-SEGMENTS(j - 1)
    output segment j..i
```

## Complexity

e[j][i] computed directly: O(n^3) time (O(n^2) with running sums and the expanded error formula),
O(n^2) space. Stage 2 is O(n^2).

## Edge cases / traps

- Single point: N·Σx² − (Σx)² = 0, so do not divide; set a = 0, b = y_j, error 0.
- Floating ties: compare with an epsilon (`t < M[i] - 1e-9`), otherwise round-off picks a
  different segmentation than the expected output.
- C = 0: every segment of ≤ 2 points has error 0, so many partitions tie at cost 0.
- Huge C: always one segment. Tiny C: many short segments.
- Mixing `printf` with `cout` after `sync_with_stdio(false)` scrambles output; use
  `cout << fixed << setprecision(2)`.

## Variants they might ask

- Only the cost: drop first[] and the traceback.
- At most K segments: M[k][i] = min over j of e[j][i] + M[k − 1][j − 1] (C no longer needed);
  O(K·n^2).
- Different error measure (absolute error, max error): only stage 1 changes; stage 2 is identical.
- Print each segment's line: recompute a, b for every printed segment j..i.
