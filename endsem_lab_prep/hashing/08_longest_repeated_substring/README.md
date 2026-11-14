# 08. Longest Repeated Substring (Rabin–Karp + Binary Search)

Source: Tutorial 8, Q11 (also LeetCode 1044 "Longest Duplicate Substring").

## Problem

Given a string S of length n, find the length L of the longest substring that occurs at least twice
in S. The two occurrences may overlap. Also print that substring; if several substrings of length L
repeat, print the one whose first occurrence starts earliest.

**Input**
One line: S (lowercase letters, no spaces).

**Output**
Line 1: L. Line 2: the substring (only if L > 0).

**Constraints**
1 ≤ n ≤ 10^5.

**Sample Input**
```
banana
```

**Sample Output**
```
3
ana
```

("ana" occurs at 1 and 3, overlapping.)

## Idea

(a) **Monotonicity.** If a substring of length L occurs at positions i ≠ j, then its first L′ characters
occur at i and j too, so some substring of every length L′ < L repeats. So "a repeat of length L
exists" is true for L = 0..L* and false above: binary search for L*.

(b) **Check one length in O(n) expected.** Slide a window of length L with a Rabin–Karp rolling hash:
`h = (h − S[i−1]·B^(L−1))·B + S[i+L−1]  (mod p)`. Keep a hash map from hash value to the start
positions of the *different* strings seen with that hash. A new window with an equal hash is compared
character by character with each stored start: if the strings are equal it is a real repeat; if not,
it was a collision, and the window is stored as a new string.

**Collisions never cause a wrong answer**: a repeat is reported only after the characters are
compared, and a collision only costs one extra O(L) comparison. (Checked: with the modulus changed
to 3, i.e. constant collisions, the program still agrees with the brute force on 1500 random strings.)

## Pseudocode

```
function CHECK(S, L, leftmost):              // first start of a repeated length-L substring, or -1
    high = B^(L-1) mod p
    h = hash of S[0..L-1]                    // Horner: h = (h*B + S[i]) mod p
    seen = empty hash map                    // hash value -> list of starts (distinct strings)
    best = -1
    for i = 0 to n-L:
        if i > 0:
            h = ((h - S[i-1]*high) mod p + p) mod p
            h = (h*B + S[i+L-1]) mod p
        dup = false
        for each j in seen[h]:
            if S[j..j+L-1] == S[i..i+L-1]:   // verify: rules out collisions
                dup = true
                best = (best == -1) ? j : min(best, j)
                break
        if dup and not leftmost: return best
        if not dup: append i to seen[h]
    return best

function LONGEST_REPEATED(S):
    lo = 0, hi = n - 1
    while lo < hi:
        mid = (lo + hi + 1) / 2
        if CHECK(S, mid, false) != -1: lo = mid
        else: hi = mid - 1
    print lo
    if lo > 0: print S[CHECK(S, lo, true) .. + lo - 1]
```

## Complexity

O(log n) checks, each O(n) expected (hashing plus verification of real matches; the early exit keeps
the binary-search checks cheap): O(n log n) expected overall. O(n) space. Brute force O(n³)–O(n⁴).

## Edge cases / traps

- n = 1 or all characters distinct: L = 0, print only `0` (tests/2, tests/3).
- Overlap allowed: "aaaaa" → 4 "aaaa" (tests/4). If overlap is *not* allowed you must also require
  `i − j ≥ L`.
- Use `mid = (lo + hi + 1) / 2` when moving `lo = mid`, or the loop never ends.
- Subtracting `S[i−1]·high` can go negative: add p before taking mod again.
- `h * B` must not overflow: with p ≈ 10^9 and B = 131 the product fits in `long long`.
- Do not trust the hash alone. Without the string comparison a collision gives a wrong length.

## Variants they might ask

- **Length only** (exactly Tutorial Q11): print `lo` and stop.
- **Repeats at least k times**: count verified matches per stored string and accept when a count
  reaches k − 1 (monotonicity still holds).
- **Non-overlapping repeats**: accept a match only if `i − j ≥ L`; keep the earliest start j of each
  string. Monotonicity still holds.
- **Longest common substring of two strings**: same binary search; insert all windows of the first
  string, then look up windows of the second (verify on hash match).

## Files

`sol.cpp`, `brute.cpp` (all lengths, all pairs). 800 random inputs agree; inputs of 10^5 characters
(all 'a', random "ab", a 50 000-character block twice) run in under 0.35 s.
