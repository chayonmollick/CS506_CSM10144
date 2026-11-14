# 07. Minimum Window Substring

Source: LeetCode 76 (Coding Practice Set 3, Q13 "Minimum Window Substring (Hashing)").

## Problem

Given strings s and t, find the shortest substring (window) of s that contains every character of t,
including duplicates (if t has two 'a's, the window needs at least two 'a's). Characters are
case-sensitive. If several shortest windows exist, print the leftmost one. If no window exists,
print `-1`.

**Input**
Line 1: s. Line 2: t. Both consist of English letters only (no spaces).

**Output**
The window, or `-1`.

**Constraints**
1 ≤ |s|, |t| ≤ 10^5.

**Sample Input**
```
ADOBECODEBANC
ABC
```

**Sample Output**
```
BANC
```

## Idea

Sliding window with a count table. `need[c]` = how many more c's the window still needs (it goes
negative when the window has extras); `missing` = total characters of t not yet covered.

- Move r right. If `need[s[r]] > 0` this character covers something, so `missing--`; then
  `need[s[r]]--`.
- While `missing == 0` the window [l, r] is valid: record it if shorter, then drop s[l]
  (`need[s[l]]++`, and if it becomes > 0 the window lost a needed character: `missing++`), `l++`.

Each index enters and leaves the window once. The table is indexed by character code (a direct-address
table with 128 slots); use `unordered_map<char,int>` if the alphabet is unknown.

## Pseudocode

```
function MIN_WINDOW(s[0..n-1], t):
    need[0..127] = 0
    for each c in t: need[c] = need[c] + 1
    missing = |t|, l = 0, bestLen = INF, bestL = 0
    for r = 0 to n-1:
        if need[s[r]] > 0: missing = missing - 1
        need[s[r]] = need[s[r]] - 1
        while missing == 0:
            if r - l + 1 < bestLen: bestLen = r - l + 1, bestL = l
            need[s[l]] = need[s[l]] + 1
            if need[s[l]] > 0: missing = missing + 1
            l = l + 1
    if bestLen == INF: return "-1"
    return s[bestL .. bestL + bestLen - 1]
```

## Complexity

O(|s| + |t|) time (each pointer moves at most |s| times), O(alphabet) space.
Brute force: all O(|s|²) windows (`brute.cpp`).

## Edge cases / traps

- Duplicates in t: "a" vs "aa" has no answer (tests/3). Counting distinct characters only is wrong.
- Case matters: 'A' ≠ 'a' (tests/5).
- Indexing an array with a `char` gives a `-Wchar-subscripts` warning; convert to `int` first.
- Update the best window **inside** the while loop, before removing s[l].
- `strictly shorter` keeps the leftmost window on ties.
- |t| > |s| means no answer.

## Variants they might ask

- **Print only the length** (or `0` when none): print `bestLen`.
- **Window containing all distinct characters of s itself**: build t from the distinct characters of s.
- **Longest substring without repeating characters** (same two-pointer + count idea): grow r, and while
  `cnt[s[r]] > 1` shrink l.
- **Permutation of t as a substring (fixed window |t|)**: slide a window of exactly |t| and compare counts.

## Files

`sol.cpp`, `brute.cpp` (all windows). 800 random inputs agree.
