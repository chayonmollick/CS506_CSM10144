# 11. Longest Increasing Subsequence (O(n log n) + one LIS)

Source: Tutorial 9 Q4 (a) O(n^2) and (b) O(n log n) with T[ℓ] = smallest last element of an
increasing subsequence of length ℓ; Coding Practice Set 4 Q10 is an LIS variant.

## Problem

Given an array a_1, ..., a_n, find the length of its longest strictly increasing subsequence and
print one such subsequence.

If several longest increasing subsequences exist, print the one whose last element is as far
right in the array as possible; among those, the one whose second-to-last element is as far right
as possible, and so on. (This is exactly what the tails + parent-pointer method below produces.)

**Input**
- Line 1: n
- Line 2: n integers a_1 ... a_n

**Output**
- Line 1: the length L
- Line 2: the L values of the subsequence, space-separated

**Constraints**: 1 ≤ n ≤ 10^5, |a_i| ≤ 10^9.

**Sample Input**
```
8
10 9 2 5 3 7 101 18
```

**Sample Output**
```
4
2 3 7 18
```

## Idea

O(n^2) DP (part (a), easy to write, fine for n ≤ 5000):
- L[i] = length of the longest increasing subsequence ENDING at i.
- L[i] = 1 + max{ L[j] : j < i, a[j] < a[i] } (1 if there is no such j); answer max L[i].
- Keep prev[i] = the j that gave the max and walk back from the best i.

O(n log n) (part (b), what sol.cpp does):
- tails[ℓ] = the smallest possible last value of an increasing subsequence of length ℓ + 1 seen so
  far. tails is strictly increasing (proof: a length-(ℓ+1) subsequence contains a length-ℓ one
  with a smaller last value), so we can binary-search it.
- For each a[i]: pos = first index with tails[pos] ≥ a[i] (lower_bound). a[i] extends the
  subsequence of length pos, so it becomes the new best tail of length pos + 1 (replace or append).
- Reconstruction: tails holds values, not a real subsequence. Keep tailIdx[pos] = index of that
  tail, and parent[i] = tailIdx[pos − 1] at the moment a[i] is placed. Walk parent[] back from
  tailIdx[L − 1] and reverse.

## Pseudocode

```
function LIS-QUADRATIC(a, n):
    best = 0
    for i = 1 to n:
        L[i] = 1; prev[i] = 0
        for j = 1 to i - 1:
            if a[j] < a[i] and L[j] + 1 > L[i]:
                L[i] = L[j] + 1; prev[i] = j
        best = max(best, L[i])
    return best

function LIS-FAST(a, n):
    len = 0
    for i = 1 to n:
        pos = LOWER-BOUND(tails[1..len], a[i])   // first position with tails[pos] >= a[i]
        tails[pos] = a[i]
        tailIdx[pos] = i
        if pos > 1:
            parent[i] = tailIdx[pos - 1]
        else:
            parent[i] = 0
        if pos == len + 1:
            len = len + 1
    i = tailIdx[len]
    while i != 0:                                  // collects the LIS backwards
        output a[i]
        i = parent[i]
    return len
```

## Complexity

O(n log n) time, O(n) space. The O(n^2) version is O(n^2) time.

## Edge cases / traps

- Strictly increasing needs `lower_bound`; using `upper_bound` would allow equal values.
- All equal / strictly decreasing input: L = 1.
- `tails` is NOT an LIS in general. In the sample it happens to end as 2 3 7 18, but for
  3 1 4 1 5 9 2 6 5 it ends as 1 2 5 6 (6 comes before the last 5 — not a subsequence), while the
  printed LIS is 1 4 5 6. Always reconstruct with parent pointers.
- The answer must be printed in left-to-right order: reverse after the parent walk.

## Variants they might ask

- Longest non-decreasing subsequence: replace `lower_bound` with `upper_bound`.
- Longest decreasing subsequence: negate all values (or use `greater<long long>()`).
- Only the length: drop tailIdx and parent (5 lines of code).
- Number of LIS / LIS with weights (maximum-sum increasing subsequence): use the O(n^2) DP with
  sum[i] = a[i] + max sum[j] over j < i, a[j] < a[i].
