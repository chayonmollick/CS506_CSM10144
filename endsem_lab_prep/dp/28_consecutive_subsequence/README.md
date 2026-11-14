# 28. Consecutive Subsequence (hash map + DP)

Source: Practice Set 4 Q10 — [Codeforces 977F Consecutive Subsequence](https://codeforces.com/problemset/problem/977/F) (LIS variant).

## Problem

You are given an array `a[1..n]`. Find a longest subsequence (not necessarily contiguous, indices increasing) whose
values are `x, x+1, x+2, ..., x+k-1` for some integer `x` — i.e. each chosen value is exactly one more than the previous one.

Print its length `k` and the indices of one such subsequence. If several subsequences have the maximum length,
print the one whose **last element appears earliest** in the array; for that range of values choose the **leftmost
possible index** for each value in turn. (Codeforces accepts any answer; the exam fixes one so the output is unique.)

**Input**
Line 1: `n`. Line 2: `n` integers `a[1..n]`.

**Output**
Line 1: the maximum length `k`. Line 2: `k` increasing 1-based indices, space-separated.

**Constraints**
1 ≤ n ≤ 2·10^5, 1 ≤ a[i] ≤ 10^9

**Sample Input**
```
7
3 3 4 7 5 6 8
```

**Sample Output**
```
4
1 3 5 6
```

(Values 3 4 5 6. Indices `2 3 5 6` are also a longest answer, but the tie rule picks index 1 for the value 3.)

## Idea

- Subproblem: `len[v]` = length of the longest valid subsequence among the elements seen so far that **ends with value v**.
- Scanning left to right, `a[i]` can only extend a chain that ends with `a[i]-1` at an earlier index:
  `len[a[i]] = len[a[i]-1] + 1`, base case `len[v] = 0` if `v` was never seen (so a new chain starts with length 1).
- Values go up to 10^9, so `len` is a **hash map** (`unordered_map`) instead of an array — O(1) expected per step.
- Overwriting `len[a[i]]` is safe: `len[a[i]-1]` never decreases, so the new value is ≥ the old one.
- Track `best` and the end value `endVal`; update only when **strictly** greater, so the first (earliest) index that
  reaches the maximum length is kept.
- Reconstruction: the values are `endVal-best+1, ..., endVal`. Scan left to right and greedily take the first
  occurrence of the next needed value. Greedy leftmost matching always succeeds if any match exists, and it ends exactly
  at the earliest index that reached length `best`.

## Pseudocode

```
function LONGEST_CONSECUTIVE(a[1..n]):
    len = empty hash map            // value -> best chain length ending in that value
    best = 0, endVal = 0
    for i = 1 to n:
        prev = len[a[i] - 1] if present else 0
        len[a[i]] = prev + 1
        if len[a[i]] > best:
            best = len[a[i]]
            endVal = a[i]
    return (best, endVal)

function RECONSTRUCT(a[1..n], best, endVal):
    want = endVal - best + 1
    result = []
    for i = 1 to n:
        if size(result) == best: break
        if a[i] == want:
            result.append(i)
            want = want + 1
    return result

Main:
    read n, a[1..n]
    (best, endVal) = LONGEST_CONSECUTIVE(a)
    print best
    print RECONSTRUCT(a, best, endVal)   (space-separated)
```

## Complexity

O(n) expected time (hash map), O(n) space. With `std::map` it is O(n log n).

## Edge cases / traps

- Use `find(a[i]-1)` — writing `len[a[i]-1]` inside the lookup inserts junk keys (still correct, just slower).
- `n = 1`: answer is `1` and index `1`.
- Strictly decreasing array: every chain has length 1, answer is index 1.
- Duplicates: a later copy of `v` can have a longer chain than an earlier copy (in `5 4 5` the second `5` gets
  length 2), so always recompute from `len[v-1]`; never skip a value because it was seen before.
- This is **not** "longest run of consecutive values anywhere" (LeetCode 128): order matters here.
- Values up to 10^9: `a[i]-1` fits in `int`; do not use an array indexed by value.

## Variants they might ask

- **Only the length**: drop the reconstruction; it is just the `len` map.
- **Any difference d** (values `x, x+d, x+2d, ...`): look up `a[i]-d` instead of `a[i]-1`.
- **Contiguous (subarray) version**: reset — `cur = (a[i] == a[i-1]+1) ? cur+1 : 1`; no map needed.
- **Print the values instead of indices**: print `endVal-best+1 .. endVal`.
