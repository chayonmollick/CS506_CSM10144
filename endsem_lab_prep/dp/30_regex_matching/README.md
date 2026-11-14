# 30. Regular Expression Matching ('.' and '*')

Source: Practice Set 4 Q12 — [LeetCode 10 Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/); Tutorial 9 Q18 (short version Q8).

## Problem

A pattern `p` consists of lowercase letters, the symbol `.` (matches any single letter) and `*` (zero or more copies
of the preceding element). Decide whether `p` matches the **entire** string `s` (not just a substring).

**Input**
Line 1: the string `s`. Line 2: the pattern `p`.

**Output**
One line: `YES` if `p` matches all of `s`, otherwise `NO`.

**Constraints**
1 ≤ |s|, |p| ≤ 1000. `s` has only lowercase letters. `p` has lowercase letters, `.` and `*`;
every `*` is preceded by a letter or `.` (never at the start, never `**`).

**Sample Input**
```
aab
c*a*b
```

**Sample Output**
```
YES
```

(`c*` is used zero times, `a*` twice, then `b`.)

## Idea

- Subproblem: `dp[i][j]` = true iff the prefix `s[0..i)` (first `i` chars) matches the prefix `p[0..j)` (first `j` chars).
- Base case: `dp[0][0] = true`; `dp[i][0] = false` for `i > 0` (empty pattern matches only the empty string).
  `dp[0][j]` can still be true for `j > 0` — e.g. `a*b*` matches the empty string — and the `*` rule below
  computes it automatically (row `i = 0` is filled too).
- Transition on the last pattern character `p[j-1]`:
  - letter or `.`: `dp[i][j] = dp[i-1][j-1]` if `i > 0` and `p[j-1]` matches `s[i-1]`, else false.
  - `*` (the element is `x = p[j-2]`):
    - **zero copies** of `x`: `dp[i][j-2]`;
    - **one more copy**: if `i > 0` and `x` matches `s[i-1]`, then `dp[i-1][j]` — we eat `s[i-1]` with one copy of
      `x` and keep the same `x*` available (column `j`, not `j-2`), which covers 1, 2, 3, ... copies.
    - `dp[i][j]` = (zero copies) OR (one more copy).
- Why the `*` rule is correct: in any match, `x*` matches some block `s[t..i)` of copies of `x`. If the block is empty
  we are in the first case; otherwise its last char `s[i-1]` matches `x` and `s[0..i-1)` matches `p[0..j)` with a
  shorter block — the second case. Conversely both cases build a valid match.
- Fill order: `i = 0..n` outer, `j = 1..m` inner (every reference is to a smaller `i` or smaller `j`). Answer `dp[n][m]`.

## Pseudocode

```
function IS_MATCH(s[1..n], p[1..m]):
    dp[0..n][0..m] = false
    dp[0][0] = true
    for i = 0 to n:
        for j = 1 to m:
            if p[j] == '*':
                dp[i][j] = dp[i][j-2]                                  // zero copies
                if i > 0 and (p[j-1] == '.' or p[j-1] == s[i]):
                    dp[i][j] = dp[i][j] or dp[i-1][j]                  // one more copy
            else if i > 0 and (p[j] == '.' or p[j] == s[i]):
                dp[i][j] = dp[i-1][j-1]
    return dp[n][m]

Main:
    read s, p
    if IS_MATCH(s, p): print "YES" else print "NO"
```

(Pseudocode is 1-indexed: `s[i]` here is `s[i-1]` in the C++ code.)

## Complexity

O(|s|·|p|) time and space (10^6 cells). Plain backtracking without memo is exponential (e.g. `aaaa...a` vs `a*a*...a*b`).

## Edge cases / traps

- `*` applies to the **preceding element**, so `a*` can vanish completely: `a` vs `ab*` → YES.
- Full match only: `aa` vs `a` → NO.
- `.*` matches everything, including the empty string: `ab` vs `.*` → YES, but `ab` vs `.*c` → NO.
- Do not skip row `i = 0`: patterns like `a*b*c*` must make `dp[0][j]` true.
- Guard `j ≥ 2` before reading `p[j-2]` (only matters if the input could start with `*`).
- Off-by-one: `dp` indices are lengths, string indices are `i-1`, `j-1`.

## Variants they might ask

- **Wildcard matching** (`?` = one char, `*` = any sequence, LeetCode 44): `*` rule becomes `dp[i][j] = dp[i][j-1] || dp[i-1][j]`.
- **Add `+` (one or more)**: `x+` means `xx*`, so rewrite the pattern first (replace every `x+` by `xx*`) and run the same DP.
- **O(|p|) space**: keep only rows `i-1` and `i`.
- **Count matching substrings / find first match**: run the DP once per start position (O(n^2 m)).
