# 17. Reorganize string (no two equal neighbours)

Source: exam-style variant of LeetCode 767 "Reorganize String",
<https://leetcode.com/problems/reorganize-string/>. Optional, the same greedy family as the task
scheduler (08).

## Problem

Rearrange the letters of a lowercase string s so that no two adjacent characters are equal. If
this is impossible, print `IMPOSSIBLE`.

**Deterministic rule (stated):** build the answer left to right. At each step append the letter
with the **most copies left** among letters different from the previous character. On ties,
choose the **alphabetically smaller** letter.

**Input.** One line: s (1 ≤ |s| ≤ 10^5, letters `a`–`z`).

**Output.** One line: the rearranged string, or `IMPOSSIBLE`.

**Sample Input**
```
aaabbc
```
**Sample Output**
```
ababac
```

## Idea

- **Feasibility (pigeonhole):** a letter occurring more than ⌈n/2⌉ = (n+1)/2 times must end up
  next to itself. Otherwise the greedy always succeeds.
- **Greedy with a max-heap** of (count, −letter). Pop the top. If it equals the previous
  character, pop the next one instead, use it, and push the first one back. Push back any
  letter with copies left.

## Pseudocode

```
function REORGANIZE(s):
    count each letter in cnt[a..z]
    if max(cnt) > (n + 1) / 2:
        return "IMPOSSIBLE"
    H = max-heap of (cnt[c], -c) for every c with cnt[c] > 0
    res = ""
    while H is not empty:
        (k, c) = EXTRACT_MAX(H)
        if res is not empty and last(res) == letter(c):
            (k2, c2) = EXTRACT_MAX(H)        // exists when feasible
            res.append(letter(c2))
            if k2 - 1 > 0: INSERT(H, (k2 - 1, c2))
            INSERT(H, (k, c))
        else:
            res.append(letter(c))
            if k - 1 > 0: INSERT(H, (k - 1, c))
    return res
```

## Complexity

n steps, each with O(log 26) = O(1) heap work: O(n) time, O(26) heap space plus O(n) output.

## Edge cases / traps

- n = 1: the string itself.
- `aab` → `aba`. `aaab` → `IMPOSSIBLE`, since 3 > (4+1)/2 = 2.
- Push the blocked letter back **after** using the second one, otherwise you pop it again
  immediately.
- (count, −letter) in a max-heap gives "more copies first, then smaller letter". Using
  (count, letter) would prefer the larger letter on ties.

## Variants they might ask

- **Equal letters at least k apart** (LeetCode 358): hold used letters in a queue for k steps
  before pushing them back. That is the task-scheduler idea from 08.
- **Only YES/NO:** just the pigeonhole check.
- **Any valid answer, O(n):** sort letters by count and fill even indices 0, 2, 4, … then odd
  indices.

## Files

`sol.cpp` (STL max-heap), `brute.cpp` (the same rule by scanning 26 counts). Random tests also
checked that every output has no equal neighbours, and compared `IMPOSSIBLE` against an
exhaustive permutation search for short strings.
