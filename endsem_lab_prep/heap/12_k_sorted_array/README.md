# 12. Sort a K-sorted (nearly sorted) array

Source: exam-style classic (GfG "Sort a nearly sorted (or K sorted) array"; CLRS exercise on
merging / k-sorted arrays).

## Problem

An array of N integers is **K-sorted**: every element is at most K positions away from where
it would be in the sorted array. Sort it in O(N log K) using a heap.

**Input.** Line 1: N and K (1 ≤ N ≤ 10^5, 0 ≤ K < N). Line 2: N integers in [-10^9, 10^9].
The array is guaranteed to be K-sorted.

**Output.** One line: the array in non-decreasing order.

**Sample Input**
```
7 3
6 5 3 2 8 10 9
```
**Sample Output**
```
2 3 5 6 8 9 10
```

## Idea

The element that belongs at sorted position i is somewhere in a[i..i+K]. After positions
0..i−1 are filled, a min-heap holding the next K+1 unplaced elements therefore contains the right
element as its minimum. Slide along: push a[i], and once the heap has K+1 elements, pop the min
into the next output slot. At the end, drain the heap.

## Pseudocode

```
function SORT_K_SORTED(a[0..N-1], K):
    H = empty min-heap
    out = 0
    for i = 0 to N - 1:
        INSERT(H, a[i])
        if H.size > K:                  // heap holds K+1 elements
            a[out] = EXTRACT_MIN(H)
            out = out + 1
    while H is not empty:
        a[out] = EXTRACT_MIN(H)
        out = out + 1
    return a
```

## Complexity

O(N log K) time and O(K) extra space. Writing back into `a` is safe because `out ≤ i` always.
A full sort is O(N log N). Insertion sort is O(N·K), which is fine only for tiny K.

## Edge cases / traps

- K = 0: the array is already sorted, and the heap of size 1 just passes elements through.
- The window is K **+ 1**. Popping when the size reaches K is one too early and can output a
  wrong element.
- Duplicates are fine.
- If the input is not really K-sorted, the output is not sorted. Do not "fix" it, since the
  problem guarantees it.

## Variants they might ask

- **Check / count:** the minimum K for which the array is K-sorted is the maximum of
  |i − sortedPos(i)| (match duplicates in stable order).
- **Reverse K-sorted (descending):** use a max-heap.
- **Online / stream version:** print each popped value as soon as the heap exceeds K.

## Files

`sol.cpp` (STL min-heap of size K+1), `brute.cpp` (`std::sort`).
