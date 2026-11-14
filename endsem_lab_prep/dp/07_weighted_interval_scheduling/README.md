# 07. Weighted Interval Scheduling (max value + chosen requests)

Source: DP slides, "Weighted Interval Scheduling" (p(i), COMPUTE-OPT, M-COMPUTE-OPT,
ITERATIVE-COMPUTE-OPT, FIND-SOLUTION; six-request worked example, OPT = 11 with {R1, R3}).
The slides give only p(i) and the values, so the start/finish times below were made up to
match them.

## Problem

One resource receives n requests; request i occupies the half-open time interval [s_i, f_i) and
pays v_i. Two requests are compatible if they do not overlap (one may start exactly when the
other finishes). Choose a set of pairwise compatible requests with maximum total value.

Number the requests 1..n in input order. To make the chosen set unique: sort the requests by
finish time (ties by input index), run FIND-SOLUTION, which takes request i whenever
v_i + M[p(i)] ≥ M[i−1], and print the original indices of the chosen requests in increasing order.

**Input**
- Line 1: n
- Next n lines: s_i f_i v_i

**Output**
- Line 1: the maximum total value
- Line 2: the chosen request indices (input numbering, increasing), space-separated

**Constraints**: 1 ≤ n ≤ 10^5, 0 ≤ s_i < f_i ≤ 10^9, 1 ≤ v_i ≤ 10^9 (use `long long`).

**Sample Input**
```
6
0 3 4
2 5 4
4 7 7
1 8 2
5 9 2
3 10 1
```

**Sample Output**
```
11
1 3
```

## Idea

- Sort by finish time so that f_1 ≤ f_2 ≤ ... ≤ f_n. p(i) = largest j < i with f_j ≤ s_i
  (0 if none): the requests compatible with i that come before it are exactly 1..p(i).
  Sorted finishes make this a binary search (`upper_bound(f_1..f_{i−1}, s_i)`).
- Subproblem: M[i] = best value using only requests 1..i.
- Recurrence: M[0] = 0; M[i] = max(M[i−1] (i out), v_i + M[p(i)] (i in)).
- Fill order: i = 1..n (both i − 1 and p(i) are smaller).
- Reconstruction (FIND-SOLUTION): from i = n, if v_i + M[p(i)] ≥ M[i−1] take i and jump to
  p(i), otherwise go to i − 1. Store the original index before sorting so you can print it.

## Pseudocode

```
function COMPUTE-P(f, s, n):            // requests already sorted by finish time
    for i = 1 to n:
        lo = 1, hi = i - 1, p[i] = 0
        while lo <= hi:                  // last j with f[j] <= s[i]
            mid = (lo + hi) / 2
            if f[mid] <= s[i]:
                p[i] = mid; lo = mid + 1
            else:
                hi = mid - 1
    return p

function ITERATIVE-COMPUTE-OPT(v, p, n):
    M[0] = 0
    for i = 1 to n:
        M[i] = max(M[i-1], v[i] + M[p[i]])
    return M

function FIND-SOLUTION(i):
    while i > 0:
        if v[i] + M[p[i]] >= M[i-1]:
            output i                     // request i is in the solution
            i = p[i]
        else:
            i = i - 1
```

## Complexity

O(n log n): sorting and the n binary searches; the DP and the traceback are O(n).
The plain recursion COMPUTE-OPT is exponential (Fibonacci-like when p(i) = i − 2).

## Edge cases / traps

- Touching intervals (f_j = s_i) are compatible: search with `<=` / `upper_bound`, not
  `lower_bound`. Using `<` changes the answer on test 5.
- p(i) is an index in the SORTED order; printing it directly prints the wrong request — keep the
  original id in the struct (test 3 feeds the sample in shuffled order).
- Earliest-finish greedy is optimal only without weights (test 6: greedy gets 6, optimum 10).
- Totals reach 10^5 · 10^9: `long long` for v and M.
- Identical intervals: only one can be taken (test 4).

## Variants they might ask

- Unweighted (maximum number of requests): set every v_i = 1, or just use the greedy.
- Memoized version: M-COMPUTE-OPT(i) with M[] initialised to −1.
- Closed intervals [s, f] (touching NOT allowed): p(i) = last j with f_j < s_i → use
  `lower_bound` instead of `upper_bound`.
- Maximum value with at most k requests: add a second index, M[i][c] = max(M[i−1][c],
  v_i + M[p(i)][c−1]).
