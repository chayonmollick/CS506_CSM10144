# 11. Connect ropes with minimum cost

Source: exam-style classic (GfG "Minimum Cost of Ropes", LeetCode 1167 "Minimum Cost to Connect
Sticks", <https://leetcode.com/problems/minimum-cost-to-connect-sticks/>). It is the same greedy
as building a Huffman code.

## Problem

There are N ropes with given lengths. Joining two ropes of lengths a and b costs a + b and
produces one rope of length a + b. Join all ropes into one with the minimum total cost.

**Input.** Line 1: N (1 ≤ N ≤ 10^5). Line 2: N lengths, each in [1, 10^9].

**Output.** One integer: the minimum total cost (0 if N = 1).

**Sample Input**
```
4
4 3 2 6
```
**Sample Output**
```
29
```
(2+3 = 5, cost 5. Then 4+5 = 9, cost 9. Then 6+9 = 15, cost 15. Total 29.)

## Idea

A rope's length is paid once for every join it takes part in, which is its depth in the merge
tree. To minimise Σ length × depth, the shortest ropes should be deepest, so always join the
**two shortest** current ropes. This is Huffman's exchange argument. A min-heap gives the two
shortest in O(log n).

## Pseudocode

```
function MIN_COST_ROPES(len[1..N]):
    H = BUILD_MIN_HEAP(len)
    cost = 0
    while H.size > 1:
        a = EXTRACT_MIN(H)
        b = EXTRACT_MIN(H)
        cost = cost + a + b
        INSERT(H, a + b)
    return cost
```

## Complexity

N − 1 joins, each with 3 heap operations: O(N log N) time, O(N) space.

## Edge cases / traps

- N = 1: no joins, cost 0. The loop condition `size > 1` handles it.
- The cost can reach about 10^9 × 10^5 × 17: use `long long` for the lengths and the sum.
- Sorting once and joining from the left is **wrong**. The new rope must be reinserted, and it
  can be longer than ropes not yet joined. Try `1 1 1 1`: the greedy cost is 8, left-to-right
  gives 9.
- Merging the two **longest** first is the opposite of what you want.

## Variants they might ask

- **Huffman code lengths / total encoded bits:** the same loop on frequencies. The total cost
  equals Σ freq × codeLength.
- **Optimal merge of sorted files:** the same thing, where the cost of a merge is the sum of
  the sizes.
- **Join k ropes at a time:** pad with zero-length ropes until (N − 1) % (k − 1) == 0, then pop
  k at a time.
- **Print the cost of each join:** print `a + b` inside the loop.

## Files

`sol.cpp` (STL min-heap), `brute.cpp` (tries every join order, for N ≤ 7).
