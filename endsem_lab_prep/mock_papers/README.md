# Mock papers

Four 2-hour papers in the format of the CS506 mid-semester lab exam: a common setup (5 marks),
then (a) (10 marks) and (b) (15 marks). The real paper has 2 questions from DP, hashing and heaps,
so any two of these make a realistic rehearsal.

| Mock | Common setup | (a) | (b) |
|---|---|---|---|
| [`mock1_heap`](mock1_heap/PAPER.md) | Hand-written 1-indexed min-heap | BUILD-MIN-HEAP array + k smallest | Running median with two heaps |
| [`mock2_hashing`](mock2_hashing/PAPER.md) | Hand-written chained hash table (negative keys, insert at head) | I / D / S commands, print the chains | Longest subarray with sum K (prefix sum → first index) |
| [`mock3_dp_strings`](mock3_dp_strings/PAPER.md) | LCS-LENGTH table | LCS length + PRINT-LCS (ties go up) | Shortest common supersequence from the same table |
| [`mock4_dp_vs_heap`](mock4_dp_vs_heap/PAPER.md) | Read a cost grid | Right/down min path + alphabetically smallest path (DP from the end) | 4-direction min path (Dijkstra with a priority queue) |

How to use them:
1. Open only `PAPER.md`, and write the pseudocode on paper first.
2. Code in a fresh file and test with the sample.
3. Check your program against the official tests: `./mine < a/tests/2.in | diff - a/tests/2.out`, for every test.
4. Read `SOLUTION.md` for the pseudocode in course format, and compare with `a/sol.cpp` and `b/sol.cpp`.

Each part has `brute.cpp`, a slow but obviously correct version, for checking on your own inputs.
Every `sol.cpp` was compared against its brute force on 400–500 random inputs.
