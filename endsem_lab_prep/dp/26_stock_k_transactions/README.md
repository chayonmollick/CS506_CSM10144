# 26. Stock Trading with at most k Transactions

Source: Tutorial 9 Q16(b) (short version Q6b); same as [LeetCode 188 Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/).

## Problem

A trader knows the price `p[1..n]` of a commodity on each of `n` days. He may hold **at most one unit** at a time
and may make **at most k** buy–sell transactions (a transaction = one buy followed later by one sell). There is no
cooldown. Find the maximum profit.

**Input**
Line 1: two integers `n` and `k`. Line 2: `n` integers `p[1] .. p[n]`.

**Output**
A single integer: the maximum profit.

**Constraints**
1 ≤ n ≤ 1000, 0 ≤ k ≤ 100, 0 ≤ p[i] ≤ 1000

**Sample Input**
```
6 2
3 2 6 5 0 3
```

**Sample Output**
```
7
```

(Buy at 2, sell at 6 (+4); buy at 0, sell at 3 (+3).)

## Idea

- State machine with the transaction number in the state. After processing days `1..i`:
  - `buy[j]` = best profit while **holding** the unit of transaction `j`,
  - `sell[j]` = best profit after **completing** `j` transactions (holding nothing).
- Transitions for day `i`, for `j = 1..k`:
  - `buy[j]  = max(buy[j],  sell[j-1] - p[i])` — keep holding, or start transaction `j` today;
  - `sell[j] = max(sell[j], buy[j] + p[i])` — keep, or close transaction `j` today.
- Base: `sell[0..k] = 0` (no trades yet), `buy[1..k] = −∞` (nothing held).
- Answer: `sell[k]` ("at most k": `sell[j]` never decreases in `j`, because unused transactions cost nothing).
- Updating in place within a day is safe: it only adds "buy and sell on the same day" (profit 0) or
  "sell j-1 and buy j on the same day" (same as holding) — neither creates extra profit.
- Tutorial's table form (same thing): `T[j][i] = max(T[j][i-1], p[i] + max_{t<i}(T[j-1][t] - p[t]))`; keep the inner
  max as a running variable `best = max(best, T[j-1][i] - p[i])` → O(nk).

## Pseudocode

```
function MAX_PROFIT_K(p[1..n], k):
    for j = 0 to k:
        sell[j] = 0
        buy[j] = -INF
    for i = 1 to n:
        for j = 1 to k:
            buy[j]  = max(buy[j],  sell[j-1] - p[i])
            sell[j] = max(sell[j], buy[j] + p[i])
    return sell[k]

Main:
    read n, k, p[1..n]
    print MAX_PROFIT_K(p, k)
```

## Complexity

O(nk) time, O(k) space.

## Edge cases / traps

- k = 0 → 0 (the code handles it: the inner loop never runs, `sell[0] = 0`).
- `buy` must start at −∞, not 0 (0 would mean "holding a unit that cost nothing").
- Falling prices → 0: never forced to trade.
- If `k ≥ n/2`, the limit never binds: answer = sum of all positive rises `max(0, p[i+1] - p[i])`. Use this
  shortcut when k can be huge (e.g. k ≤ 10^9) to avoid an O(nk) blow-up.

## Variants they might ask

- **k = 1**: track the minimum price so far; answer `max(p[i] - minSoFar)`.
- **k = 2** (LeetCode 123): the same code with k = 2, i.e. four variables `buy1, sell1, buy2, sell2`.
- **Transaction fee f**: `sell[j] = max(sell[j], buy[j] + p[i] - f)`.
- **Print the trades**: keep 2-D tables `buy[i][j]`, `sell[i][j]` and walk back from `sell[n][k]`, noting on which days
  the "close" and "start" options were chosen.
