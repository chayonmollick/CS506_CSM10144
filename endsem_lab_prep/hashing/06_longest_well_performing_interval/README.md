# 06. Longest Well-Performing Interval

Source: LeetCode 1124 (Coding Practice Set 3, Q3 "Longest Well-Performing Interval (Hashing)").

## Problem

hours[i] is the number of hours an employee worked on day i. A day is **tiring** if hours[i] > 8
(strictly). A well-performing interval is a contiguous range of days in which tiring days are strictly
more than non-tiring days. Print the length of the longest well-performing interval (0 if none).

**Input**
Line 1: n. Line 2: n integers hours[0..n−1].

**Output**
One integer.

**Constraints**
1 ≤ n ≤ 10^5, 0 ≤ hours[i] ≤ 16.

**Sample Input**
```
7
9 9 6 0 6 6 9
```

**Sample Output**
```
3
```

(Days 0..2 = 9 9 6: two tiring, one not.)

## Idea

Score each day +1 (tiring) or −1. An interval is well-performing when its score sum is > 0, i.e.
P[j+1] − P[i] > 0 with prefix sums P. At day j with prefix s:

- If s > 0, the whole prefix 0..j works: length j + 1 (the best possible ending at j).
- Otherwise we want the earliest index i with P < s. Prefix sums start at 0 and move by ±1, so before
  any prefix value v < s ≤ 0 can appear, the value s − 1 must have appeared first. Hence the earliest
  prefix smaller than s is the **first occurrence of s − 1**. Look it up in a map of first
  occurrences: length j − first[s − 1].

Store each prefix value only at its first occurrence.

## Pseudocode

```
function LONGEST_WPI(hours[0..n-1]):
    first = empty hash map            // prefix score -> first index
    s = 0, best = 0
    for j = 0 to n-1:
        if hours[j] > 8: s = s + 1 else: s = s - 1
        if s > 0:
            best = j + 1
        else if (s - 1) in first:
            best = max(best, j - first[s - 1])
        if s not in first:
            first[s] = j
    return best
```

## Complexity

O(n) expected time, O(n) space. Brute force O(n²).

## Edge cases / traps

- Exactly 8 hours is **not** tiring (`> 8`, tests/4).
- No tiring day at all: 0 (tests/2). All tiring: n (tests/6).
- Looking up `s` instead of `s − 1` finds intervals with sum 0 (equal counts), which are not
  "strictly more".
- Do not overwrite first occurrences.
- Why only s − 1 (not s − 2, s − 3 ...)? Any smaller value first appears after s − 1 did, so it gives
  a shorter interval.

## Variants they might ask

- **Longest interval with sum ≥ 1 for general ±1 / 0 scores**: with 0 scores the "first occurrence of
  s − 1" argument breaks (prefixes can stay flat). Use a monotonic stack of prefix minima, or check
  all smaller values when the range is small.
- **Return the interval**: track `l = first[s−1] + 1` (or 0) and `r = j` when `best` improves.
- **Threshold other than 8 / at least as many tiring days (≥)**: change the score test, and for "≥"
  look up `s` (sum ≥ 0) and use `s >= 0` for the prefix case.

## Files

`sol.cpp` (`unordered_map`), `brute.cpp` (O(n²)). 600 random inputs agree.
