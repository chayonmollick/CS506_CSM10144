# Template: open addressing (linear / quadratic / double hashing) with tombstones

Source: lecture slides "Hash tables" (HASH-INSERT, HASH-SEARCH, linear / quadratic / double hashing,
"You can't just empty a slot on delete": tombstones) and Tutorial 8 Q3.

One array of m slots, at most one key per slot. A slot is NIL (never used), a key, or DELETED
(tombstone). `sol.cpp` uses no STL containers.

## I/O of `sol.cpp`

```
Input : m
        LINEAR | QUADRATIC c1 c2 | DOUBLE
        q, then q lines:  I x | S x | D x | P
Output: I x -> "slot j probes p" | DUPLICATE | OVERFLOW
        S x -> "FOUND j probes p" | "NOT FOUND probes p"
        D x -> "DELETED j" | NOT FOUND
        P   -> the m slots on one line: the key, "-" for NIL, "D" for a tombstone
```

Probe i = 0, 1, ..., m-1 with h'(k) = k mod m (non-negative):

| method    | h(k, i)                                    |
|-----------|--------------------------------------------|
| LINEAR    | (h'(k) + i) mod m                          |
| QUADRATIC | (h'(k) + c1·i + c2·i²) mod m               |
| DOUBLE    | (h'(k) + i·h2(k)) mod m, h2(k) = 1 + (k mod (m−1)) |

**Probes** = number of slots examined, including the last one (a key placed at its home slot uses
1 probe). `I x` first searches for x and prints `DUPLICATE` if it is there; the probes printed are
those of the insertion loop only.

## Tutorial 8 Q3 (checked by hand and by `brute.cpp`)

Keys 10 22 31 4 15 28 17 88 59, m = 11.

| method | final table (slots 0..10) | probes per key | total |
|---|---|---|---|
| linear (tests/1) | 22 88 - - 4 15 28 17 59 31 10 | 1 1 1 1 2 1 2 2 5 | 16 |
| quadratic c1=1, c2=3 (tests/2) | 22 - 88 17 4 - 28 59 15 31 10 | 1 1 1 1 2 1 4 9 3 | 23 |
| double, h2 = 1 + (k mod 10) (tests/3) | 22 - 59 17 4 15 28 88 - 31 10 | 1 1 1 1 3 1 2 3 3 | 16 |

Quadratic needs the most: with m = 11, c1 = 1, c2 = 3 the probe sequence is not a permutation of the
slots (88 starts at 0 and visits 0, 4, 3, 8, 8, 3, 4, 0, 2: repeats before finding slot 2), and keys with
the same h'(k) follow the same path (secondary clustering). Linear suffers primary clustering
(59 walks 4→5→6→7→8).

## Pseudocode (course style)

```
NIL = empty slot, DELETED = tombstone

function PROBE(k, i):
    h1 = ((k mod m) + m) mod m
    if method == LINEAR:    return (h1 + i) mod m
    if method == QUADRATIC: return (h1 + c1*i + c2*i*i) mod m
    h2 = 1 + (((k mod (m-1)) + (m-1)) mod (m-1))
    return (h1 + i*h2) mod m

function HASH_SEARCH(T, k):
    for i = 0 to m-1:
        j = PROBE(k, i)
        if T[j] == k: return j            // found after i+1 probes
        if T[j] == NIL: return NOT-FOUND  // an empty slot ends the search
        // DELETED: keep probing
    return NOT-FOUND

function HASH_INSERT(T, k):
    if HASH_SEARCH(T, k) != NOT-FOUND: return DUPLICATE
    for i = 0 to m-1:
        j = PROBE(k, i)
        if T[j] == NIL or T[j] == DELETED:   // a tombstone may be reused
            T[j] = k
            return j                         // used i+1 probes
    return OVERFLOW

function HASH_DELETE(T, k):
    j = HASH_SEARCH(T, k)
    if j == NOT-FOUND: return NOT-FOUND
    T[j] = DELETED                        // NOT NIL: later keys may have probed past j
    return j
```

## How to adapt

- **Only build the table** (Tutorial Q3 style): see `hashing/01_open_addressing_build`.
- **Other h2** (slides: h2(k) = 8 − (k mod 8), or R − (k mod R) with prime R < m): change the line
  computing `h2` in `probe`. h2 must never be 0, and m prime makes every sequence a permutation.
- **Quadratic as on the slides**, h(k,i) = (k mod 13 + i²) mod 13: `QUADRATIC 0 1`.
- **Count probes of an unsuccessful search**: `hashSearch` already sets `probes`.
- **Rehash** when α = n/m passes 0.5–0.7 or tombstones pile up: make a table of size about 2m (next
  prime) and re-insert every real key (skip DELETED).
- **Key range includes INT_MIN**: keep a separate `state[]` array (EMPTY / FULL / DELETED) instead of
  sentinel values (that is what `brute.cpp` does).

## Traps

- Deleting by writing NIL breaks searches for keys that probed past that slot (tests/4: after deleting
  7 and 0, 14 is still found because slots 0 and 1 hold tombstones).
- Quadratic probing may fail to find a free slot even when the table is not full (tests/5: m = 4,
  i² mod 4 ∈ {0, 1}, so key 8 reports OVERFLOW). Always stop after m probes.
- `c2*i*i` overflows `int` for large m. Use `long long`.
- h2(k) = 1 + (k mod (m−1)) needs m ≥ 2; for negative k take the non-negative mod first.
- Say what you count: "probes" here = slots examined. Some books count collisions = probes − 1.

## Tests

1–3 = Tutorial Q3 (linear, quadratic 1 3, double); 4 = tombstones (search and insert past DELETED);
5 = quadratic overflow, duplicate, negative key; 6 = double hashing with deletes and negative keys;
7–8 = 150 / 60 random operations (checked against `brute.cpp`).
