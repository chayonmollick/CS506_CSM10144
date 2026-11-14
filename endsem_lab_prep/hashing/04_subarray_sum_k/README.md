# 04. Count Subarrays with Sum Exactly K

Source: Tutorial 8, Q10(a) (also LeetCode 560).

## Problem

Given an integer array A[0..n−1] (entries may be negative or zero) and an integer K, count the
subarrays (contiguous, non-empty) whose sum is exactly K. Two subarrays are different if their start
or end index differs.

**Input**
Line 1: n K. Line 2: n integers.

**Output**
One integer: the number of subarrays with sum K.

**Constraints**
1 ≤ n ≤ 10^5, −10^9 ≤ A[i], K ≤ 10^9. The answer can exceed 2^31 (use 64-bit).

**Sample Input**
```
5 3
1 2 3 -3 3
```

**Sample Output**
```
5
```

(The five subarrays: [1 2], [3], [1 2 3 −3], [3 −3 3], the last [3].)

## Idea

Let P[0] = 0 and P[j] = A[0] + ... + A[j−1]. The subarray A[i..j−1] has sum P[j] − P[i], so it has sum
K exactly when P[i] = P[j] − K. Scan j left to right with a hash map cnt[value] = how many earlier
prefixes had that value; each j adds cnt[P[j] − K]. Start with cnt[0] = 1 (the empty prefix, for
subarrays that start at index 0). Look up before inserting P[j] so a prefix never pairs with itself
(matters when K = 0).

**Why not a sliding window?** Shrinking the window only helps if removing elements lowers the sum. With
negative numbers, extending can lower the sum and shrinking can raise it, so the window has no
monotone rule for when to move which end.

**Correctness**: every subarray corresponds to exactly one pair (i < j) of prefix indices, and at step
j the map holds exactly P[0..j−1], so each pair with P[i] = P[j] − K is counted once.

## Pseudocode

```
function COUNT_SUBARRAYS_SUM_K(A[0..n-1], K):
    cnt = empty hash map            // prefix value -> occurrences
    cnt[0] = 1
    prefix = 0, ans = 0
    for j = 0 to n-1:
        prefix = prefix + A[j]
        if (prefix - K) in cnt:
            ans = ans + cnt[prefix - K]
        cnt[prefix] = cnt[prefix] + 1   // (0 if absent)
    return ans
```

## Complexity

O(n) expected time, O(n) space (at most n + 1 distinct prefix sums). Brute force O(n²).

## Edge cases / traps

- Forgetting `cnt[0] = 1` misses every subarray that starts at index 0.
- All zeros with K = 0: n(n+1)/2 subarrays; n = 10^5 gives 5 000 050 000, more than `int`
  (tests/9). Prefix sums reach 10^14: `long long` for prefix, keys and answer.
- Inserting `prefix` before the lookup counts the empty subarray when K = 0.
- Negative K and negative prefixes: fine for `unordered_map`; in your own table use
  `((k % M) + M) % M` (`sol_manual.cpp`).
- `cnt[prefix - K]` with `operator[]` inserts a zero entry for every miss. Use `find` (or `count`) to
  keep the map small.

## Variants they might ask

- **Longest subarray with sum K**: store the *first* index of each prefix instead of a count
  (`14b_longest_subarray_sum_k`; zero-sum when K = 0).
- **Does any subarray have sum K / print one**: return as soon as `prefix − K` is found; store the
  index to print the bounds.
- **Subarray sum divisible by k**: key = `((prefix % k) + k) % k`, count equal keys.
- **Only non-negative numbers**: a sliding window also works, but the hash version is still correct.

## Files

`sol.cpp` (`unordered_map`), `sol_manual.cpp` (own chained table with (key, count) nodes, M = 100003),
`brute.cpp` (O(n²)). 500 random inputs agree; tests 7–9 are large (9 checks 64-bit overflow).
