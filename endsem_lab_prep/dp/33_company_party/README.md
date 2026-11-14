# 33. Company Party (DP on a tree)

Source: Tutorial 9 Q5 (short version Q1) — CLRS Problem 15-6 "Planning a company party".

## Problem

The company hierarchy is a rooted tree: employee `i` has an immediate supervisor `p[i]`, and the president (the
root) has `p = 0`. Every employee `i` has a conviviality rating `c[i]`, which may be negative.
Choose a set of guests so that **no employee attends together with his/her immediate supervisor**, maximising the
total conviviality of the guests.

(a) Print the maximum total conviviality (inviting nobody is allowed and gives 0).
(b) Print the maximum total conviviality if the **president must attend**.

**Input**
Line 1: `n`. Line 2: `n` integers `c[1..n]`. Line 3: `n` integers `p[1..n]` (`p[i]` is the immediate supervisor
of `i`; exactly one `p[i]` is 0 — the president).

**Output**
Line 1: the answer to (a). Line 2: the answer to (b).

**Constraints**
1 ≤ n ≤ 10^5, |c[i]| ≤ 10^4, the input forms one rooted tree.

**Sample Input**
```
8
2 9 -2 4 1 6 2 5
0 1 1 2 2 3 3 6
```

**Sample Output**
```
17
15
```

(Tree: 1 → {2, 3}, 2 → {4, 5}, 3 → {6, 7}, 6 → {8}. Best party {2, 6, 7} = 9 + 6 + 2 = 17 mixes levels.
With the president: {1, 4, 5, 6, 7} = 2 + 4 + 1 + 6 + 2 = 15.)

## Idea

- Two values per employee `v` (subproblems are subtrees):
  - `inc[v]` = best total inside `v`'s subtree **with `v` attending**;
  - `exc[v]` = best total inside `v`'s subtree **with `v` not attending**.
- Recurrence over the children `u` of `v`:
  - `inc[v] = c[v] + Σ exc[u]` — if `v` attends, none of its direct reports may;
  - `exc[v] = Σ max(inc[u], exc[u])` — if `v` stays home, each child subtree is independent and picks its best.
- Base case (leaf): `inc[v] = c[v]`, `exc[v] = 0`.
- Order: children before parents (post-order). Here: BFS from the root gives parents before children, so process
  the BFS order **backwards** — no recursion, so a 10^5-long chain cannot overflow the stack.
- Answers: (a) `max(inc[root], exc[root])`; (b) `inc[root]` (the president is forced in, nothing else changes).
- Correctness (cut-and-paste): in an optimal party restricted to `v`'s subtree, the part inside each child's subtree
  must be optimal for that child under the constraint imposed by `v`'s choice, otherwise swap in a better one.
- Reconstruction: go top-down; if `v` is "in", children are "out"; if `v` is "out", each child `u` is in iff `inc[u] > exc[u]`.

## Pseudocode

```
function PARTY(n, c[1..n], p[1..n]):
    for i = 1 to n:
        if p[i] == 0: root = i
        else: children[p[i]].append(i)
    order = BFS(root)                         // parents before children
    for t = n - 1 down to 0:
        v = order[t]
        inc[v] = c[v], exc[v] = 0
        for u in children[v]:
            inc[v] = inc[v] + exc[u]
            exc[v] = exc[v] + max(inc[u], exc[u])
    return (max(inc[root], exc[root]), inc[root])

Main:
    read n, c[1..n], p[1..n]
    (a, b) = PARTY(n, c, p)
    print a
    print b
```

## Complexity

O(n) time (each edge is used once), O(n) space.

## Edge cases / traps

- Negative ratings: a leaf with `c < 0` should stay home — `exc = 0` takes care of it; never initialise with `inc` only.
- All ratings negative: (a) is 0 (empty party), (b) is `c[president] + Σ exc[children] = c[president]`.
- `n = 1`: (a) `max(c[1], 0)`, (b) `c[1]`.
- The president is not necessarily employee 1 — find the `p[i] = 0`.
- Recursive DFS on a chain of 10^5 employees may overflow the stack; the reverse-BFS loop avoids it.
- Sums reach 10^9 — use `long long`.

## Variants they might ask

- **Print the guest list**: top-down pass as described in Idea (or store a flag while computing).
- **Maximum independent set / count of guests** (all `c = 1`): same code.
- **No two guests at distance ≤ 2** (no grand-supervisor either): state needs `exc` split into "child attends or not".
- **Tree given as an edge list** (undirected, root 1): build adjacency lists, BFS from 1 to get parents, then the same loop.
