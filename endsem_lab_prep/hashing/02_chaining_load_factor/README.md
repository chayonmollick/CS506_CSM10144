# 02. Hash Table with Chaining: Queries, Load Factor and Longest Chain

Source: slides "Hash tables" (CHAINED-HASH-INSERT/SEARCH/DELETE, h(k) = k mod 8 example, load factor
α = n/m); Tutorial 8 Q1–Q2 (chain lengths, worst case Θ(n)).

## Problem

Common setup: a hash table with m slots and separate chaining, h(k) = k mod m (non-negative, so
−6 mod 5 = 4). Each slot holds a singly linked list; a new key is inserted at the **head** of its list.
A key that is already in the table is not inserted again.

Insert the n given keys in order. Then answer q queries:

- `S x`: print `FOUND` if x is in the table, else `NOT FOUND`.
- `D x`: delete x; print `DELETED`, or `NOT FOUND` if x is not in the table.

After the queries print every chain, the load factor α = (keys now stored) / m with 2 decimals, and
the longest chain (smallest slot index on ties).

**Input**
Line 1: m n. Line 2: n keys (empty line if n = 0). Line 3: q. Next q lines: `S x` or `D x`.

**Output**
One line per query, then m lines `i: k1 k2 ...` (chain i from head to tail; just `i:` if empty), then
```
Load factor: <alpha, 2 decimals>
Longest chain: slot <i>, length <L>
```

**Constraints**
1 ≤ m ≤ 10^4, 0 ≤ n ≤ 10^5, 1 ≤ q ≤ 10^5, keys in [−10^9, 10^9].

**Sample Input**
```
8 8
18 41 22 44 59 32 31 73
6
S 73
S 10
D 22
D 100
D 44
S 22
```

**Sample Output**
```
FOUND
NOT FOUND
DELETED
NOT FOUND
DELETED
NOT FOUND
0: 32
1: 73 41
2: 18
3: 59
4:
5:
6:
7: 31
Load factor: 0.75
Longest chain: slot 1, length 2
```

(41 and 73 both hash to 1; 73 came later so it is at the head. 6 keys remain, 6/8 = 0.75.)

## Idea

This is the chaining template plus two counters. Keep `stored` (incremented on a real insert,
decremented on a real delete) for α = stored/m, and measure each chain's length while printing it,
remembering the first maximum.

## Pseudocode

```
function HASH(k): return ((k mod m) + m) mod m

function CHAINED_HASH_INSERT(T, k):
    if CHAINED_HASH_SEARCH(T, k) != NULL: return
    x = Node(k, T[HASH(k)]); T[HASH(k)] = x
    stored = stored + 1

function CHAINED_HASH_DELETE(T, k):
    prev = NULL, cur = T[HASH(k)]
    while cur != NULL and cur.key != k: prev = cur, cur = cur.next
    if cur == NULL: return false
    if prev == NULL: T[HASH(k)] = cur.next else prev.next = cur.next
    stored = stored - 1
    return true

function REPORT(T):
    best = 0, bestLen = 0
    for i = 0 to m-1:
        len = 0
        print i ":"
        for each node p in chain T[i]: print p.key, len = len + 1
        if len > bestLen: best = i, bestLen = len        // strict > keeps smallest slot
    print "Load factor:" stored / m (2 decimals)
    print "Longest chain: slot" best ", length" bestLen
```

## Complexity

Each insert/search/delete is O(1 + chain length), expected O(1 + α). The report is O(m + n).
Space O(m + n).

## Edge cases / traps

- Duplicate keys in the input must not be counted twice in α (tests/3).
- α counts keys *now* stored, after the deletions, and can exceed 1 with chaining (tests/4: m = 1, α = 2.00).
- Empty table: α = 0.00 and longest chain is slot 0 with length 0 (tests/2).
- Print α with `fixed << setprecision(2)` (or `printf("%.2f")`); integer division `stored / m` gives 0.
- Deleting the head of a chain: update `T[slot]`, not `prev->next`.

## Variants they might ask

- **Average chain length over non-empty chains**: count non-empty chains `c` and print `stored / c`.
- **Expected search cost** (slides): successful ≈ 1 + α/2, unsuccessful ≈ α; or compute the exact
  average comparisons for a successful search as Σ L_i(L_i+1)/2 / n over chains.
- **Insert at the tail** (some papers): walk to the last node before linking; chains print oldest first.
- **Rehash when α > 1**: allocate 2m+1 slots, re-insert every node, free the old table.

## Files

`sol.cpp` (`std::list`), `sol_manual.cpp` (own `Node` lists, no STL containers), `brute.cpp`
(one vector of keys, chains rebuilt at the end). 500 random inputs agree.
