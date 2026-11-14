# 11. Longest Consecutive Sequence

Source: LeetCode 128 (classic hash-set problem; fits the Tutorial 8 Part B "O(n) expected time" style).

## Problem

Given an unsorted array of n integers (duplicates and negatives allowed), find the longest set of
values x, x+1, ..., x+L−1 that all appear in the array (positions do not matter). Print L and then the
values in increasing order. If several sequences have the maximum length, print the one with the
smallest starting value. The algorithm must run in O(n) expected time (no sorting).

**Input**
Line 1: n. Line 2: n integers.

**Output**
Line 1: L. Line 2: the L values separated by spaces.

**Constraints**
1 ≤ n ≤ 10^5, −10^9 ≤ a[i] ≤ 10^9.

**Sample Input**
```
6
100 4 200 1 3 2
```

**Sample Output**
```
4
1 2 3 4
```

## Idea

Put all values in a hash set. A value x **starts** a run exactly when x − 1 is not in the set. Only
from such starts, walk x+1, x+2, ... while they are in the set. Every value is visited by at most one
walk (the walk of its run's start), so the total work is O(n) expected even though there is a loop
inside a loop. Iterate over **distinct** values: with duplicates of a start value the same run would
be walked many times.

## Pseudocode

```
function LONGEST_CONSECUTIVE(a[0..n-1]):
    S = empty hash set
    for i = 0 to n-1: HASH_INSERT(S, a[i])          // duplicates ignored
    bestLen = 0, bestStart = 0
    for each distinct x in S:
        if (x - 1) in S: continue                    // not the start of a run
        y = x
        while (y + 1) in S: y = y + 1
        len = y - x + 1
        if len > bestLen or (len == bestLen and x < bestStart):
            bestLen = len, bestStart = x
    print bestLen
    print bestStart, bestStart+1, ..., bestStart+bestLen-1
```

## Complexity

O(n) expected time: n inserts, and each distinct value is checked as x − 1 once and walked over at
most once. O(n) space. Sorting (`brute.cpp`) gives O(n log n), which the question forbids.

## Edge cases / traps

- Duplicates: `5 5 5 5 5` → 1 (tests/3); `0 ... 0 1 ...` must not count 0 twice (tests/4).
- Without the "x − 1 not in S" check the walks cost O(n²) (e.g. 1..n in any order).
- Iterating over the input array instead of the distinct values: 50 000 copies of the start value
  each walk a run of 50 000 (tests/8). `sol_manual.cpp` stores the distinct values separately.
- `y + 1` at 10^9: fine in `long long`; with `int` close to INT_MAX it overflows.
- Negative values in your own hash table: `((k % M) + M) % M` (tests/5, tests/6).
- Unordered iteration order: break ties explicitly (smallest start).

## Variants they might ask

- **Length only**: print `bestLen`.
- **Longest run of consecutive values that are also consecutive positions** (a subarray): different
  problem, a single linear scan.
- **Number of runs / all runs**: count starts (values with x − 1 absent) and print each walk.
- **Longest arithmetic run with step d**: replace ±1 with ±d.

## Files

`sol.cpp` (`unordered_set`), `sol_manual.cpp` (own chained hash set, M = 100003), `brute.cpp`
(sort + unique + scan). 800 random inputs agree; tests 7–8 have n = 10^5.
