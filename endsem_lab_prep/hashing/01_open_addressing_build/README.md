# 01. Open Addressing: Build the Table and Count Probes

Source: Tutorial 8, Q3 (keys 10 22 31 4 15 28 17 88 59, m = 11); slides "Hash tables" (linear,
quadratic, double hashing worked examples).

## Problem

Insert n distinct integer keys, in the given order, into an empty hash table of m slots using open
addressing with the auxiliary hash function h'(k) = k mod m (taken non-negative, so -3 mod 7 = 4).
The probe sequence for key k is h(k, 0), h(k, 1), ..., h(k, m−1) where

- `LINEAR`: h(k, i) = (h'(k) + i) mod m
- `QUADRATIC c1 c2`: h(k, i) = (h'(k) + c1·i + c2·i²) mod m
- `DOUBLE`: h(k, i) = (h'(k) + i·h2(k)) mod m with h2(k) = 1 + (k mod (m − 1))

A key goes into the first empty slot of its probe sequence. The number of probes of an insertion is
the number of slots examined, including the empty slot finally used (1 if the home slot is free).
If all m probes hit occupied slots, the key is not inserted: print -1 as its probe count; it still
adds m to the total.

**Input**
Line 1: m. Line 2: `LINEAR`, `QUADRATIC c1 c2` or `DOUBLE`. Line 3: n. Line 4: n distinct keys.

**Output**
```
Table: <slot 0> <slot 1> ... <slot m-1>      (key, or - if empty)
Probes: <p1> <p2> ... <pn>                   (in input order)
Total: <sum of probes>
```

**Constraints**
1 ≤ n ≤ m ≤ 10^5 (m ≥ 2 for DOUBLE), keys distinct in [−10^9, 10^9], 0 ≤ c1, c2 ≤ 100.

**Sample Input**
```
11
LINEAR
9
10 22 31 4 15 28 17 88 59
```

**Sample Output**
```
Table: 22 88 - - 4 15 28 17 59 31 10
Probes: 1 1 1 1 2 1 2 2 5
Total: 16
```

The other two parts of Tutorial Q3 (tests/2 and tests/3):

```
QUADRATIC 1 3 -> Table: 22 - 88 17 4 - 28 59 15 31 10   Probes: 1 1 1 1 2 1 4 9 3   Total: 23
DOUBLE        -> Table: 22 - 59 17 4 15 28 88 - 31 10   Probes: 1 1 1 1 3 1 2 3 3   Total: 16
```

Which scheme needs the most probes? Quadratic (23): with c1 = 1, c2 = 3, m = 11 the sequence is not a
permutation (88 visits 0, 4, 3, 8, 8, 3, 4, 0, 2) and keys with the same h'(k) share their whole path
(secondary clustering). Linear pays for primary clustering (59 walks 4, 5, 6, 7, 8). Double hashing
gives different keys with the same home slot different step sizes.

## Idea

Simulate HASH-INSERT from the slides: for i = 0, 1, ... compute h(k, i) and stop at the first empty
slot. The only part that changes between the three methods is the PROBE function. Counting probes is
just i + 1 at the moment the key is placed.

## Pseudocode

```
function PROBE(k, i):
    h1 = ((k mod m) + m) mod m
    if method == LINEAR:    return (h1 + i) mod m
    if method == QUADRATIC: return (h1 + c1*i + c2*i*i) mod m
    h2 = 1 + (((k mod (m-1)) + (m-1)) mod (m-1))
    return (h1 + i*h2) mod m

function HASH_INSERT(T, k):
    for i = 0 to m-1:
        j = PROBE(k, i)
        if T[j] == NIL:
            T[j] = k
            return i + 1                  // probes used
    return -1                             // overflow

main:
    read m, method (and c1, c2), n, keys[1..n]
    T[0..m-1] = NIL, total = 0
    for t = 1 to n:
        p[t] = HASH_INSERT(T, keys[t])
        total = total + (p[t] == -1 ? m : p[t])
    print "Table:" T (NIL as -), "Probes:" p, "Total:" total
```

## Complexity

Each insertion is at most m probes: O(n·m) worst case, O(n / (1 − α)) expected under uniform
hashing (slides: an insertion costs at most 1/(1 − α) expected probes). Space O(m).

## Edge cases / traps

- Negative keys: `((k % m) + m) % m`, also inside h2 (tests/7).
- Quadratic probing can report overflow while free slots remain (tests/6: m = 4, i² mod 4 ∈ {0, 1}).
  Loop at most m times or you get an infinite loop.
- `c2*i*i` and `i*h2` overflow `int` for big m: compute in `long long`.
- Probes vs collisions: probes = collisions + 1. Read the question and say which one you print.
- DOUBLE with m = 1 would divide by zero in `k mod (m-1)`.

## Variants they might ask

- **Different h2** (slides: h2(k) = 8 − (k mod 8), m = 13): change the `h2` line in PROBE.
- **Quadratic h(k, i) = (h'(k) + i²) mod m** (slides): `QUADRATIC 0 1` (tests/5).
- **Search / delete with tombstones afterwards**: use `templates/hash_open_addressing/sol.cpp`.
- **Print the slot of each key instead of the table**: record `j` returned by the loop alongside `p[t]`.

## Files

`sol.cpp` (vector), `sol_manual.cpp` (plain arrays, no STL containers), `brute.cpp` (walks each
probe sequence by stepping; checked on 500 random inputs). Tests: 1–3 Tutorial Q3, 4–5 slides
examples, 6 overflow, 7 negatives, 8 m = 1, 9–10 large.
