# 16. Last stone weight

Source: exam-style variant of LeetCode 1046 "Last Stone Weight",
<https://leetcode.com/problems/last-stone-weight/>. Optional warm-up for max-heap simulation.

## Problem

There are N stones with positive weights. Each turn, take the two **heaviest** stones, x ≤ y,
and smash them. If x = y both are destroyed. Otherwise x is destroyed and y becomes y − x.
Repeat until at most one stone is left. Print its weight, or 0 if no stone is left.

**Input.** Line 1: N (1 ≤ N ≤ 10^5). Line 2: N weights in [1, 10^9].

**Output.** One integer.

**Sample Input**
```
6
2 7 4 1 8 1
```
**Sample Output**
```
1
```
(8,7 → 1. 4,2 → 2. 2,1 → 1. 1,1 → gone. 1 remains.)

## Idea

"Repeatedly take the largest two" is a max-heap: pop twice, push back the difference if it is
non-zero.

## Pseudocode

```
function LAST_STONE(w[1..N]):
    H = BUILD_MAX_HEAP(w)
    while H.size > 1:
        y = EXTRACT_MAX(H)
        x = EXTRACT_MAX(H)
        if y != x:
            INSERT(H, y - x)
    if H is empty:
        return 0
    return MAX(H)
```

## Complexity

Each turn removes at least one stone: at most N − 1 turns, O(N log N) time, O(N) space.

## Edge cases / traps

- N = 1: print that stone.
- All stones can vanish (`2 2`): print 0. Do not read `top()` of an empty heap.
- `priority_queue<long long>` is already a max-heap. Do not add `greater<>`.

## Variants they might ask

- **Smash the two lightest:** min-heap.
- **Print the heap after each turn:** use the hand-written heap from `templates/heap_manual`.
- **Last Stone Weight II** (any two stones, minimise the result): that is a **DP** subset-sum
  problem, not a heap problem. Split into two groups with sums as close as possible.

## Files

`sol.cpp` (STL max-heap), `brute.cpp` (sorts before each smash).
