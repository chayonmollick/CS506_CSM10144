# 15. Hash Functions: Division, Multiplication (Knuth) and Universal Hashing

Source: Tutorial 8, Q4 (m = 1000, A = (√5 − 1)/2, keys 61..65) and Q6 (h_ab(k) = ((ak + b) mod p) mod m);
slides "Compression maps", "Choosing A: Fibonacci hashing", "Universal hashing".

## Problem

For each of n keys compute its slot in a table of size m under three hash functions:

- Division: h(k) = k mod m
- Multiplication: h(k) = ⌊m · (k·A mod 1)⌋ with A = (√5 − 1)/2 ≈ 0.6180339887 ("k·A mod 1" is the
  fractional part of k·A)
- Universal: h_ab(k) = ((a·k + b) mod p) mod m, for the given prime p and constants a, b

**Input**
Line 1: m n. Line 2: n keys. Line 3: p a b.

**Output**
```
Division: <n slots>
Multiplication: <n slots>
Universal: <n slots>
```

**Constraints**
1 ≤ m ≤ 10^4, 1 ≤ n ≤ 10^5, 0 ≤ k ≤ 10^6, p prime with m < p ≤ 2·10^9 and every key < p,
1 ≤ a < p, 0 ≤ b < p.

**Sample Input**
```
1000 5
61 62 63 64 65
1009 389 17
```

**Sample Output**
```
Division: 61 62 63 64 65
Multiplication: 700 318 936 554 172
Universal: 539 928 308 697 77
```

Hand check, multiplication (Tutorial Q4): 61·A = 37.70007…, so ⌊1000 · 0.70007…⌋ = 700;
62·A = 38.31810… → 318; 63·A = 38.93614… → 936; 64·A = 39.55417… → 554; 65·A = 40.17220… → 172.
Universal: 389·61 + 17 = 23746 = 23·1009 + 539 → 539 mod 1000 = 539.

**Why it matters that consecutive keys go far apart (Q4):** keys that arrive in runs (IDs, roll
numbers) would fill neighbouring slots under k mod m, causing clustering in open addressing; with
Knuth's A the fractional parts {kA} jump by about 0.618 each step, so consecutive keys spread over the
whole table.

## Idea

Direct evaluation. The only care points are the fractional part (x − ⌊x⌋) and overflow in a·k.

## Pseudocode

```
function H_DIV(k, m):
    return ((k mod m) + m) mod m

function H_MUL(k, m):
    A = (sqrt(5) - 1) / 2
    x = k * A
    return floor(m * (x - floor(x)))

function H_UNIV(k, m, p, a, b):
    return ((a*k + b) mod p) mod m         // a*k in 64-bit
```

## Complexity

O(1) per key, O(n) total.

## Edge cases / traps

- `fmod(x, 1.0)` or `x − floor(x)` for the fractional part; casting to `int` before multiplying by m
  loses everything.
- Precision: with `double` and keys ≤ 10^6 the result was checked against 50-digit decimal
  arithmetic for **every** key 0..10^6 and m ∈ {1, 701, 1000, 1024, 9973, 10000}: all equal. For
  much larger keys use the integer method below.
- `a*k` overflows 32 bits (a up to 2·10^9): `long long`.
- Universal family requirements: p prime, p > every key, a ≠ 0 (a = 0 sends every key to b mod p mod m).
- m = 1: every slot is 0 (tests/3).

## Variants they might ask

- **CLRS integer multiplication method** (m = 2^r, word size w = 32): s = ⌊A·2^32⌋ = 2654435769,
  h(k) = ((k·s) mod 2^32) >> (32 − r). In C++: `(unsigned)((unsigned long long)k * 2654435769ULL) >> (32 - r)`.
  (Gives slightly different slots from the real-number formula; use it only if asked.)
- **Strings**: polynomial hash with Horner's rule, h = (h·x + c) mod m, x = 31/33/37/41 (slides).
- **Insert these keys into a chained table**: feed the chosen h into `templates/hash_chaining`.
- **Pick random a, b**: `a = 1 + rand() % (p − 1)`, `b = rand() % p`; print them for reproducibility.

## Files

`sol.cpp` only (a brute force would be the same formula). Verified with Python `decimal` (50 digits)
on all tests and on every key 0..10^6 for six table sizes.
