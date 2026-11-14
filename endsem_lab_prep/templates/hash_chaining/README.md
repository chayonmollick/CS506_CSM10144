# Template: hash table with separate chaining (hand-written)

Source: lecture slides "Hash tables" (CHAINED-HASH-INSERT / SEARCH / DELETE, h(k) = k mod 8 example).

Use this when the paper says something like *"Common setup: implement a hash table with chaining:
struct + insert / search / delete. Do not use STL containers."* `sol.cpp` uses no STL containers: its
own `Node` linked lists and a `Node**` array of chain heads.

## I/O of `sol.cpp`

```
Input : m q            (m = number of slots, q = number of operations)
        q lines:  I x  | S x  | D x  | P
Output: I x -> nothing (x is ignored if already present)
        S x -> FOUND / NOT FOUND
        D x -> DELETED / NOT FOUND
        P   -> m lines "i: k1 k2 ..."  (chain i from head to tail; "i:" if empty)
```

Sample (slides: insert 18 41 22 44 59 32 31 73 with h(k) = k mod 8, each at the head of its chain):

```
8 9          0: 32
I 18         1: 73 41
I 41         2: 18
...          ...
I 73         5:
P            7: 31
```

## Pseudocode (course style)

```
struct Node:
    int key
    Node* next

function HASH(k, m):
    return ((k mod m) + m) mod m          // C++ % can be negative for k < 0

function INIT(T, m):
    for i = 0 to m-1:
        T[i] = NULL

function CHAINED_HASH_SEARCH(T, k):
    p = T[HASH(k, m)]
    while p != NULL:
        if p.key == k: return p
        p = p.next
    return NULL

function CHAINED_HASH_INSERT(T, k):
    if CHAINED_HASH_SEARCH(T, k) != NULL: return     // keep keys distinct
    j = HASH(k, m)
    x = Node(k, T[j])        // new node points to the old head
    T[j] = x                 // O(1): insert at the head

function CHAINED_HASH_DELETE(T, k):
    j = HASH(k, m)
    prev = NULL, cur = T[j]
    while cur != NULL and cur.key != k:
        prev = cur, cur = cur.next
    if cur == NULL: return false            // not present
    if prev == NULL: T[j] = cur.next        // deleting the head
    else: prev.next = cur.next
    free cur
    return true

function PRINT(T):
    for i = 0 to m-1:
        print i ":" followed by the keys of chain i, head first
```

Cost: O(1) to hash plus O(chain length); expected Θ(1 + α) for every operation, α = n/m (slides).

## How to adapt

- **Key → value map** (counts, first index, totals): add `long long val` to `Node`; `insert` updates
  `val` when the key exists. `hashing/04_subarray_sum_k/sol_manual.cpp` (counts) and
  `hashing/05_longest_equal_01/sol_manual.cpp` (first index) show this.
- **Hash set for big keys** (prefix sums, values up to 1e9): change `int key` to `long long key` and use
  `((k % m) + m) % m` with `long long`. See `hashing/11_longest_consecutive/sol_manual.cpp`.
- **Pick m**: a prime not near a power of 2 (slides: m = 701 for 2000 keys); e.g. 100003 when n ≤ 1e5.
- **Duplicates allowed**: drop the search at the top of `chainInsert`.
- **Insert at the tail / keep chains sorted**: walk to the last node (or the first larger key) before
  linking. Only do this if the question says so; the slides insert at the head.
- **Load factor / longest chain**: count nodes per chain while printing. See `hashing/02_chaining_load_factor`.
- **String keys**: polynomial hash with Horner's rule, `h = (h * 31 + c) mod m`, then chain as usual.
- **Universal hashing**: replace `hashFn` with `((a*k + b) mod p) mod m` (p prime > every key,
  1 ≤ a < p, 0 ≤ b < p). Use `long long` for `a*k`.

## Traps

- `k % m` is negative for negative k in C/C++. Always use `((k % m) + m) % m`.
- When deleting, handle the head of the chain separately (or use a `Node**` to the link).
- `S` and `D` must print exactly `FOUND` / `NOT FOUND` / `DELETED`. Check the paper's wording.
- `new Node[m]` is not the same as `new Node*[m]`: the table is an array of *pointers*.

## Tests

`tests/1` is the slides example; 2 = deletes at head/middle/tail, duplicate insert; 3 = negative keys;
4 = m = 1 (everything in one chain); 5 = 120 random operations (checked against `brute.cpp`).
