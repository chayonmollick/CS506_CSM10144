# 10. Farmer Totals and Heavy Hitters (more than n/k records)

Source: Tutorial 8, Q12 (Punjab Mandi Board, Khanna grain market): (a) per-farmer totals,
(b) farmer-IDs appearing in more than n/k records, two passes, O(k) memory (Misra–Gries).

## Problem

There are n sale records (farmer-ID, quantity); farmer-IDs are 12-digit numbers.

(a) Print the total quantity sold by every farmer, in order of the farmer's first appearance.
(b) Print, in increasing order, every farmer-ID that appears in **more than n/k** records
(strictly more). Print `NONE` if there is none.

**Input**
Line 1: n k. Next n lines: `id quantity`.

**Output**
Line 1: D, the number of distinct farmers. Next D lines: `id total`. Last line: the heavy IDs
separated by spaces, or `NONE`.

**Constraints**
1 ≤ n ≤ 10^5, 2 ≤ k ≤ 100, 10^11 ≤ id < 10^12, 1 ≤ quantity ≤ 10^9 (totals need 64 bits).

**Sample Input**
```
10 3
482910375561 50
730215649902 20
482910375561 30
118804567213 10
482910375561 25
730215649902 40
482910375561 5
905561230047 15
730215649902 10
730215649902 35
```

**Sample Output**
```
4
482910375561 110
730215649902 105
118804567213 10
905561230047 15
482910375561 730215649902
```

(n/k = 3.33; the first two farmers have 4 records each.)

## Idea

**(a)** A hash map farmer-ID → total, one pass, O(n) expected. A direct-address table is not
reasonable: the universe has 10^12 possible IDs (terabytes of memory) while only a few thousand are
used. Keep a list of IDs in first-appearance order for printing.

**(b) Simple hash version** (`sol.cpp`): count records per ID in the same hash map and keep those with
count·k > n. O(n) expected, but O(#farmers) memory.

**(b) Misra–Gries** (`sol_misra_gries.cpp`), O(k) memory, two passes:

- Pass 1 keeps at most k − 1 (candidate, counter) pairs. For record x: if x is a candidate, increment
  its counter; else if a counter is 0, make x a candidate with counter 1; else decrement **all** k − 1
  counters (x and k − 1 different IDs "cancel" each other).
- Invariant: every decrement step removes k occurrences of k different IDs (x itself plus one of each
  candidate). So there are at most n/k decrement steps, and any ID's true count minus its counter
  is at most n/k. An ID with count > n/k therefore still has a positive counter at the end: it
  survives pass 1.
- Pass 1 can also keep IDs that are not heavy, so pass 2 counts the ≤ k − 1 candidates exactly and
  reports those with count·k > n.

## Pseudocode

```
function TOTALS(records):                       // part (a)
    total = empty hash map, order = []
    for (id, q) in records:
        if id not in total: total[id] = 0, order.append(id)
        total[id] = total[id] + q
    print |order|
    for id in order: print id, total[id]

function MISRA_GRIES(records, k):               // part (b), O(k) words
    cand[1..k-1], cnt[1..k-1] = 0
    for (x, _) in records:                      // pass 1
        if x == cand[c] for some c with cnt[c] > 0:
            cnt[c] = cnt[c] + 1
        else if cnt[c] == 0 for some c:
            cand[c] = x, cnt[c] = 1
        else:
            for c = 1 to k-1: cnt[c] = cnt[c] - 1
    heavy = []
    for c = 1 to k-1 with cnt[c] > 0:            // pass 2: verify
        occ = number of records with id == cand[c]
        if occ * k > n: heavy.append(cand[c])
    sort heavy
    print heavy, or "NONE" if empty
```

## Complexity

(a) O(n) expected time, O(#farmers) space. (b) hash version O(n) expected; Misra–Gries O(nk) time
with the plain array of candidates (O(n) expected if the candidates are kept in a small hash map),
O(k) extra space, exactly two passes.

## Edge cases / traps

- "More than n/k" is strict: compare `count * k > n` in integers (no division, no rounding to think
  about). `count > n / k` with integer division also works for whole counts, but `count >= n / k`
  or a floating-point comparison does not. A count of exactly n/k is not heavy (tests/3: n = 6,
  k = 2, count 3; tests/4: three IDs with exactly n/k = 2 records each).
- k > n: every ID is heavy (tests/5).
- IDs are 12 digits: `long long`, not `int`. Totals up to 10^14: `long long`.
- Misra–Gries output after pass 1 alone may contain false positives: always run pass 2.
- There can be at most k − 1 heavy IDs (k of them would need more than n records).

## Variants they might ask

- **Majority element (k = 2)**: Misra–Gries with one counter is Boyer–Moore voting.
- **Top farmer by total / sort by total**: copy (total, id) pairs to a vector and sort, or use a heap.
- **Print totals in increasing ID order**: sort `order` before printing (or use `std::map`).
- **Only one pass allowed**: Misra–Gries counters give a superset of the heavy IDs plus estimates
  (counter ≤ true count ≤ counter + n/k), but not the exact answer.

## Files

`sol.cpp` (hash counts), `sol_misra_gries.cpp` (two-pass, k − 1 counters for (b)), `brute.cpp`
(O(n²) rescans). All three agree on 800 random inputs.
