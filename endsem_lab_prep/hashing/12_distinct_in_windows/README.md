# 12. Count Distinct Elements in Every Window of Size k

Source: classic hashing + sliding window problem (GeeksforGeeks "Count distinct elements in every
window"); same counting idea as `07_minimum_window_substring`.

## Problem

Given an array a[0..n−1] and an integer k, print the number of distinct values in every window
a[i..i+k−1], for i = 0, 1, ..., n−k, in order.

**Input**
Line 1: n k. Line 2: n integers.

**Output**
n − k + 1 integers on one line, separated by spaces.

**Constraints**
1 ≤ k ≤ n ≤ 10^5, −10^9 ≤ a[i] ≤ 10^9.

**Sample Input**
```
7 4
1 2 1 3 4 2 3
```

**Sample Output**
```
3 4 4 3
```

(Windows: {1,2,1,3} → 3, {2,1,3,4} → 4, {1,3,4,2} → 4, {3,4,2,3} → 3.)

## Idea

Keep a hash map value → count for the current window. Sliding one step adds a[i] (count + 1) and
removes a[i−k] (count − 1). When a count drops to 0, **erase** the key, so the number of keys in the
map is exactly the number of distinct values. (Equivalently keep a counter `distinct`: +1 when a
count goes 0 → 1, −1 when it goes 1 → 0.)

## Pseudocode

```
function DISTINCT_IN_WINDOWS(a[0..n-1], k):
    freq = empty hash map
    for i = 0 to n-1:
        freq[a[i]] = freq[a[i]] + 1               // a[i] enters
        if i >= k:                                // a[i-k] leaves
            freq[a[i-k]] = freq[a[i-k]] - 1
            if freq[a[i-k]] == 0: delete a[i-k] from freq
        if i >= k-1:
            print size(freq)
```

## Complexity

O(n) expected time, O(k) space (the map never holds more than k keys).
Brute force O(n·k²) (`brute.cpp`), or O(n·k) with a fresh set per window.

## Edge cases / traps

- Not erasing zero-count keys: `freq.size()` then counts values that already left the window.
- Remove a[i−k] only once the window is full (`i >= k`), print only from `i = k−1`.
- k = n: one number (tests/3). k = 1: all ones (tests/6). All equal: all ones (tests/4).
- Values can be negative or up to 10^9: hash map, not a counting array (tests/5).

## Variants they might ask

- **Windows where all k elements are distinct**: count windows with `freq.size() == k`.
- **Duplicate within distance k** ("contains nearby duplicate"): window of size k+1 with a hash set;
  report true as soon as an inserted value is already present.
- **Most frequent element in each window / first non-repeating in each window**: same add/remove
  bookkeeping, plus a queue for the order of arrival.
- **Longest subarray with at most d distinct values**: variable-size window, shrink while
  `freq.size() > d`.

## Files

`sol.cpp`, `brute.cpp` (rescans each window). 800 random inputs agree.
