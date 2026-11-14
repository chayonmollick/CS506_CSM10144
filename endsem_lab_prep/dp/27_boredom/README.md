# 27. Boredom

Source: Practice Set 4 Q9 — [Codeforces 455A Boredom](https://codeforces.com/problemset/problem/455/A)

## Problem

You are given a sequence of `n` integers. In one step you choose an element with value `x`, delete it and gain
`x` points; at the same time **every** element equal to `x - 1` or `x + 1` is deleted (without points).
You may stop at any time. Find the maximum number of points.

**Input**
Line 1: integer `n`. Line 2: `n` integers `a[1] .. a[n]`.

**Output**
A single integer: the maximum points.

**Constraints**
1 ≤ n ≤ 10^5, 1 ≤ a[i] ≤ 10^5

**Sample Input**
```
9
1 2 1 3 2 2 2 2 3
```

**Sample Output**
```
10
```

(Choose a 2: both 1s and both 3s disappear; then take the remaining four 2s: 5 × 2 = 10.)

## Idea

- Once you take one copy of `x`, all `x-1` and `x+1` are gone, so you can take **all** copies of `x` with no further
  loss. So per value the decision is just "take all copies of x" (gain `x · cnt[x]`) or "take none".
- Two adjacent values `x` and `x+1` cannot both be taken → this is **house robber over the values 1..MAX**
  with house `x` worth `x · cnt[x]` (see `23_house_robber`).
- Subproblem: `f[x]` = best points using only values `1..x`.
- Recurrence: `f[x] = max(f[x-1], f[x-2] + x · cnt[x])`.
- Base: `f[0] = 0`, `f[1] = cnt[1]`. Fill `x = 2..MAX`, answer `f[MAX]`.
- Counting `cnt[x]` is a direct-address table (values ≤ 10^5); for values up to 10^9 use a hash map and work over the
  sorted distinct values (see variants).

## Pseudocode

```
function BOREDOM(a[1..n]):
    cnt[0..MAX] = 0
    for i = 1 to n:
        cnt[a[i]] = cnt[a[i]] + 1
    f[0] = 0
    f[1] = cnt[1]
    for x = 2 to MAX:
        f[x] = max(f[x-1], f[x-2] + x * cnt[x])
    return f[MAX]

Main:
    read n, a[1..n]
    print BOREDOM(a)
```

## Complexity

O(n + MAX) time and space, MAX = 10^5.

## Edge cases / traps

- **Overflow**: 10^5 copies of 10^5 give 10^10 points — `f` and `cnt` must be `long long` (and `x * cnt[x]` must be
  computed in `long long`).
- Greedy "take the largest value first" fails: `5 6 6 7 7 7`: taking 7s (21) + 5 = 26 is right here, but for
  `1 2 1 3 2 2 2 2 3` taking 3 first gives 3+3+1+1 = 8 < 10.
- Values that do not occur have `cnt = 0`; the recurrence just carries `f[x-1]` forward.

## Variants they might ask

- **Values up to 10^9**: count with `unordered_map<int,long long>`, sort the distinct values `v1 < v2 < ...`;
  if `v[i] == v[i-1] + 1` use `f[i] = max(f[i-1], f[i-2] + v[i]·cnt)`, otherwise `f[i] = f[i-1] + v[i]·cnt`.
- **Deleting x-d..x+d** (a wider band): `f[x] = max(f[x-1], f[x-d-1] + x·cnt[x])`.
- **Print the chosen values**: walk back from `x = MAX`: if `f[x] == f[x-1]` go to `x-1`, else `x` was taken, go to `x-2`.
