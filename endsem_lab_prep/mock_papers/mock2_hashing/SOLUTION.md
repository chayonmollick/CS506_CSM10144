# Mock 2 — solution

Code: [`a/sol.cpp`](a/sol.cpp), [`b/sol.cpp`](b/sol.cpp). Tests: `../../test.sh mock_papers/mock2_hashing`.

## Common setup
```
struct Node: long long key; int value; Node* next
struct HashTable: int m; Node* slot[0..m-1]      // all NULL at the start

function HASH(T, k):
    return ((k mod T.m) + T.m) mod T.m           // C's % is negative for negative k

function HASH-SEARCH(T, k):
    x = T.slot[HASH(T, k)]
    while x != NULL and x.key != k: x = x.next
    return x

function HASH-INSERT(T, k, v):
    x = HASH-SEARCH(T, k)
    if x != NULL: x.value = v; return
    s = HASH(T, k)
    T.slot[s] = new Node(k, v, next = T.slot[s])  // insert at the head, O(1)

function HASH-DELETE(T, k):
    p = address of T.slot[HASH(T, k)]            // pointer to the link into the node
    while *p != NULL and (*p).key != k: p = address of (*p).next
    if *p == NULL: return false
    d = *p; *p = d.next; free d
    return true
```
Expected time: O(1 + α) per operation, where α = n/m. Worst case: Θ(n), when everything lands in one chain.

## (a)
Run each command in turn. Then for each slot i, print `i:` and walk the chain.
- Because inserts go to the head, the most recently inserted key comes first.
- Trace for slot 3 of the sample: 10, 3, 17, −4 hash to 3 (−4 mod 7 = 3 after the fix).
  - Each insert puts its key at the head, giving `-4 17 3 10`.
  - `D 3` removes 3.
  - `I 31` puts 31 at the head, giving `31 -4 17 10`.

## (b)
```
P = 0; HASH-INSERT(T, 0, 0)              // prefix sum 0 at index 0
best = 0
for j = 1 to n:
    P = P + a[j]
    x = HASH-SEARCH(T, P - K)            // a[i+1..j] sums to K  <=>  P[i] = P[j] - K
    if x != NULL and j - x.value > best:
        best = j - x.value; L = x.value + 1; R = j
    if HASH-SEARCH(T, P) == NULL:
        HASH-INSERT(T, P, j)             // store only the FIRST index of each prefix sum
print best == 0 ? "0" : "best L R"
```
- **Why the first index:** the longest subarray ending at j starts right after the *earliest* i with P[i] = P[j] − K.
- **Why `>` and not `>=`:** for the same length, the one found first ends first, so it also starts first.
- **Why not a sliding window:** negative numbers break it, because the window sum is not monotone.

Time: O(n) expected.

**Variants:**
- *Count* the subarrays with sum K: store how many times each prefix occurred and add that count.
- Longest subarray with equal numbers of 0s and 1s: map 0 → −1 and use K = 0.
- Divisible by k: key = P mod k.
