# 10. Shortest Path DP (Bellman–Ford) with Negative Edges

Source: DP slides, "Shortest Paths" (SHORTEST-PATH(G, t), PRINT-PATH, "When it fails · negative
cycles"); the sample is the slides' worked example with s = 1, a = 2, c = 3, b = 4, t = 5.

## Problem

A directed graph has n vertices (1..n) and m weighted edges; weights may be negative. Find the
cheapest path from s to t and print it.

- If the graph contains a negative cycle from which t can be reached, print `NEGATIVE CYCLE`
  (even if s itself cannot reach that cycle).
- Otherwise, if t cannot be reached from s, print `NO PATH`.

**Input**
- Line 1: n m
- Next m lines: u v c — a directed edge u → v with cost c
- Last line: s t

**Output**
- Line 1: the minimum cost (or `NEGATIVE CYCLE` / `NO PATH` and nothing else)
- Line 2: the vertices of the path from s to t, space-separated (just `s` when s = t)

**Constraints**: 1 ≤ n ≤ 500, 0 ≤ m ≤ 5000, |c| ≤ 10^6, 1 ≤ s, t ≤ n. Parallel edges and
self-loops may appear.

**Sample Input**
```
5 7
1 2 2
1 3 6
2 4 3
2 5 9
3 4 -4
3 5 3
4 5 1
1 5
```

**Sample Output**
```
3
1 3 4 5
```

(s → c → b → t = 6 − 4 + 1 = 3 beats s → a → b → t = 2 + 3 + 1 = 6.)

## Idea

- Subproblem: OPT(i, v) = cost of the cheapest v → t path that uses at most i edges.
- Recurrence: OPT(0, t) = 0, OPT(0, v) = ∞ for v ≠ t;
  OPT(i, v) = min( OPT(i − 1, v), min over edges (v, w) of c(v, w) + OPT(i − 1, w) ).
- Without negative cycles a shortest path is simple, so it has ≤ n − 1 edges: answer OPT(n − 1, s).
- Fill order: rounds i = 1..n − 1; inside a round any vertex/edge order. We keep ONE array M[v]
  and update it in place (still correct: every value is the cost of a real path and is at most
  OPT(i, v) after round i).
- Reconstruction: first[v] = the w that last improved M[v]. PRINT-PATH walks s, first[s], ... t.
- Negative cycle: run one more round; if any M[v] still improves, some path to t needs ≥ n edges,
  so it repeats a vertex on a negative cycle.

## Pseudocode

```
function SHORTEST-PATH(G, t):
    for each vertex v:
        M[v] = infinity
    M[t] = 0
    for i = 1 to n - 1:                       // one more edge allowed per round
        for each edge (v, w) with cost c:
            if M[w] != infinity and c + M[w] < M[v]:
                M[v] = c + M[w]
                first[v] = w
    for each edge (v, w) with cost c:         // round n: detection
        if M[w] != infinity and c + M[w] < M[v]:
            return "NEGATIVE CYCLE"
    return M, first

function PRINT-PATH(s, t):
    v = s
    while v != t:
        output v
        v = first[v]
    output t
```

## Complexity

O(n·m) time, O(n + m) space (O(n^2) if you keep the full OPT(i, v) table as on the slides).

## Edge cases / traps

- Guard `M[w] != INF` before adding c, otherwise INF + (negative c) looks like a real path (and
  INF + positive c can overflow). Use `long long`.
- s = t: cost 0, path is just `s` — unless a negative cycle reaches t.
- A negative cycle that cannot reach t does not matter: its vertices keep M = ∞.
- Check the negative cycle BEFORE printing `NO PATH` (the statement gives it priority).
- Dijkstra is wrong with negative edges; that is why this DP is asked.

## Variants they might ask

- Single source (distances FROM s to every vertex): standard Bellman–Ford — dist[s] = 0, relax
  `dist[u] + c < dist[v]`, keep pred[v] = u, print the path by walking pred back from t and
  reversing.
- Report only a negative cycle reachable FROM s: run the source version and check round n.
- Early exit: stop when a whole round changes nothing (same answer, often much faster).
- Exactly / at most k edges: keep two arrays (prev, cur) and run exactly k rounds without
  in-place updates, so round i really means "≤ i edges".
