# 05. Longest Subarray with Equal Numbers of 0s and 1s

Source: Tutorial 8, Q10(b) (also LeetCode 525 "Contiguous Array").

## Problem

Given a binary array A[0..n−1], find the length of the longest contiguous subarray that contains the
same number of 0s and 1s. Print 0 if there is none.

**Input**
Line 1: n. Line 2: n values, each 0 or 1.

**Output**
One integer: the maximum length.

**Constraints**
1 ≤ n ≤ 10^5.

**Sample Input**
```
7
1 0 1 1 1 0 0
```

**Sample Output**
```
6
```

(A[1..6] = 0 1 1 1 0 0 has three 0s and three 1s.)

## Idea

Replace every 0 by −1. A subarray has equally many 0s and 1s exactly when its sum is 0, i.e. when two
prefix sums are equal: P[i] = P[j] means A[i..j−1] is balanced, with length j − i. For a fixed j the
longest such subarray uses the **smallest** i with P[i] = P[j], so the hash map stores only the
**first** index at which each prefix value occurs, and is never overwritten. That is the answer to the
tutorial's "which value, and why": the earliest index maximises j − i, and any later index for the
same value can only give a shorter subarray.

Store prefix 0 at index −1 (the empty prefix) so balanced subarrays starting at 0 are found.

## Pseudocode

```
function LONGEST_EQUAL_01(A[0..n-1]):
    first = empty hash map              // prefix sum -> first index
    first[0] = -1
    s = 0, best = 0
    for j = 0 to n-1:
        if A[j] == 1: s = s + 1 else: s = s - 1
        if s in first:
            best = max(best, j - first[s])
        else:
            first[s] = j                // keep the earliest index only
    return best
```

## Complexity

O(n) expected time, O(n) space.
Since prefix sums lie in [−n, n], a plain array of size 2n + 1 indexed by s + n is a direct-address
table that does the same job in worst-case O(n) (slides: direct addressing works when the universe is
small).

## Edge cases / traps

- Forgetting `first[0] = -1`: misses balanced prefixes like `1 0` (tests/6 must print 2).
- Updating `first[s]` on every visit (storing the last index) gives the *shortest*, not longest.
- All equal values: answer 0 (tests/3).
- Answer is a length (j − i), not j − i + 1: with index −1 stored for the empty prefix the
  formula j − first[s] is already the length.
- Own hash table: prefix sums are negative, so use `((k % M) + M) % M`.

## Variants they might ask

- **Print the subarray bounds**: when `best` improves, store `l = first[s] + 1`, `r = j`.
- **Longest subarray with sum K / zero-sum subarray in a general array**: look up `s − K` instead of
  `s` (`14b_longest_subarray_sum_k`).
- **Count balanced subarrays**: store counts instead of first indices (same as `04_subarray_sum_k`
  with K = 0).
- **Equal numbers of two given values x and y**: map x → +1, y → −1, everything else → 0.

## Files

`sol.cpp` (`unordered_map`), `sol_manual.cpp` (own chained table of (prefix, first index) nodes),
`brute.cpp` (O(n²) counting). 500 random inputs agree.
