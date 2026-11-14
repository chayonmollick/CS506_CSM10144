# 09. Rabin–Karp Pattern Search

Source: Tutorial 8 (rolling hashes, Q11 part (b) technique); CLRS RABIN-KARP-MATCHER.

## Problem

Given a text T and a pattern P, print every shift s (0-based) such that T[s..s+|P|−1] = P, in
increasing order, using the Rabin–Karp algorithm. Occurrences may overlap. Print `-1` if P does not
occur. Both lines may contain spaces.

**Input**
Line 1: T. Line 2: P.

**Output**
The shifts separated by single spaces, or `-1`.

**Constraints**
1 ≤ |T| ≤ 10^6, 1 ≤ |P| ≤ 10^5, printable ASCII characters.

**Sample Input**
```
abracadabra
abra
```

**Sample Output**
```
0 7
```

## Idea

Treat a string of length m as an m-digit number in base d = 256 and keep it modulo a prime q.
Compute the pattern hash p and the hash t of the first window once (Horner's rule). Moving the
window one step removes the leading digit and appends the next one in O(1):

t' = (d·(t − T[s]·h) + T[s+m]) mod q, with h = d^(m−1) mod q.

Equal hashes are only a *candidate* match ("spurious hit" if the strings differ), so compare the m
characters before reporting. With a large prime q spurious hits are rare, so the expected time is
O(n + m) plus O(m) per real match. (Checked: even with q = 13, as in the CLRS example, the output
still matches the naive matcher on 1500 random inputs.)

## Pseudocode

```
function RABIN_KARP(T[0..n-1], P[0..m-1], d, q):
    if m > n: return []
    h = d^(m-1) mod q
    p = 0, t = 0
    for i = 0 to m-1:                         // preprocessing (Horner)
        p = (d*p + P[i]) mod q
        t = (d*t + T[i]) mod q
    result = []
    for s = 0 to n-m:
        if p == t and T[s..s+m-1] == P:       // verify: rules out spurious hits
            result.append(s)
        if s < n-m:
            t = (d*(t - T[s]*h) + T[s+m]) mod q   // keep it non-negative: add q before mod
    return result
```

## Complexity

Preprocessing O(m). Matching O(n + m) expected, O((n − m + 1)·m) worst case (every window a spurious
hit or a real match, e.g. T = aaaa…, P = aa…). Space O(1) besides the output.

## Edge cases / traps

- Overlapping matches: "aaaaa" / "aa" → `0 1 2 3` (tests/3). Do not jump ahead by m after a match.
- |P| > |T|: no window at all, print `-1` (tests/5). Without the check, `n − m` is negative.
- `t − T[s]·h` is negative before the mod: add q.
- Use `unsigned char` for character codes; `char` can be negative for non-ASCII bytes.
- Lines with spaces: read with `getline`, not `cin >>` (tests/6). Strip a trailing `'\r'`.
- `d*t` with t < q ≈ 10^9 fits in `long long`; with `int` it overflows.

## Variants they might ask

- **Count occurrences / first occurrence only**: count `result` / stop at the first verified match.
- **Number of spurious hits** (CLRS exercise, d = 10, q = 13, T = 2359023141526739921, P = 31415):
  count windows with `p == t` that fail verification (tests/2 has this text; the true match is at 6).
- **Multiple patterns of the same length**: put all pattern hashes in a hash set and look up each
  window's hash (verify on hit).
- **2D / other alphabets**: change d to the alphabet size, map characters to 0..d−1.

## Files

`sol.cpp`, `brute.cpp` (naive matcher). 800 random inputs agree (texts with spaces included).
