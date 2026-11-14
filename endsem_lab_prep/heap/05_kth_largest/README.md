# 05. K-th largest element (array and stream)

Source: exam-style variant of LeetCode 215 "Kth Largest Element in an Array"
(<https://leetcode.com/problems/kth-largest-element-in-an-array/>) and LeetCode 703 "Kth Largest
Element in a Stream" (<https://leetcode.com/problems/kth-largest-element-in-a-stream/>).

## Problem

Integers a_1, a_2, …, a_N arrive one at a time. The k-th largest is the k-th element of the
**sorted-descending** list, so duplicates count separately: in `5 5 4`, the 2nd largest is 5.

(a) Print the K-th largest element of the whole array.
(b) After each of a_K, a_(K+1), …, a_N arrives, print the K-th largest among the elements seen
so far. That is N − K + 1 values.

**Input.** Line 1: N and K (1 ≤ K ≤ N ≤ 10^5). Line 2: N integers in [-10^9, 10^9].

**Output.** Line 1: the answer to (a). Line 2: the N − K + 1 answers to (b), space-separated.

**Sample Input**
```
8 3
4 1 7 3 8 5 9 2
```
**Sample Output**
```
7
1 3 4 5 7 7
```

## Idea

Keep a **min-heap of size K** holding the K largest keys seen so far. Its root is the smallest of
them, which is exactly the K-th largest. For a new key x, push it, and if the size becomes K + 1,
pop the root. In the hand-written version, if x > root, overwrite the root with x and run
MIN-HEAPIFY(1). Answer (a) is the root after the last element, which is also the last value of (b).

## Pseudocode

```
function KTH_LARGEST_STREAM(a[1..N], K):
    H = empty min-heap
    res = []
    for i = 1 to N:
        if H.size < K:
            INSERT(H, a[i])
        else if a[i] > MIN(H):
            H[1] = a[i]                 // replace the smallest of the top K
            MIN_HEAPIFY(H, 1)
        if H.size == K:
            res.append(MIN(H))
    print MIN(H)                        // (a)
    print res                           // (b)
```

## Complexity

O(N log K) time and O(K) extra space. Sorting would be O(N log N) per query. A max-heap of all
N keys followed by K − 1 extract-max calls is O(N + K log N) for (a) only.

## Edge cases / traps

- K = N: the answer is the minimum, and line 2 has exactly one value.
- K = 1: the running maximum.
- Duplicates count separately. Do not deduplicate unless the paper says "k-th largest
  **distinct**".
- Use a **min**-heap for "largest" and a **max**-heap for "smallest". This is the most common
  mistake.
- The (b) sequence never decreases, because the K-th largest can only go up as keys arrive.

## Variants they might ask

- **K-th smallest:** use a max-heap of size K (`priority_queue<long long>`) and pop when the size
  exceeds K.
- **Print the K largest in descending order:** pop the heap into a vector and reverse it.
- **K-th largest distinct:** skip x if it is already in the heap. Keep a hash set of heap keys
  next to the heap.
- **One-shot only (a):** `nth_element` / quickselect is O(N) average. Mention it, but write the
  heap.

## Files

`sol.cpp` (STL min-heap), `sol_manual.cpp` (hand-written min-heap, replace-root trick),
`brute.cpp` (sort every prefix).
