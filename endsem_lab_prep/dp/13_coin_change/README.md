# 13. Coin Change: Minimum Coins, Combinations, Sequences

Source: Tutorial 9 Q13 (count multisets vs sequences; "they differ only in the order of the two
loops ... Check with c = {1, 2, 5}, A = 5"); Coding Practice Set 4 Q5 (Coin Change).

## Problem

There are k coin denominations c_1, ..., c_k (unlimited supply of each) and an amount A.

- (a) Print the minimum number of coins whose values sum to A, or −1 if it is impossible.
- (b) Print the number of ways to make A when the order of coins does NOT matter
  (1+2+2 and 2+1+2 are the same way).
- (c) Print the number of ways to make A when the order DOES matter
  (1+2+2, 2+1+2 and 2+2+1 are different).

Print (b) and (c) modulo 1 000 000 007.

**Input**
- Line 1: k A
- Line 2: k distinct positive integers c_1 ... c_k

**Output**
- Three lines: the answers to (a), (b), (c)

**Constraints**: 1 ≤ k ≤ 100, 0 ≤ A ≤ 10^5, 1 ≤ c_i ≤ 10^5.

**Sample Input**
```
3 5
1 2 5
```

**Sample Output**
```
1
4
9
```

(Combinations: 5, 2+2+1, 2+1+1+1, 1+1+1+1+1. Sequences: 5, plus the 8 ordered sums of 1s and 2s.)

## Idea

- (a) mn[a] = fewest coins for amount a. mn[0] = 0; mn[a] = 1 + min over c_i ≤ a of mn[a − c_i]
  (∞ if no coin fits or all those are ∞). Same shape as rod cutting with min instead of max.
- (b) and (c) use the same update W[a] += W[a − c] with W[0] = 1 (one way to pay 0: no coins);
  only the loop order differs.
  - (b) COINS OUTER, amounts inner: after processing coins 1..i, W[a] = number of multisets
    using only coins 1..i. Every multiset is counted once, as "coins of type 1, then type 2, ...",
    because a coin of type i is only ever added after all smaller types are fixed.
  - (c) AMOUNT OUTER, coins inner: W[a] = Σ over coins c ≤ a of W[a − c], i.e. "which coin is
    LAST". Different last coins give different sequences, so every order is counted.
- Check A = 5, c = {1, 2, 5}: coins outer gives W = 1,1,2,2,3,4 (answer 4); amount outer gives
  1,1,2,3,5,9 (answer 9).
- Inner loop in (b) runs UPWARD so a coin can be reused (unbounded). Running it downward would
  give the 0/1 version (each coin at most once) — see problem 05.

## Pseudocode

```
function MIN-COINS(c, k, A):
    mn[0] = 0
    for a = 1 to A:
        mn[a] = infinity
        for i = 1 to k:
            if c[i] <= a and mn[a - c[i]] + 1 < mn[a]:
                mn[a] = mn[a - c[i]] + 1
    if mn[A] == infinity:
        return -1
    return mn[A]

function COUNT-COMBINATIONS(c, k, A):     // order does not matter
    W[0] = 1; W[1..A] = 0
    for i = 1 to k:                        // coins OUTER
        for a = c[i] to A:                 // upward: reuse allowed
            W[a] = W[a] + W[a - c[i]]
    return W[A]

function COUNT-SEQUENCES(c, k, A):        // order matters
    W[0] = 1; W[1..A] = 0
    for a = 1 to A:                        // amount OUTER
        for i = 1 to k:
            if c[i] <= a:
                W[a] = W[a] + W[a - c[i]]
    return W[A]
```

## Complexity

O(k·A) time for each part, O(A) space. Pseudo-polynomial (A is a number, not an input length).

## Edge cases / traps

- A = 0: answers 0, 1, 1 (the empty selection).
- Impossible amount: −1, 0, 0 — never print INF; keep INF small enough that INF + 1 does not
  overflow (here 10^9 in an `int`).
- Counts grow exponentially: take the modulo inside the loop, use `long long`.
- Greedy (largest coin first) fails for (a): c = {1, 3, 4}, A = 6 gives 4+1+1 = 3 coins, optimum
  3+3 = 2 coins.
- Swapping the loop order silently changes (b) into (c) — the classic bug.

## Variants they might ask

- Print the coins of an optimal (a): store last[a] = the coin that improved mn[a]; walk
  a = A, A − last[A], ... .
- Each coin at most once (0/1 count): coins outer, amount loop DOWNWARD from A to c[i].
- Fewest coins with a limited count of each coin: bounded knapsack — add a loop over how many
  copies (or split counts into powers of two).
- Count ways to climb n stairs with steps {1, 2}: exactly (c) with c = {1, 2}.
