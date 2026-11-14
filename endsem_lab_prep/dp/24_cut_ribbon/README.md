# 24. Cut Ribbon

Source: Practice Set 4 Q4 — [Codeforces 189A Cut Ribbon](https://codeforces.com/problemset/problem/189/A)
(exam-style change: print -1 when no cutting exists; Codeforces guarantees one exists).

## Problem

A ribbon has length `n`. Cut it into pieces so that every piece has length exactly `a`, `b` or `c`
(the whole ribbon must be used). Find the **maximum number of pieces**. If the ribbon cannot be cut this way,
print -1.

**Input**
One line with four integers `n a b c`.

**Output**
A single integer: the maximum number of pieces, or -1 if impossible.

**Constraints**
1 ≤ n, a, b, c ≤ 4000 (a, b, c need not be distinct)

**Sample Input**
```
5 5 3 2
```

**Sample Output**
```
2
```

(5 = 3 + 2 gives 2 pieces; 5 = 5 gives only 1.)

## Idea

- This is an **unbounded knapsack / coin change with "maximise count"**: lengths are coins, each usable any number of times.
- Subproblem: `dp[x]` = maximum number of pieces that make length **exactly** `x`, or −∞ if impossible.
- Look at the last piece: `dp[x] = 1 + max(dp[x-a], dp[x-b], dp[x-c])` over the terms with `x - len ≥ 0` and
  `dp[x - len] ≠ −∞`.
- Base case: `dp[0] = 0`; every other entry starts at −∞.
- Fill order: `x = 1..n`. Answer `dp[n]`, printed as -1 if it is still −∞.

## Pseudocode

```
function MAX_PIECES(n, a, b, c):
    dp[0] = 0
    for x = 1 to n:
        dp[x] = -INF
        for len in {a, b, c}:
            if x >= len and dp[x - len] != -INF:
                dp[x] = max(dp[x], dp[x - len] + 1)
    if dp[n] == -INF:
        return -1
    return dp[n]

Main:
    read n, a, b, c
    print MAX_PIECES(n, a, b, c)
```

## Complexity

O(3n) = O(n) time, O(n) space.

## Edge cases / traps

- **Initialise to −∞, not 0.** With 0, `dp[x] = dp[x-len] + 1` builds on impossible lengths
  (e.g. n = 7, lengths 2 4 6 would wrongly print a positive number; the answer is -1).
- Check `dp[x-len] != -INF` before adding 1 (or use a −∞ so negative that +1 cannot make it look valid).
- Greedy "use the smallest piece as often as possible" fails: `7 5 5 2` → 2 (5 + 2), not 3 (2+2+2 leaves 1).
- An O(n²) solution (loop over the counts of `a` and `b`, the rest must be a multiple of `c`) also passes for
  n ≤ 4000 — that is `brute.cpp`.

## Variants they might ask

- **Minimum number of pieces** (= coin change, min coins): `min` instead of `max`, +∞ instead of −∞.
- **Number of ways** (order does not matter): outer loop over the lengths, inner loop over `x`,
  `ways[x] += ways[x - len]` (Tutorial 9 Q13a); swap the loops to count ordered sequences (Q13b).
- **Arbitrary list of k lengths**: loop over the list instead of `{a, b, c}`, O(nk).
- **Each length usable at most once**: 0/1 knapsack, run `x` downwards from n.
