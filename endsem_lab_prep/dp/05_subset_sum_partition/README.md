# 05. Subset Sum / Equal-Sum Partition (1-D table)

Source: Tutorial 9 Q15 (O(nS) with a one-dimensional table, inner loop downward);
Practice Set 4 Q7 (Partition Equal Subset Sum).

## Problem

Given n positive integers a_1 ... a_n with total S, decide whether they can be split into two
groups with equal sums. If they can, print the indices of one group with sum S/2.

If several groups work, print the one with the smallest possible largest index; among those,
the smallest possible second-largest index, and so on. (This is exactly the group the 1-D table
below reconstructs.)

**Input**
- Line 1: n
- Line 2: n integers a_1 ... a_n

**Output**
- Line 1: `YES` or `NO`
- Line 2 (only for `YES`): the indices (1-based, increasing) of one group with sum S/2

**Constraints**: 1 ≤ n ≤ 100, 1 ≤ a_i ≤ 1000 (so S ≤ 10^5).

**Sample Input**
```
4
1 5 11 5
```

**Sample Output**
```
YES
3
```

## Idea

- Partition is subset sum with target T = S/2 (if S is odd, answer NO immediately).
- Subproblem (2-D form): can[i][s] = some subset of items 1..i sums to s.
  Recurrence: can[0][0] = true, can[0][s>0] = false;
  can[i][s] = can[i−1][s] OR (a_i ≤ s AND can[i−1][s − a_i]).
- 1-D form: keep one array can[0..T]; for each item run s = T down to a_i:
  can[s] = can[s] OR can[s − a_i]. Going DOWN means can[s − a_i] still holds the value from
  the previous row (items 1..i−1), so item i is used at most once.
- Reconstruction: when can[s] turns true for the first time (while processing item i) store
  from[s] = i. Then walk s = T, output from[s], s = s − a[from[s]] until s = 0. The indices
  strictly decrease, so no item repeats.

## Pseudocode

```
function SUBSET-SUM(a, n, T):
    can[0] = true
    for s = 1 to T:
        can[s] = false
    for i = 1 to n:
        for s = T downto a[i]:          // downward: item i used at most once
            if not can[s] and can[s - a[i]]:
                can[s] = true
                from[s] = i
    return can[T]

function EQUAL-PARTITION(a, n):
    S = a[1] + ... + a[n]
    if S is odd:
        print "NO"; return
    if not SUBSET-SUM(a, n, S / 2):
        print "NO"; return
    print "YES"
    s = S / 2
    while s > 0:                        // traceback
        output from[s]
        s = s - a[from[s]]
```

## Complexity

O(nS) time, O(S) space. Pseudo-polynomial (Tutorial Q15(b)): polynomial in the VALUE S, but
exponential in the input size (S needs only log S bits); the problem is NP-complete.

## Edge cases / traps

- Odd total: NO without running the DP. n = 1: always NO (a_1 > 0).
- Inner loop UPWARD is the bug from the tutorial: can[s − a_i] may already include item i, so
  an item is reused (e.g. a = {3}, T would reach 6 from 3 + 3).
- Use `vector<bool>`/`vector<char>` of size T + 1, not an int array of size 10^5 on the stack
  inside main if limits grow.
- The traceback needs from[] recorded only the FIRST time can[s] becomes true; overwriting it
  later can make the walk use an item twice.

## Variants they might ask

- Subset sum with a given target T: call SUBSET-SUM(a, n, T) directly (same code, T from input).
- Count subsets with sum T: replace OR by `+` (cnt[s] += cnt[s − a_i]), still downward.
- Minimum difference partition: run SUBSET-SUM with T = S/2 (floor) and take the largest s ≤ T with
  can[s] true; answer S − 2s.
- k equal groups / negative numbers: different problem (bitmask DP / shift indices by the
  most negative sum).
