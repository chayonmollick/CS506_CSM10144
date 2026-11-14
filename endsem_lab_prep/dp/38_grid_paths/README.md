# 38. Grid Paths (minimum path sum + number of paths with obstacles)

Source: exam-style variant combining [LeetCode 64 Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)
and [LeetCode 63 Unique Paths II](https://leetcode.com/problems/unique-paths-ii/); warm-up for Tutorial 9 Q25 (blocked cells).

## Problem

A grid has `n` rows and `m` columns. Cell `(i, j)` holds a non-negative cost, or `-1` if it is blocked. A robot starts
at the top-left cell `(1, 1)` and must reach the bottom-right cell `(n, m)`, moving only **right** or **down** and
never entering a blocked cell.

(a) Print the minimum possible sum of the costs of the cells on the path (both end cells included), or `-1` if no
path exists.
(b) Print the number of different paths, modulo 1000000007 (0 if none).

**Input**
Line 1: two integers `n` and `m`.
Next `n` lines: `m` integers each, the grid.

**Output**
Line 1: the answer to (a). Line 2: the answer to (b).

**Constraints**
1 ≤ n, m ≤ 1000; each cell is −1 or 0 ≤ a[i][j] ≤ 10^4 (start or end may be blocked)

**Sample Input**
```
3 3
1 3 1
1 -1 1
4 2 1
```

**Sample Output**
```
7
2
```

(Only two paths avoid the centre: along the top row then down (1+3+1+1+1 = 7) and down the left column then along
the bottom (1+1+4+2+1 = 9).)

## Idea

- Subproblems: `best[i][j]` = minimum sum of a path from `(1, 1)` to `(i, j)`; `ways[i][j]` = number of such paths.
- The last move into `(i, j)` came from above `(i−1, j)` or from the left `(i, j−1)`:
  - `best[i][j] = a[i][j] + min(best[i−1][j], best[i][j−1])`
  - `ways[i][j] = ways[i−1][j] + ways[i][j−1]`
- Base cases: `best[1][1] = a[1][1]`, `ways[1][1] = 1` (if not blocked). Blocked cell: `best = ∞`, `ways = 0`.
  Neighbours outside the grid count as `∞` / `0`.
- Fill order: row by row, left to right (both "from" cells are already done).
- Reconstruction of the min path: from `(n, m)` step back to whichever neighbour gave the `min`.

## Pseudocode

```
function GRID_PATHS(a[1..n][1..m]):
    for i = 1 to n:
        for j = 1 to m:
            best[i][j] = INF, ways[i][j] = 0
            if a[i][j] == -1: continue                 // blocked
            if i == 1 and j == 1:
                best[1][1] = a[1][1], ways[1][1] = 1
                continue
            from = INF, w = 0
            if i > 1: from = min(from, best[i-1][j]); w = w + ways[i-1][j]
            if j > 1: from = min(from, best[i][j-1]); w = w + ways[i][j-1]
            if from < INF: best[i][j] = from + a[i][j]
            ways[i][j] = w mod M
    return (best[n][m], ways[n][m])

Main:
    read n, m, grid
    (b, w) = GRID_PATHS(grid)
    print (b == INF ? -1 : b)
    print w
```

## Complexity

O(n · m) time and space (O(m) space with one row per table, since row `i` only needs row `i − 1`).

## Edge cases / traps

- Start or end blocked → `-1` and `0` (handle before/inside the loop; do not set `ways[1][1] = 1` blindly).
- Never do `INF + a[i][j]` — check `from < INF` first.
- Without obstacles the count is C(n+m−2, n−1), astronomically large: take `% M` at every cell.
- A 1 × m or n × 1 grid has exactly one path (if nothing is blocked).
- Min path sum is at most (n + m − 1) · 10^4 ≈ 2 × 10^7, fits `int`, but `long long` with `INF` is simpler.

## Variants they might ask

- **Max path sum / collect max coins**: replace `min` with `max` and `INF` with `−INF`.
- **Also allow diagonal moves**: add the neighbour `(i−1, j−1)` to both recurrences.
- **Print the min path** as a string of `R`/`D`: walk back from `(n, m)` choosing the neighbour with the smaller
  `best`, collect the moves, reverse.
- **Two robots / collect twice** → see 39 (two carts, O(n^3) diagonal DP).
