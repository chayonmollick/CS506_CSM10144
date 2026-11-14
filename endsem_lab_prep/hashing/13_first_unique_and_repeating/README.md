# 13. First Non-Repeating Element and First Repeating Element

Source: classic hash-count problems (GeeksforGeeks "First non-repeating element" and "First
repeating element"; LeetCode 387 is the string version).

## Problem

Given an array a[0..n−1]:

1. The **first non-repeating element** is the first element, in array order, that occurs exactly once.
2. The **first repeating element** is the element that occurs more than once and whose *first*
   occurrence has the smallest index.

Print both values (line 1 and line 2). Print `NONE` on a line if that element does not exist.

**Input**
Line 1: n. Line 2: n integers.

**Output**
Two lines, as described.

**Constraints**
1 ≤ n ≤ 10^5, −10^9 ≤ a[i] ≤ 10^9.

**Sample Input**
```
7
5 10 3 4 3 5 6
```

**Sample Output**
```
10
5
```

(5 and 3 both repeat; 5's first occurrence (index 0) is earlier than 3's (index 2). Note the other
definition, "the first element seen for the second time while scanning", would give 3 here.)

## Idea

Two passes. Pass 1 counts every value in a hash map. Pass 2 walks the array in order: the first index
with count 1 gives answer 1; the first index with count > 1 gives answer 2 (that index is the first
occurrence of its value, and it is the earliest among all repeated values).

## Pseudocode

```
function FIRST_UNIQUE_AND_REPEATING(a[0..n-1]):
    cnt = empty hash map
    for i = 0 to n-1:
        cnt[a[i]] = cnt[a[i]] + 1
    uniq = NONE, rep = NONE
    for i = 0 to n-1:
        if uniq == NONE and cnt[a[i]] == 1: uniq = a[i]
        if rep  == NONE and cnt[a[i]] > 1:  rep  = a[i]
    print uniq
    print rep
```

## Complexity

O(n) expected time, O(n) space. Brute force O(n²) (count each element by rescanning).

## Edge cases / traps

- Know which "first repeating" is asked: earliest **first** occurrence (this program) vs earliest
  **second** occurrence (scan with a hash set; the first value already in the set). The sample
  separates them (5 vs 3).
- Every value repeats → `NONE` on line 1 (tests/3); all distinct → `NONE` on line 2 (tests/4).
- n = 1: the element itself is non-repeating (tests/2).
- Negative values and ±10^9 (tests/5): a counting array would need 2·10^9 slots, so hash.
- Iterating the hash map to find "first" is wrong: its order is not the array order.

## Variants they might ask

- **First element seen twice while scanning** (one pass): keep a hash set; the first a[i] already in
  the set is the answer.
- **Print the 1-based position** (GfG style) instead of the value: `sol.cpp` already keeps the
  indices `uniq` / `rep`, so print `uniq + 1` / `rep + 1` (and `-1` when none).
- **First non-repeating character in a string**: `int cnt[256]` instead of the map.
- **First non-repeating element in a stream** (after each insertion): counts + a queue; pop from the
  front while the front's count > 1.

## Files

`sol.cpp`, `brute.cpp`. 800 random inputs agree.
