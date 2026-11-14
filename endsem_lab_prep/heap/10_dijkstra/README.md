# 10. Dijkstra's shortest paths with a priority queue

Source: Heap Sort slide 28 (priority-queue applications: Dijkstra) and the Fibonacci Heaps slides
(O(E log V) with a binary heap vs O(E + V log V) with a Fibonacci heap). Exam-style variant.

## Problem

Given a **directed** graph with N vertices (1..N), M edges with **non-negative** weights and a
source S, print the shortest distance from S to every vertex. Print `-1` for vertices that S
cannot reach.

**Input.** Line 1: N, M, S (1 ≤ N ≤ 10^5, 0 ≤ M ≤ 2·10^5, 1 ≤ S ≤ N). Next M lines: u v w,
an edge u → v of weight w (0 ≤ w ≤ 10^9). Parallel edges and self-loops may appear.

**Output.** One line: dist(1), dist(2), …, dist(N), space-separated (`-1` if unreachable).

**Sample Input**
```
6 6 1
1 2 4
1 3 1
3 2 2
2 4 1
3 4 5
4 5 3
```
**Sample Output**
```
0 3 1 4 7 -1
```

## Idea

Always settle the unsettled vertex with the smallest tentative distance, which is the root of a
min-heap. With non-negative weights that distance is final, and relaxing its outgoing edges can
only lower other distances. `std::priority_queue` has no DECREASE-KEY, so on every improvement
push a new pair (newDist, v). When a pair is popped whose distance is larger than `dist[v]`, it
is stale: skip it (**lazy deletion**). The heap holds at most M + 1 entries.

## Pseudocode

```
function DIJKSTRA(G, s):
    for each vertex v:
        dist[v] = INF
    dist[s] = 0
    H = empty min-heap of (distance, vertex)
    INSERT(H, (0, s))
    while H is not empty:
        (d, u) = EXTRACT_MIN(H)
        if d > dist[u]:
            continue                    // stale entry
        for each edge (u, v, w) in G.adj[u]:
            if dist[u] + w < dist[v]:   // RELAX
                dist[v] = dist[u] + w
                INSERT(H, (dist[v], v)) // instead of DECREASE-KEY
    return dist
```

## Complexity

Binary heap with lazy deletion: O((N + M) log M) = O(M log N) time, O(N + M) space. A heap with
real DECREASE-KEY (hand-written, with a position array) is O((N + M) log N). A Fibonacci heap
gives O(M + N log N), because DECREASE-KEY is O(1) amortized. The plain O(N²) array version is
better for dense graphs.

## Edge cases / traps

- Distances can reach about 10^5 × 10^9: use `long long`.
- Unreachable vertices print `-1`. Do not print your INF sentinel.
- **Negative weights break Dijkstra.** Use Bellman-Ford (that is `brute.cpp`).
- Without the stale check the answer is still correct but slower. Without `greater<>` you have a
  max-heap and the answer is **wrong**.
- Pair order in the heap is (distance, vertex), with the distance first so that it is compared
  first.

## Variants they might ask

- **Undirected graph:** for each edge also add `adj[v].push_back(make_pair(u, w))`.
- **Print the path to a target:** store `parent[v] = u` when relaxing, then walk back from the
  target and reverse.
- **Grid / minimum effort path:** vertices are cells and edges go to the 4 neighbours. The same
  loop works with `(dist, r, c)`.
- **Network delay time** (LeetCode 743): the answer is max(dist), or -1 if any vertex is
  unreachable.

## Files

`sol.cpp` (STL min-heap, lazy deletion), `brute.cpp` (Bellman-Ford).
