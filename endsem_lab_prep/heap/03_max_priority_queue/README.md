# 03. Max-priority queue: INCREASE-KEY and EXTRACT-MAX

Source: Heap Sort slides 28–31 (HEAP-MAXIMUM, HEAP-EXTRACT-MAX, HEAP-INCREASE-KEY,
MAX-HEAP-INSERT; worked example "increase A[9] from 4 to 15").

## Problem

Build a max-heap from N integers with BUILD-MAX-HEAP (1-indexed, as in the lectures), then
process Q commands. Indices are positions in the heap array (A[1] is the root).

- `maximum`: print the maximum, or `EMPTY`.
- `extractMax`: remove the maximum and print it, or print `EMPTY` (heap underflow).
- `insert k`: MAX-HEAP-INSERT key k.
- `increaseKey i k`: HEAP-INCREASE-KEY(A, i, k). If i is not in [1, heap-size] or k < A[i],
  print `ERROR` and leave the heap unchanged. k = A[i] is allowed.
- `print`: print A[1..heap-size] space-separated, or `EMPTY`.

When both children beat the parent and are equal, MAX-HEAPIFY takes the **left** child (strict `>`).

**Input.** Line 1: N (0 ≤ N ≤ 10^5). Line 2: N integers. Line 3: Q (1 ≤ Q ≤ 10^5). Then Q
commands. Keys are in [-10^9, 10^9].

**Output.** One line per `maximum`, `extractMax`, `print` and failed `increaseKey`.

**Sample Input**
```
10
4 1 3 2 16 9 10 14 8 7
9
print
increaseKey 9 15
print
maximum
extractMax
print
increaseKey 3 5
insert 11
print
```
**Sample Output**
```
16 14 10 8 7 9 3 2 4 1
16 15 10 14 7 9 3 2 8 1
16
16
15 14 10 8 7 9 3 2 1
ERROR
15 14 10 8 11 9 3 2 1 7
```

## Idea

- EXTRACT-MAX moves the last leaf to the root. The tree keeps its shape, and only the root can
  violate the heap property, so one MAX-HEAPIFY(1) repairs it.
- INCREASE-KEY only makes a key **bigger**, so it can only beat its parent. Bubble it up.
- INSERT puts −∞ in a new leaf and raises it with INCREASE-KEY. In code you can store the key
  directly and bubble up, which gives the same result.

## Pseudocode

```
function HEAP_MAXIMUM(A):
    return A[1]

function HEAP_EXTRACT_MAX(A):
    if A.heap_size < 1:
        error "heap underflow"
    max = A[1]
    A[1] = A[A.heap_size]
    A.heap_size = A.heap_size - 1
    MAX_HEAPIFY(A, 1)
    return max

function HEAP_INCREASE_KEY(A, i, key):
    if i < 1 or i > A.heap_size or key < A[i]:
        error "new key is smaller than current key"
    A[i] = key
    while i > 1 and A[PARENT(i)] < A[i]:
        exchange A[i], A[PARENT(i)]
        i = PARENT(i)

function MAX_HEAP_INSERT(A, key):
    A.heap_size = A.heap_size + 1
    A[A.heap_size] = -infinity
    HEAP_INCREASE_KEY(A, A.heap_size, key)
```
MAX_HEAPIFY and BUILD_MAX_HEAP are as in `02_build_heap_heapsort`.

## Complexity

BUILD is O(N). MAXIMUM is O(1). EXTRACT-MAX, INCREASE-KEY and INSERT are O(log n) each.
Total time is O(N + Q log(N+Q)) and space is O(N+Q).

## Edge cases / traps

- Check i **before** reading A[i] in INCREASE-KEY. An out-of-range i must not touch memory.
- `extractMax` down to an empty heap, then `print`: prints `EMPTY`.
- With `-infinity` in INSERT, use `LLONG_MIN`, never `-1` or `0`. Keys can be negative.
- Indices refer to the **current** heap array. After any operation the same key may sit at a
  different index, so print the heap to see where it is.
- STL `priority_queue` cannot do INCREASE-KEY by position. This question needs the hand-written
  heap.

## Variants they might ask

- **Min-priority queue:** DECREASE-KEY and EXTRACT-MIN. Flip every key comparison and use
  +∞ in INSERT.
- **HEAP-DELETE(A, i):** INCREASE-KEY(A, i, +∞), then EXTRACT-MAX. Or move A[n] into slot i
  and run both bubble-up and heapify-down.
- **Change key in either direction:** set A[i] = key, then bubble up **and** MAX-HEAPIFY(i).
  Only one of them will move the key.
- **Keys are (priority, job-id)** (job scheduling): store pairs and compare priority, then id.

## Files

`sol.cpp` (vector), `sol_manual.cpp` (plain array, recursive heapify), `brute.cpp` (slides written
literally, INSERT through −∞).
