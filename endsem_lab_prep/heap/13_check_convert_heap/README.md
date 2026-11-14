# 13. Check heap property, then convert a min-heap into a max-heap

Source: exam-style variant on the slides' heap property and BUILD-MAX-HEAP (GfG "Check if an
array represents a binary heap", "Convert min heap to max heap").

## Problem

Given an array A[1..N] (1-indexed, so the children of i are 2i and 2i+1):

1. Print whether it is a **max-heap**, where A[PARENT(i)] ≥ A[i] for every i > 1.
2. Print whether it is a **min-heap**, where A[PARENT(i)] ≤ A[i] for every i > 1.
3. Convert it into a max-heap with BUILD-MAX-HEAP exactly as in the lectures (`for i = N/2 downto
   1: MAX-HEAPIFY`, left child wins ties) and print the result. The input is typically a min-heap,
   but any array works.

**Input.** Line 1: N (1 ≤ N ≤ 10^5). Line 2: N integers in [-10^9, 10^9].

**Output.**
```
Max-heap: YES|NO
Min-heap: YES|NO
Converted: A[1] A[2] ... A[N]
```

**Sample Input**
```
7
1 3 2 7 4 5 6
```
**Sample Output**
```
Max-heap: NO
Min-heap: YES
Converted: 7 4 6 3 1 5 2
```

## Idea

- The heap property is local. If every parent-child pair is ordered, then by transitivity every
  ancestor-descendant pair is ordered too. One pass over i = 2..N comparing A[i/2] with A[i] is
  enough.
- Converting does **not** need anything special about min-heaps. BUILD-MAX-HEAP turns any array
  into a max-heap in O(N). Reversing a min-heap array is **not** a max-heap in general.

## Pseudocode

```
function IS_MAX_HEAP(A, n):
    for i = 2 to n:
        if A[i / 2] < A[i]:
            return false
    return true

function IS_MIN_HEAP(A, n):
    for i = 2 to n:
        if A[i / 2] > A[i]:
            return false
    return true

function CONVERT_TO_MAX_HEAP(A, n):    // = BUILD_MAX_HEAP
    for i = floor(n / 2) downto 1:
        MAX_HEAPIFY(A, i)
```

## Complexity

The checks are O(N). The conversion is O(N) (tight BUILD-HEAP bound). Extra space is O(1).

## Edge cases / traps

- N = 1, or all elements equal: both checks are YES, and the array is unchanged.
- With 0-indexed arrays the parent is (i−1)/2 and the children are 2i+1, 2i+2. Mixing the two
  conventions is the classic bug.
- A sorted ascending array is a min-heap. A sorted descending array is a max-heap. The converse
  is false.
- Recursive "check(i) = A[i] ≥ children && check(2i) && check(2i+1)" also works, but it is O(N)
  with recursion. The loop is simpler.

## Variants they might ask

- **0-indexed input:** loop i = 1..N−1 and compare A[(i−1)/2] with A[i].
- **Convert max-heap → min-heap:** BUILD-MIN-HEAP (flip the comparisons).
- **Check if a binary tree (pointer-based) is a heap:** it must be complete (BFS: no node after
  the first missing child) and have the heap order.
- **K-ary heap check:** the parent of i (1-indexed) is (i − 2) / k + 1.

## Files

`sol.cpp` (parent-child scan + BUILD-MAX-HEAP), `brute.cpp` (compares every node with all its
ancestors, literal recursive BUILD).
