# CS 506 — End-semester Lab Exam, Mock 1 (Heaps)

Time allotted: 2 hours | Max. marks 30 | C/C++ | STL allowed for I/O, strings and vectors

**Instructions**
1. For parts (a) and (b), write the pseudocode/logic first on the sheet provided (not needed for the common setup).
2. No internet, phones or smart devices.
3. One source file per part: `ENTRYNUMBER 1.cpp` for (a), `ENTRYNUMBER 2.cpp` for (b). Print only what is asked: no prompts, no labels.
4. Write the heap logic yourself; do not use `std::priority_queue`, `make_heap` or `push_heap` in this mock.

## Common setup (applies to both parts) [5 marks]
Implement a **1-indexed array-based binary min-heap**:
`MinHeap = { int a[]; int size; }`, with `MIN-HEAPIFY(H, i)`, `BUILD-MIN-HEAP(H)`,
`HEAP-INSERT(H, x)` and `HEAP-EXTRACT-MIN(H)`. Values are integers in [-10⁴, 10⁴] and may repeat.
Reuse the same struct and functions in both parts.

## (a) Build the heap, then the K smallest [10 marks]
Read N (1 ≤ N ≤ 10⁵), then N integers. Put them in the array in input order and call
**BUILD-MIN-HEAP** (bottom-up; not N insertions). Print the heap array `a[1..N]` on one line.
Then read k (1 ≤ k ≤ N) and print the k smallest values, obtained by calling
`HEAP-EXTRACT-MIN` k times, on one line.

Sample Input
```
10
4 1 3 2 16 9 10 14 8 7
4
```
Sample Output
```
1 2 3 4 7 9 10 14 8 16
1 2 3 4
```

## (b) Running median [15 marks]
Read N (1 ≤ N ≤ 10⁵), then N integers arriving one at a time. After each arrival print the
**median of all numbers seen so far**. With an even count, print the lower of the two middle
values. Print the N medians on one line. Use only your common-setup min-heap. A max-heap can be
simulated by storing −x. Each step must cost O(log N).

Sample Input
```
8
5 15 1 3 2 8 7 9
```
Sample Output
```
5 5 5 3 3 3 5 5
```
