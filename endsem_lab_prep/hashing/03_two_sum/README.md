# 03. Two Sum

Source: LeetCode 1 (Coding Practice Set 3, Q2 "Two Sum (Hashing)").

## Problem

Given an array a[0..n−1] of integers and an integer target, find indices i < j with
a[i] + a[j] = target. If several pairs exist, print the one with the **smallest j**; among those, the
**smallest i**. Indices are 0-based. If no pair exists print `-1 -1`.

**Input**
Line 1: n. Line 2: n integers. Line 3: target.

**Output**
One line: `i j`, or `-1 -1`.

**Constraints**
1 ≤ n ≤ 10^5, −10^9 ≤ a[i] ≤ 10^9, −2·10^9 ≤ target ≤ 2·10^9.

**Sample Input**
```
4
2 7 11 15
9
```

**Sample Output**
```
0 1
```

## Idea

Scan j from left to right. The partner of a[j] must be target − a[j] at an earlier index, so keep a
hash map value → first index seen so far. The first j whose complement is already in the map is the
smallest possible j, and storing only the first index of each value gives the smallest i. Look up
**before** inserting a[j], otherwise a[j] could pair with itself (target = 2·a[j]).

## Pseudocode

```
function TWO_SUM(a[0..n-1], target):
    first = empty hash map                 // value -> first index
    for j = 0 to n-1:
        need = target - a[j]
        if need in first:
            return (first[need], j)
        if a[j] not in first:
            first[a[j]] = j
    return (-1, -1)
```

## Complexity

O(n) expected time (one lookup and at most one insert per element), O(n) space.
Brute force: O(n²) over all pairs (`brute.cpp`).

## Edge cases / traps

- Same value twice: `3 3` with target 6 gives `0 1`; a single 3 must not pair with itself (tests/3).
- n = 1 or no valid pair: `-1 -1` (tests/4, tests/6).
- a[i] + a[j] and target − a[j] can exceed `int` (|values| up to 10^9): use `long long` (tests/5).
- Don't overwrite the stored index with later duplicates if the question wants the smallest i.
- Sorting + two pointers loses the original indices unless you sort (value, index) pairs.

## Variants they might ask

- **Any pair / LeetCode format**: same code; LeetCode guarantees exactly one answer.
- **Count pairs with sum = target**: keep `cnt[value]` instead of the first index and add
  `cnt[target − a[j]]` for every j (use `long long` for the answer). See also `14a_pairs_with_difference_k`.
- **Print values instead of indices**: print `a[i] a[j]`.
- **Use your own chained hash table** (no STL): store (value, index) nodes; `find` = CHAINED-HASH-SEARCH.
