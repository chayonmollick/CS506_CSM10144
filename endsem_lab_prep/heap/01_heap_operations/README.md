# 01. Min-heap operations by command

Source: exam-style common setup, the min-heap counterpart of the slides' priority-queue operations
(Heap Sort slides 28–30). Simplified from Practice Set 3 Q6 (Codeforces 681C, see `04_`).

## Problem

Implement an array-based binary **min-heap** with INSERT, GET-MIN and EXTRACT-MIN, then process
a list of commands.

- `insert x`: insert integer x.
- `getMin`: print the minimum, or `EMPTY` if the heap is empty.
- `removeMin`: remove the minimum and print it, or print `EMPTY` if the heap is empty.
- `size`: print the number of elements.

After all commands, print the remaining elements in ascending order on one line by repeatedly
extracting the minimum, or `EMPTY` if none remain.

**Input.** Line 1: Q (1 ≤ Q ≤ 10^5). Next Q lines: one command each. -10^9 ≤ x ≤ 10^9 and
duplicates are allowed.

**Output.** One line per `getMin` / `removeMin` / `size`, then the final line.

**Sample Input**
```
11
getMin
insert 5
insert 3
insert 8
getMin
removeMin
getMin
insert -2
size
removeMin
removeMin
```
**Sample Output**
```
EMPTY
3
3
5
3
-2
5
8
```

## Idea

The minimum is always the root A[1]. Insert appends at A[n+1] and bubbles up. Extract moves
the last leaf to the root and floats it down with MIN-HEAPIFY. Draining the heap with repeated
extract-min gives the remaining keys in ascending order, which is heapsort with a min-heap.

## Pseudocode

```
function MIN_HEAPIFY(A, i):
    l = 2i, r = 2i + 1, smallest = i
    if l <= A.n and A[l] < A[smallest]: smallest = l
    if r <= A.n and A[r] < A[smallest]: smallest = r
    if smallest != i:
        exchange A[i], A[smallest]
        MIN_HEAPIFY(A, smallest)

function INSERT(A, x):
    A.n = A.n + 1
    A[A.n] = x
    i = A.n
    while i > 1 and A[i / 2] > A[i]:
        exchange A[i], A[i / 2]
        i = i / 2

function EXTRACT_MIN(A):
    min = A[1]
    A[1] = A[A.n]
    A.n = A.n - 1
    MIN_HEAPIFY(A, 1)
    return min

main:
    read Q
    repeat Q times:
        read op
        if op == "insert": read x; INSERT(A, x)
        if op == "getMin": print A[1], or EMPTY if A.n == 0
        if op == "removeMin": print EXTRACT_MIN(A), or EMPTY if A.n == 0
        if op == "size": print A.n
    if A.n == 0: print EMPTY
    while A.n > 0: print EXTRACT_MIN(A)      // on one line
```

## Complexity

INSERT and EXTRACT-MIN take O(log n), GET-MIN and SIZE take O(1). Total time is
O(Q log Q) and extra space is O(Q).

## Edge cases / traps

- `getMin` / `removeMin` on an empty heap must print `EMPTY` and must not touch A[0] or A[-1].
- Duplicates: compare with strict `<` / `>`. Equal keys are fine either way.
- Use `long long` if keys may reach ±10^9 and are ever added together.
- In `sol_manual.cpp` the heap array is global (`A[MAXN]`), so a large Q does not overflow
  the stack.

## Variants they might ask

- **Max-heap:** flip every key comparison, or in STL drop `greater<>`:
  `priority_queue<long long> pq;`.
- **Print the heap array after each command:** only the hand-written version can do this
  (see `templates/heap_manual`). The STL queue cannot be iterated.
- **Build from an initial array:** read N keys, then run `for i = n/2 downto 1: MIN_HEAPIFY`
  (O(n)) instead of N inserts.
- **`removeMin` silently:** drop the print in that branch.

## Files

`sol.cpp` (STL `priority_queue`), `sol_manual.cpp` (hand-written array heap),
`brute.cpp` (linear scan).
