# Mock 4 — solution

Code: [`a/sol.cpp`](a/sol.cpp), [`b/sol.cpp`](b/sol.cpp). Tests: `../../test.sh mock_papers/mock4_dp_vs_heap`.

## (a) DP, computed from the end
- **Subproblem:** f[i][j] = cheapest cost from (i,j) to (R,C), both cells included.
- **Recurrence:**
  - f[R][C] = g[R][C];
  - f[i][j] = g[i][j] + min(f[i+1][j], f[i][j+1]), using only the moves that stay inside the grid.
- **Order:** i from R down to 1; in each row, j from C down to 1.
- **Reconstruction:** start at (1,1). Take `D` whenever f[i+1][j] = f[i][j] − g[i][j] (Down still lies on a cheapest path), otherwise take `R`. Choosing `D` first at every step gives the alphabetically smallest cheapest path.
```
function MIN-PATH(g, R, C):
    for i = R downto 1:
        for j = C downto 1:
            if i == R and j == C: f[i][j] = g[i][j]
            else: f[i][j] = g[i][j] + min(f[i+1][j] if i < R, f[i][j+1] if j < C)
    i = 1, j = 1, path = ""
    while (i, j) != (R, C):
        if i < R and f[i+1][j] == f[i][j] - g[i][j]: path += 'D'; i++
        else: path += 'R'; j++
    return f[1][1], path
```
**Why DP from the end:** when the DP runs from the start, the natural walk-back runs from (R,C) to (1,1). That walk-back cannot pick the alphabetically smallest path, because the first letters are decided last.

## (b) Dijkstra on the cells
With up and left moves, paths can turn back, so no cell order makes every predecessor come
first: the DP recurrence becomes cyclic. All costs are ≥ 0, so Dijkstra works. Each cell is a
vertex, and entering cell v costs g[v].
```
function DIJKSTRA-GRID(g, R, C):
    dist[all] = INF; dist[(1,1)] = g[1][1]
    Q = min-priority queue; INSERT(Q, (dist[(1,1)], (1,1)))
    while Q not empty:
        (d, u) = EXTRACT-MIN(Q)
        if d > dist[u]: continue                 // stale entry, skip (lazy deletion)
        for each neighbour v of u inside the grid:
            if d + g[v] < dist[v]:
                dist[v] = d + g[v]
                INSERT(Q, (dist[v], v))          // instead of DECREASE-KEY
    return dist[(R,C)]
```
Time: O(RC log RC). `std::priority_queue` has no decrease-key, so you push a new entry and skip the stale ones when they come out.

**Lesson:**
- DP needs an order in which the subproblems form a DAG.
- If moves can create cycles and all costs are ≥ 0, use Dijkstra.
- If costs can be negative, use Bellman–Ford. That is DP again, over the number of edges used: OPT(i, v).
