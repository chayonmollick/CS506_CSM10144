# 09. Top-K frequent elements

Source: exam-style variant of LeetCode 347 "Top K Frequent Elements",
<https://leetcode.com/problems/top-k-frequent-elements/>. It combines hashing and a heap, both
on the syllabus.

## Problem

Given N integers, print the K values that occur most often.

**Order (stated):** higher frequency first. When two values have the same frequency, the
**smaller value comes first**. This order decides both which values are chosen and the order
they are printed in.

**Input.** Line 1: N and K (1 ≤ N ≤ 10^5, 1 ≤ K ≤ number of distinct values). Line 2: N
integers in [-10^9, 10^9].

**Output.** One line with K values, space-separated, in the order above.

**Sample Input**
```
10 3
4 1 2 1 3 4 2 1 3 4
```
**Sample Output**
```
1 4 2
```
(1 and 4 appear 3 times, 2 and 3 appear twice. Ties are broken by the smaller value.)

## Idea

1. Count frequencies with a hash map (`unordered_map`): O(N).
2. Keep the best K of the D distinct values in a **min-heap of size K** whose root is the
   *worst* kept item. Here "worst" means the lowest frequency, and on equal frequency the larger
   value. Push each (freq, value) and pop the root when the size exceeds K.
3. The heap pops worst-first, so reverse at the end.

With STL, the key `(freq, -value)` under `greater<>` puts exactly that worst item on top.

## Pseudocode

```
function TOP_K_FREQUENT(a[1..N], K):
    freq = empty hash map
    for x in a:
        freq[x] = freq[x] + 1
    H = empty min-heap ordered by (freq, -value)   // root = worst kept item
    for (value, f) in freq:
        INSERT(H, (f, -value))
        if H.size > K:
            EXTRACT_MIN(H)
    res = []
    while H is not empty:
        (f, negv) = EXTRACT_MIN(H)
        res.append(-negv)
    reverse(res)
    return res
```

## Complexity

O(N) to count and O(D log K) for the heap, where D is the number of distinct values. Total is
O(N + D log K) time and O(D) space. Alternatives: a max-heap of all D items with K pops is
O(D + K log D). Bucket sort by frequency is O(N), but you still need to sort inside buckets to
get the tie order.

## Edge cases / traps

- The tie-break must hold **inside the heap** too, not only when printing. Otherwise the wrong
  value can be thrown out at the boundary.
- K = D: print every distinct value in the stated order.
- Negative values: `-value` stays in range for `long long`.
- Iterating an `unordered_map` gives an arbitrary order. Never depend on it for output.

## Variants they might ask

- **Ties by larger value / first occurrence:** change the heap key, for example
  `(freq, value)` or `(freq, -firstIndex)`.
- **Top-K frequent words** (LeetCode 692, ties alphabetical): `pair<int, string>` with a custom
  comparator struct, because `-string` does not exist (see the STL notes in `../README.md`).
- **Print value and count:** keep the pair and print `value:count`.
- **K least frequent:** use a max-heap root of the worst kept item, so flip the comparisons.

## Files

`sol.cpp` (unordered_map + size-K min-heap), `brute.cpp` (std::map + full sort).
