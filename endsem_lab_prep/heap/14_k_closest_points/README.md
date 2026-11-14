# 14. K closest points to the origin

Source: exam-style variant of LeetCode 973 "K Closest Points to Origin",
<https://leetcode.com/problems/k-closest-points-to-origin/>.

## Problem

Given N points (x, y) and K, print the K points closest to the origin (0, 0) by Euclidean
distance.

**Order (stated):** increasing distance. On equal distance, smaller x first, and on equal x,
smaller y first. This order decides both which points are chosen and the print order.

**Input.** Line 1: N and K (1 ≤ K ≤ N ≤ 10^5). Next N lines: x y (-10^4 ≤ x, y ≤ 10^4).
Points may repeat.

**Output.** K lines, each `x y`, in the order above.

**Sample Input**
```
5 3
1 3
-2 2
3 -1
-3 1
0 -4
```
**Sample Output**
```
-2 2
-3 1
1 3
```
((-2, 2) has distance² 8. The other three tie at distance² 10 and are ordered by x.)

## Idea

Compare **squared** distances, which avoids `sqrt` and floating-point error. Keep a **max-heap
of size K** of `(d², x, y)`. Its root is the worst of the kept points. Push every point and pop
when the size exceeds K. In C++ `pair` compares lexicographically, so the default max-heap on
`(d², (x, y))` already applies the tie rule. Pop all K and reverse.

## Pseudocode

```
function K_CLOSEST(P[1..N], K):
    H = empty max-heap ordered by (d2, x, y)
    for (x, y) in P:
        INSERT(H, (x*x + y*y, x, y))
        if H.size > K:
            EXTRACT_MAX(H)              // farthest of the K+1
    res = []
    while H is not empty:
        res.append(EXTRACT_MAX(H))
    reverse(res)
    return res
```

## Complexity

O(N log K) time and O(K) space. Sort-everything is O(N log N). Quickselect is O(N) average but
leaves the K points unordered.

## Edge cases / traps

- "Closest" means a **max**-heap of size K. A min-heap of all N with K pops also works
  (O(N + K log N) if you build it in O(N)).
- d² up to 2·10^8 fits in `int`, but `long long` is safer if the bounds grow.
- K = N: print all points sorted by the order.
- Duplicate points are printed as many times as they appear.

## Variants they might ask

- **Closest to a given point (px, py):** use (x−px)² + (y−py)².
- **Ties by input order:** store `(d², index)` and print the stored point.
- **K farthest:** min-heap of size K (`greater<Item>`). Popping gives nearest-first, so reverse
  for farthest-first, and restate the tie rule (for example larger d², then smaller x) in the
  key.
- **Comparator struct instead of pairs** (for `struct Point`), see the STL notes in
  `../README.md`.

## Files

`sol.cpp` (size-K max-heap of pairs), `brute.cpp` (full sort with the same order).
