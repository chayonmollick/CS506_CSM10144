# 07. Running median of a data stream

Source: Practice Set 3 Q14 (Heaps), LeetCode 295 "Find Median from Data Stream",
<https://leetcode.com/problems/find-median-from-data-stream/>. Exam-style variant with
stdin/stdout.

## Problem

Integers arrive one at a time. After each one, print the median of all integers received so
far.

**Median rule (stated):** if the count is odd, the median is the middle element of the sorted
list. If the count is even, it is the **average of the two middle elements**. Every median is
printed with **exactly one digit after the decimal point** (`5.0`, `3.5`, `-0.5`).

**Input.** Line 1: N (1 ≤ N ≤ 10^5). Line 2: N integers in [-10^9, 10^9].

**Output.** One line with N medians, space-separated.

**Sample Input**
```
6
5 2 8 -1 4 9
```
**Sample Output**
```
5.0 3.5 5.0 3.5 4.0 4.5
```

## Idea

Split the numbers into two halves:

- `lo`: a **max-heap** with the smaller half. Its top is the largest of the small numbers.
- `hi`: a **min-heap** with the larger half. Its top is the smallest of the large numbers.

Invariants: every key in `lo` is ≤ every key in `hi`, and `|lo| = |hi|` or `|lo| = |hi| + 1`.
Insert x into `lo` if x ≤ top(lo), otherwise into `hi`. Then move one top across if the sizes
broke the invariant. The median is top(lo) when the count is odd, and
(top(lo) + top(hi)) / 2 when it is even.

## Pseudocode

```
function ADD_NUMBER(lo, hi, x):          // lo = max-heap, hi = min-heap
    if lo is empty or x <= MAX(lo):
        INSERT(lo, x)
    else:
        INSERT(hi, x)
    if lo.size > hi.size + 1:
        INSERT(hi, EXTRACT_MAX(lo))
    else if hi.size > lo.size:
        INSERT(lo, EXTRACT_MIN(hi))

function MEDIAN(lo, hi):
    if lo.size > hi.size:
        return MAX(lo)
    return (MAX(lo) + MIN(hi)) / 2

main:
    read N
    for i = 1 to N:
        read x
        ADD_NUMBER(lo, hi, x)
        print MEDIAN(lo, hi) with 1 decimal
```

## Complexity

O(log n) per insertion and O(1) per median query. Total time is O(N log N) and space is O(N).
Re-sorting after every insertion would be O(N² log N).

## Edge cases / traps

- Add the two middles in `long long` (2 × 10^9 overflows `int`) and divide by **2.0**, not 2.
- Printing: `cout << fixed << setprecision(1)`. Values x.0 and x.5 are exact in a double, and
  `-0.5` prints correctly. Integer tricks such as `s/2` then ".5" give `0.5` instead of `-0.5`.
- With N = 1, `hi` is empty, so never read top(hi) when the count is odd.
- Duplicates: the `x <= MAX(lo)` tie goes to `lo`, and rebalancing keeps the invariant.

## Variants they might ask

- **Lower median as an integer** (for even counts print the smaller middle): print `lo.top()`
  every time. Upper median: keep `|hi| ≥ |lo|` and print `hi.top()`.
- **Floor of the average:** `twice / 2` with care for negatives (`floor`), or keep the double.
- **Median of a sliding window of size k:** needs deletion. Use two multisets, or two heaps
  with lazy deletion plus a hash map of pending deletes (LeetCode 480).
- **Print only the final median:** `nth_element` / sort once. The two heaps are needed only for
  the streaming version.

## Files

`sol.cpp` (two STL heaps), `sol_manual.cpp` (one hand-written `Heap` struct with an `isMax` flag,
used twice), `brute.cpp` (sort each prefix).
