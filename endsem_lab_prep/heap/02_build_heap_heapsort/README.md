# 02. BUILD-MAX-HEAP and HEAPSORT

Source: Heap Sort slides (MAX-HEAPIFY, BUILD-MAX-HEAP, HEAPSORT; worked example
A = [4, 1, 3, 2, 16, 9, 10, 14, 8, 7]).

## Problem

Given an array A[1..N], run BUILD-MAX-HEAP using MAX-HEAPIFY exactly as in the lectures
(1-indexed, `for i = floor(N/2) downto 1`; when both children beat A[i] and are equal, the
**left** child wins). Print the array after BUILD-MAX-HEAP. Then sort it in place with HEAPSORT
and print the sorted array.

**Input.** Line 1: N (1 ≤ N ≤ 10^5). Line 2: N integers in [-10^9, 10^9], duplicates allowed.

**Output.** Line 1: `Max-heap:` followed by the N values after BUILD-MAX-HEAP.
Line 2: `Sorted:` followed by the N values in ascending order. Values are separated by single
spaces.

**Sample Input**
```
10
4 1 3 2 16 9 10 14 8 7
```
**Sample Output**
```
Max-heap: 16 14 10 8 7 9 3 2 4 1
Sorted: 1 2 3 4 7 8 9 10 14 16
```

## Idea

Indices above N/2 are leaves, which are already 1-element heaps. Going from N/2 down to 1, each
MAX-HEAPIFY(i) sees two children that are already max-heaps, so floating A[i] down fixes the
subtree. HEAPSORT then swaps the root (the max) into the last live slot, shrinks heap-size and
re-heapifies the root, N−1 times.

## Pseudocode

```
function MAX_HEAPIFY(A, i):
    l = 2i
    r = 2i + 1
    largest = i
    if l <= A.heap_size and A[l] > A[largest]:
        largest = l
    if r <= A.heap_size and A[r] > A[largest]:
        largest = r
    if largest != i:
        exchange A[i], A[largest]
        MAX_HEAPIFY(A, largest)

function BUILD_MAX_HEAP(A, n):
    A.heap_size = n
    for i = floor(n / 2) downto 1:
        MAX_HEAPIFY(A, i)

function HEAPSORT(A, n):
    BUILD_MAX_HEAP(A, n)
    for i = n downto 2:
        exchange A[1], A[i]
        A.heap_size = A.heap_size - 1
        MAX_HEAPIFY(A, 1)

main:
    read n, A[1..n]
    BUILD_MAX_HEAP(A, n);  print "Max-heap:", A[1..n]
    HEAPSORT(A, n);        print "Sorted:", A[1..n]
```

## Complexity

MAX-HEAPIFY is O(log n), since T(n) ≤ T(2n/3) + Θ(1). BUILD-MAX-HEAP is **O(n)**: the tight
bound comes from Σ h·n/2^(h+1) = O(n), and O(n log n) is only the loose bound. HEAPSORT is
O(n log n) in every case, in place with O(1) extra space, and **not stable**.

## Edge cases / traps

- N = 1: the loop `n/2 downto 1` runs zero times, and both lines print the single value.
- Do not use `std::make_heap` when the heap array is printed. With duplicate keys libstdc++
  (g++) can give a different, still valid layout. Example: `0 1 0 2 3 3` gives CLRS `3 2 3 0 1 0`
  but g++ `make_heap` gives `3 3 0 2 1 0`. The TA will compare with the CLRS layout.
- The tie rule matters with duplicates. Use strict `>`, check the left child first, and swap
  only if a child is strictly larger.
- Recursion depth is only log n, so recursive MAX-HEAPIFY is safe.
- The loop must go **downwards**. Heapifying i = 1..n/2 upwards does not give a heap in general.

## Variants they might ask

- **Min-heap / descending sort:** flip `>` to `<` (MIN-HEAPIFY). Heapsort with a min-heap
  sorts in descending order.
- **Print the array after every MAX-HEAPIFY call in BUILD** (the slide trace): add `printLine`
  inside the build loop.
- **Print the array after each heapsort round:** print inside the heapsort loop. The slides show
  round 1 = `14 8 10 4 7 9 3 2 1 16`.
- **Count swaps / comparisons:** increment a global counter at each exchange.

## Files

`sol.cpp` (vector, iterative heapify), `sol_manual.cpp` (plain array, recursive heapify as on the
slides), `brute.cpp` (literal BUILD-MAX-HEAP plus `std::sort`).
