# 32. Word Break (hash-set dictionary): decide, count, reconstruct

Source: Tutorial 9 Q14 (related: [LeetCode 139 Word Break](https://leetcode.com/problems/word-break/), [LeetCode 140 Word Break II](https://leetcode.com/problems/word-break-ii/)).

## Problem

Given a string `s` and a dictionary `D` of distinct words stored in a **hash set**, decide whether `s` can be split
into a sequence of dictionary words (a word may be used any number of times).

(a) Print `YES` or `NO`.
(b) Print the number of different segmentations modulo 1000000007.
(c) If the answer is `YES`, print one segmentation: the one with the **shortest possible first word**, then the
shortest possible second word, and so on (each choice must still allow the rest to be split).

**Input**
Line 1: the string `s`. Line 2: `m`, the number of words. Line 3: `m` distinct words, space-separated.

**Output**
Line 1: `YES` or `NO`. Line 2: the number of segmentations modulo 1000000007 (0 if `NO`).
Line 3 (only if `YES`): the words of the chosen segmentation separated by single spaces.

**Constraints**
1 ≤ |s| ≤ 1000, 1 ≤ m ≤ 1000, 1 ≤ word length ≤ 20; all strings use lowercase letters.

**Sample Input**
```
catsanddog
5
cat cats and sand dog
```

**Sample Output**
```
YES
2
cat sand dog
```

(The two segmentations are `cat sand dog` and `cats and dog`; the first word `cat` is shorter.)

## Idea

- Subproblem (suffixes): `ok[i]` = the suffix `s[i..n)` can be split; `ways[i]` = number of splits of `s[i..n)`.
- The first word of a split of `s[i..n)` is `s[i..i+L)` for some `1 ≤ L ≤ ℓ` (ℓ = max word length) that is in `D`,
  and the rest `s[i+L..n)` must itself be splittable:
  - `ok[i] = OR over L of ( s[i..i+L) ∈ D and ok[i+L] )`
  - `ways[i] = Σ over L with s[i..i+L) ∈ D of ways[i+L]`
- Base case: `ok[n] = true`, `ways[n] = 1` (the empty suffix has exactly one split — the empty one).
- Fill order: `i = n-1` down to 0. Answers: `ok[0]`, `ways[0]`.
- Each hash lookup of a substring of length ≤ ℓ costs O(ℓ) expected, so the total is O(nℓ²) expected (Tutorial Q14a).
- Reconstruction: start at `i = 0`; take the smallest `L` with `s[i..i+L) ∈ D` and `ok[i+L]`; move to `i+L`.
  Because `ok[i+L]` is true the walk never gets stuck. Suffix DP is what makes this forward walk easy.
- Why counting is polynomial but listing is not (Q14b): `s = aaaa...a`, `D = {a, aa}` has Fib(n+1) splits —
  exponentially many to print, but `ways[]` adds them up in O(nℓ²).

## Pseudocode

```
function WORD_BREAK(s[0..n-1], D, maxLen):
    ok[0..n] = false, ways[0..n] = 0
    ok[n] = true, ways[n] = 1
    for i = n - 1 down to 0:
        for L = 1 to min(maxLen, n - i):
            if ok[i + L] and s[i .. i+L-1] in D:        // hash-set lookup
                ok[i] = true
                ways[i] = (ways[i] + ways[i + L]) mod M
    return ok, ways

function ONE_SPLIT(s, D, ok):
    i = 0, words = []
    while i < n:
        L = smallest L >= 1 with ok[i + L] and s[i .. i+L-1] in D
        words.append(s[i .. i+L-1])
        i = i + L
    return words

Main:
    read s, m, words; insert words into hash set D; maxLen = longest word
    (ok, ways) = WORD_BREAK(s, D, maxLen)
    if not ok[0]: print "NO", print 0
    else: print "YES", print ways[0], print ONE_SPLIT(s, D, ok) (space-separated)
```

## Complexity

O(n·ℓ²) expected time (n·ℓ substrings, each hashed in O(ℓ)), O(n + total dictionary size) space.

## Edge cases / traps

- Limit `L` by `maxLen` — looping `L` up to `n` makes it O(n²·ℓ) or worse.
- `ok[0]` true but `ways[0] mod M == 0` is possible in theory — decide YES/NO from `ok`, never from `ways`.
- Take `% M` on every addition (`aaaa...a` with `{a, aa}` overflows `long long` by n ≈ 90).
- Words may be reused; the dictionary is a set, so a repeated word in the input would not be counted twice.
- Prefix DP (`dp[j]` = `s[0..j)` splittable) also works for (a)/(b), but then reconstruct **backwards** and the
  "shortest first word" rule is harder; the suffix DP matches the rule directly.

## Variants they might ask

- **Only decide (LeetCode 139)**: drop `ways` and the reconstruction.
- **Print all segmentations (LeetCode 140)**: DFS from `i = 0` that only follows `L` with `ok[i+L]` true (no dead ends).
- **Minimum number of words**: `best[i] = min over valid L of best[i+L] + 1`, `best[n] = 0`.
- **Longest-first-word rule**: in the reconstruction try `L` from `maxLen` down to 1.
