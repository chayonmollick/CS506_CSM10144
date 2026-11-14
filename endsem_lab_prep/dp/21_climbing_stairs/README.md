# 21. Climbing Stairs (1/2 steps, and 1..k steps)

Source: Practice Set 4 Q1 — [LeetCode 70 Climbing Stairs](https://leetcode.com/problems/climbing-stairs/); the 1..k part is an exam-style variant.

## Problem

A staircase has `n` steps. You start at the bottom (step 0) and want to stand exactly on step `n`.

(a) In one move you climb either 1 or 2 steps. Count the number of distinct move sequences.
(b) In one move you climb any number of steps from 1 to `k`. Count the number of distinct move sequences.

Two sequences are different if they differ in at least one move (order matters: 1+2 and 2+1 are different).
Print both counts modulo 1000000007.

**Input**
One line with two integers `n` and `k`.

**Output**
Line 1: the answer to (a). Line 2: the answer to (b). Both modulo 1000000007.

**Constraints**
1 ≤ n ≤ 10^5, 1 ≤ k ≤ 100

**Sample Input**
```
5 3
```

**Sample Output**
```
8
13
```

(For n = 5 with 1/2 steps: 1+1+1+1+1, 2+1+1+1 (4 orders), 2+2+1 (3 orders) = 8.)

## Idea

- Subproblem: `ways[i]` = number of move sequences that end exactly on step `i`.
- Look at the **last move**. For (a) it was a 1-step (from `i-1`) or a 2-step (from `i-2`), so
  `ways[i] = ways[i-1] + ways[i-2]` — Fibonacci, `ways[n] = Fib(n+1)`.
- For (b) the last move was `s` for some `1 ≤ s ≤ min(k, i)`, so `ways[i] = Σ ways[i-s]`.
- Base case: `ways[0] = 1` (the empty sequence). For (a) also `ways[1] = 1`.
- Fill order: `i = 1, 2, ..., n` (each entry needs only smaller indices).
- (a) needs only the last two values, so it runs in O(1) space.

## Pseudocode

```
function CLIMB_12(n):
    prev2 = 1, prev1 = 1              // ways[0], ways[1]
    for i = 2 to n:
        cur = (prev1 + prev2) mod M
        prev2 = prev1
        prev1 = cur
    return prev1

function CLIMB_K(n, k):
    ways[0..n] = 0
    ways[0] = 1
    for i = 1 to n:
        for s = 1 to min(k, i):
            ways[i] = (ways[i] + ways[i - s]) mod M
    return ways[n]

Main:
    read n, k
    print CLIMB_12(n)
    print CLIMB_K(n, k)
```

## Complexity

(a) O(n) time, O(1) space. (b) O(nk) time, O(n) space (O(n) time with a sliding window sum, see variants).

## Edge cases / traps

- `ways[0] = 1`, not 0 — the empty sequence is what makes `ways[1] = 1` and `ways[2] = 2` come out right.
- Without the modulus the answer overflows `long long` after n = 91 (and `int` after n = 45).
- `k > i`: the inner loop must stop at `s = i` (no negative index).
- Take `% M` after every addition, not only at the end.

## Variants they might ask

- **No modulus, n ≤ 45**: same code with `int`/`long long` and no `% M` (LeetCode's original).
- **Allowed step sizes from a set S** (e.g. {1, 3, 5}): inner loop over `s in S` with `s ≤ i` — this is "coin change, order matters" (Tutorial 9 Q13b).
- **O(n) for large k**: keep `window = ways[i-1] + ... + ways[i-k]`; `ways[i] = window`, then add `ways[i]` and subtract `ways[i-k]` (if `i-k ≥ 0`).
- **Broken steps** (some steps cannot be stood on): set `ways[i] = 0` for those `i` right after computing it.
