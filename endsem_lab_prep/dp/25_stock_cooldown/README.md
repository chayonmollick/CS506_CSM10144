# 25. Stock Trading with Cooldown (hold / sold / rest)

Source: Practice Set 4 Q8 — [LeetCode 309 Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/);
Tutorial 9 Q16(a) (short version Q6a).

## Problem

A trader knows the price `p[1..n]` of a commodity on each of `n` days. He may hold **at most one unit** at a time
(buy, later sell, then buy again, ...). After a sell he must wait one day (**cooldown**): if he sells on day `i`
he cannot buy on day `i+1`. He may do as many transactions as he likes, or none. Find the maximum profit.

**Input**
Line 1: integer `n`. Line 2: `n` integers `p[1] .. p[n]`.

**Output**
A single integer: the maximum profit.

**Constraints**
1 ≤ n ≤ 10^5, 0 ≤ p[i] ≤ 10^4

**Sample Input**
```
5
1 2 3 0 2
```

**Sample Output**
```
3
```

(Buy at 1, sell at 2, cooldown on the day with price 3, buy at 0, sell at 2: 1 + 2 = 3.)

## Idea

Model each day's end as one of three states:

| state | meaning at the end of day i | how we get there |
|---|---|---|
| `hold[i]` | owns one unit | keep holding (`hold[i-1]`), or buy today from `rest[i-1]` (not from `sold` — cooldown) |
| `sold[i]` | sold today | `hold[i-1] + p[i]` |
| `rest[i]` | owns nothing, did not sell today | stay idle (`rest[i-1]`), or yesterday was a sale (`sold[i-1]`) |

- `hold[i] = max(hold[i-1], rest[i-1] - p[i])`
- `sold[i] = hold[i-1] + p[i]`
- `rest[i] = max(rest[i-1], sold[i-1])`
- Base (day 1): `hold = -p[1]`, `sold = -∞` (nothing to sell yet), `rest = 0`.
- Answer: `max(sold[n], rest[n])` (ending with a unit in hand is never better).
- Each day uses only the previous day → three variables. Update all three from the **old** values.

Tutorial check, p = (1, 2, 3, 0, 2):

| day | price | hold | sold | rest |
|---|---|---|---|---|
| 1 | 1 | -1 | -∞ | 0 |
| 2 | 2 | -1 | 1 | 0 |
| 3 | 3 | -1 | 2 | 1 |
| 4 | 0 | 1 | -1 | 2 |
| 5 | 2 | 1 | **3** | 2 |

Answer `max(3, 2) = 3`. Reconstruction: remember which option won in each state (or walk the table back).

## Pseudocode

```
function MAX_PROFIT_COOLDOWN(p[1..n]):
    hold = -p[1], sold = -INF, rest = 0
    for i = 2 to n:
        h = max(hold, rest - p[i])
        s = hold + p[i]
        r = max(rest, sold)
        hold = h, sold = s, rest = r
    return max(sold, rest)

Main:
    read n, p[1..n]
    print MAX_PROFIT_COOLDOWN(p)
```

## Complexity

O(n) time, O(1) space.

## Edge cases / traps

- Buying is allowed only from `rest`, never directly from `sold` — that is exactly the cooldown.
- Do not overwrite `hold` before computing `sold` from it: use temporaries (`h, s, r`) as in the code.
- `sold` on day 1 must be −∞ (or at least not positive); `rest = 0` covers "never trade".
- n = 1 or falling prices: answer 0.

## Variants they might ask

- **No cooldown, unlimited transactions**: `hold = max(hold, sold_or_rest - p)`, i.e. buy from the same
  "not holding" state; answer = sum of all positive day-to-day rises.
- **Transaction fee f**: `sold[i] = hold[i-1] + p[i] - f`, everything else unchanged.
- **Cooldown of d days**: buy from `rest`, where `rest[i] = max(rest[i-1], sold[i-d])` (keep the last d values).
- **At most k transactions**: add the transaction count to the state, see `26_stock_k_transactions`.
