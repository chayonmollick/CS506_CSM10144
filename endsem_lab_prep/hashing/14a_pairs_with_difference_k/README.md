# 14a. Count Pairs with Difference k

Source: classic hashing problem (GeeksforGeeks "Count pairs with given difference"; LeetCode 2006 /
532 are variants).

## Problem

Given an array a[0..n−1] and an integer k ≥ 0, count the index pairs (i, j) with i < j and
|a[i] − a[j]| = k. Equal values at different indices form different pairs.

**Input**
Line 1: n k. Line 2: n integers.

**Output**
One integer: the number of pairs.

**Constraints**
1 ≤ n ≤ 10^5, 0 ≤ k ≤ 2·10^9, −10^9 ≤ a[i] ≤ 10^9. The answer can exceed 2^31.

**Sample Input**
```
5 3
1 5 3 4 2
```

**Sample Output**
```
2
```

(Pairs (1, 4) and (5, 2).)

## Idea

Scan j left to right with a hash map cnt[value] of the elements before j. The partner of a[j] is
either a[j] − k or a[j] + k, so add cnt[a[j] − k] + cnt[a[j] + k], then insert a[j]. Each pair is
counted exactly once, at its larger index. When k = 0 the two partner values are the same: add it
only once (otherwise every equal pair is counted twice).

## Pseudocode

```
function COUNT_PAIRS_DIFF_K(a[0..n-1], k):
    cnt = empty hash map
    ans = 0
    for j = 0 to n-1:
        ans = ans + cnt[a[j] - k]                 // 0 if absent
        if k != 0:
            ans = ans + cnt[a[j] + k]
        cnt[a[j]] = cnt[a[j]] + 1                 // insert AFTER counting
    return ans
```

## Complexity

O(n) expected time, O(n) space. Brute force O(n²). (Sort + two pointers is O(n log n) but counting
duplicates correctly is fiddly; the hash version handles them for free.)

## Edge cases / traps

- k = 0: count pairs of equal values, n·(n−1)/2 for all-equal input (tests/3: 5 equal → 10).
  Adding both cnt[x − k] and cnt[x + k] would double it.
- Inserting a[j] before counting pairs it with itself when k = 0.
- k up to 2·10^9 and x ± k overflow `int`: use `long long` (tests/5).
- Answer up to n²/2 ≈ 5·10^9: `long long`.
- No pair: 0 (tests/2, tests/6).

## Variants they might ask

- **Unique value pairs** (LeetCode 532 "K-diff pairs"): build a count map first; for k > 0 count
  distinct x with x + k present; for k = 0 count distinct x with cnt[x] ≥ 2.
- **Pairs with sum k**: partner is `k − a[j]` (see `03_two_sum`).
- **Print the pairs**: store indices per value (a vector per key) and print (i, j) for each partner index.
- **Does any pair exist**: return as soon as a partner count is positive.

## Files

`sol.cpp`, `brute.cpp` (all pairs). 800 random inputs agree.
