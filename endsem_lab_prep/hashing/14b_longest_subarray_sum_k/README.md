# 14b. Longest Subarray with Sum K (Largest Zero-Sum Subarray when K = 0)

Source: classic prefix-sum + hashing problem (GeeksforGeeks "Largest subarray with 0 sum" /
"Longest subarray with sum K"); first-occurrence idea of Tutorial 8 Q10(b).

## Problem

Given an integer array a[0..n−1] (negative values allowed) and an integer K, print the length of the
longest contiguous subarray whose sum is exactly K. Print 0 if no such subarray exists.

**Input**
Line 1: n K. Line 2: n integers.

**Output**
One integer: the maximum length.

**Constraints**
1 ≤ n ≤ 10^5, −10^9 ≤ a[i], K ≤ 10^9.

**Sample Input**
```
8 0
15 -2 2 -8 1 7 10 23
```

**Sample Output**
```
5
```

(−2 2 −8 1 7 has sum 0.)

## Idea

Prefix sums P[0] = 0, P[j+1] = P[j] + a[j]. The subarray a[i..j] has sum K exactly when
P[j+1] − P[i] = K, i.e. P[i] = P[j+1] − K. For the longest subarray ending at j we want the **earliest**
prefix with value P[j+1] − K, so the hash map stores only the first index of each prefix value (never
overwritten). Store prefix 0 at index −1 so subarrays starting at 0 count.

This is `04_subarray_sum_k` with "count" replaced by "first index", and `05_longest_equal_01` with
an arbitrary K.

## Pseudocode

```
function LONGEST_SUM_K(a[0..n-1], K):
    first = empty hash map              // prefix sum -> first index
    first[0] = -1
    prefix = 0, best = 0
    for j = 0 to n-1:
        prefix = prefix + a[j]
        if (prefix - K) in first:
            best = max(best, j - first[prefix - K])
        if prefix not in first:
            first[prefix] = j           // earliest index only
    return best
```

## Complexity

O(n) expected time, O(n) space. Brute force O(n²).

## Edge cases / traps

- Look up `prefix − K` **before** inserting `prefix` (for K = 0 the current prefix would match
  itself, giving length 0, harmless, but for the "count" variant it matters).
- Do not overwrite `first[prefix]`; the latest index gives shorter subarrays.
- Forgetting `first[0] = −1` misses subarrays starting at index 0 (tests/2, tests/4).
- Sliding window does not work with negative numbers.
- Prefix sums up to 10^14: `long long` (tests/6).

## Variants they might ask

- **Print the subarray**: when `best` improves, store `l = first[prefix − K] + 1`, `r = j`.
- **Does a zero-sum subarray exist** (yes/no): answer yes as soon as a prefix repeats or is 0.
- **Count subarrays with sum K**: see `04_subarray_sum_k` (counts instead of first index).
- **Longest subarray with equal 0s and 1s**: map 0 → −1, K = 0 (`05_longest_equal_01`).

## Files

`sol.cpp`, `brute.cpp` (O(n²)). 800 random inputs agree.
