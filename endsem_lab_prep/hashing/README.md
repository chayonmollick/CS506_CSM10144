# Hashing: end-sem lab prep

Every folder has `README.md` (exam-style statement, idea, course-style pseudocode, complexity, traps,
variants), `sol.cpp` (C++11, stdin → stdout), `tests/` and usually `brute.cpp`. Folders marked
**manual** also have `sol_manual.cpp`, the same program with a hand-written hash table (no
`unordered_map` / `unordered_set`) in case STL containers are not allowed.

Hand-written tables to copy from: `../templates/hash_chaining` (chaining: insert / search / delete /
print) and `../templates/hash_open_addressing` (linear / quadratic / double hashing with tombstones).

Run the tests from `endsem_lab_prep/`: `./test.sh hashing templates/hash_chaining templates/hash_open_addressing`.

## Index

| No. | Problem | Technique | Source |
|-----|---------|-----------|--------|
| 01 | [Open addressing: build table, probes](01_open_addressing_build) (manual) | linear / quadratic / double hashing, count probes | Tutorial 8 Q3, slides |
| 02 | [Chaining: queries, load factor, longest chain](02_chaining_load_factor) (manual) | chained table, head insertion, α = n/m | slides (CHAINED-HASH-*) |
| 03 | [Two sum](03_two_sum) | complement lookup, value → first index | LeetCode 1, Practice Set 3 Q2 |
| 04 | [Count subarrays with sum K](04_subarray_sum_k) (manual) | prefix sum + count map | Tutorial 8 Q10(a), LeetCode 560 |
| 05 | [Longest subarray with equal 0s and 1s](05_longest_equal_01) (manual) | 0 → −1, prefix + first-index map | Tutorial 8 Q10(b), LeetCode 525 |
| 06 | [Longest well-performing interval](06_longest_well_performing_interval) | ±1 scores, first occurrence of s − 1 | LeetCode 1124, Practice Set 3 Q3 |
| 07 | [Minimum window substring](07_minimum_window_substring) | sliding window + count table | LeetCode 76, Practice Set 3 Q13 |
| 08 | [Longest repeated substring](08_longest_repeated_substring) | binary search on length + Rabin–Karp, verify on hash match | Tutorial 8 Q11, LeetCode 1044 |
| 09 | [Rabin–Karp pattern search](09_rabin_karp_search) | rolling hash, spurious-hit check | Tutorial 8 (rolling hash), CLRS |
| 10 | [Farmer totals and heavy hitters (> n/k)](10_farmer_totals_heavy_hitters) | hash totals; Misra–Gries two passes | Tutorial 8 Q12 |
| 11 | [Longest consecutive sequence](11_longest_consecutive) (manual) | hash set, walk only from run starts | LeetCode 128 |
| 12 | [Distinct elements in every window of size k](12_distinct_in_windows) | sliding window + count map, erase at 0 | GfG classic |
| 13 | [First non-repeating / first repeating element](13_first_unique_and_repeating) | count map, second pass in array order | GfG classic, LeetCode 387 |
| 14a | [Count pairs with difference k](14a_pairs_with_difference_k) | count map, partners x − k and x + k | GfG classic, LeetCode 2006 |
| 14b | [Longest subarray with sum K (zero-sum)](14b_longest_subarray_sum_k) | prefix sum + first-index map | GfG "largest zero-sum subarray" |
| 15 | [Division / multiplication / universal hash values](15_hash_functions) | h(k) formulas, Knuth's A | Tutorial 8 Q4, Q6 |

## How to recognise a hashing problem

- **"Subarray with sum K / sum 0 / equal 0s and 1s", negatives allowed** → prefix sums + hash map.
  Count map for "how many" (04), first-index map for "longest" (05, 14b), and seed the map with the
  empty prefix (0 → count 1, or 0 → index −1).
- **"Longest" with prefix sums** → store the **first** occurrence only, never overwrite (05, 06, 14b).
- **"Find a pair with sum / difference"** → for each element look up its partner among the elements
  before it, then insert it (03, 14a). Look up before insert so an element never pairs with itself.
- **"In every window of size k" / "smallest window containing"** → sliding window + count table;
  erase keys whose count drops to 0 so `size()` = number of distinct values (07, 12).
- **"Frequency / first unique / duplicates / totals per ID"** → one counting pass, then a second pass
  in input order (10, 13). Iterating a hash map is in *no* particular order.
- **"Consecutive values, any order, O(n)"** → hash set, start only where x − 1 is absent (11).
- **"Repeated / matching substring"** → rolling hash (Rabin–Karp); always compare characters on a
  hash match (08, 09). Binary search on the length when "exists for L ⇒ exists for L − 1".
- **"IDs are huge (12 digits), only a few used"** → hash map, not a direct-address array; the
  universe is too big (10). If the range is small (e.g. prefix sums in [−n, n]) an array works too.
- **"More than n/k times with O(k) memory"** → Misra–Gries: k − 1 counters, then a verifying pass (10).
- **"Show the table / probes / chains"** → simulate the textbook procedure exactly (01, 02, templates).

## Three most likely exam questions

1. **Common setup: hash table with chaining** (struct Node, `h(k) = k mod m`, insert at head, search,
   delete). (a) Insert keys, answer search/delete queries, print the chains with the load factor and
   longest chain (02). (b) Use *your* table to solve an application: two sum / count subarrays with sum K /
   longest consecutive sequence (03, 04, 11 with `sol_manual.cpp`).
2. **Common setup: open addressing** with linear, quadratic and double hashing. (a) Insert keys and
   print the final table and probes per insertion (01, exactly Tutorial Q3). (b) Delete with tombstones,
   then search and insert again (`templates/hash_open_addressing`).
3. **Prefix-sum hashing pair**: (a) count subarrays with sum K (04), (b) longest subarray with equal
   0s and 1s or longest zero-sum subarray (05, 14b). Close runner-up: Rabin–Karp search (09) and the
   longest repeated substring (08).

## STL quick reference (C++11; `#include <unordered_map>`, `<unordered_set>`, `<map>`)

```cpp
unordered_map<long long, int> cnt;      // hash map, O(1) expected per operation
cnt.reserve(2 * n);                     // optional: avoid rehashing
cnt[x]++;                               // operator[] INSERTS x with value 0 if missing
if (cnt.find(x) != cnt.end()) ...       // lookup without inserting
if (cnt.count(x)) ...                   // 0 or 1
unordered_map<long long, int>::iterator it = cnt.find(x);   // it->first = key, it->second = value
cnt.insert(make_pair(x, i));            // does NOT overwrite an existing key (good for "first index")
cnt.erase(x);                           // by key; returns number erased (0/1)
for (auto& kv : cnt) { kv.first; kv.second; }               // order is unspecified
for (auto it = cnt.begin(); it != cnt.end(); ) {            // erase while iterating
    if (it->second == 0) it = cnt.erase(it); else ++it;
}
cnt.size(); cnt.empty(); cnt.clear();

unordered_set<long long> S(a.begin(), a.end());             // distinct values
bool isNew = S.insert(x).second;        // false if x was already there
S.count(x); S.erase(x);

map<long long, long long> ordered;      // balanced BST: O(log n), iterates in increasing key order
```

**Pitfalls**

- `m[x]` in a condition (`if (m[x] > 0)`) silently inserts x; use `find`/`count` when only checking.
- Iteration order of `unordered_*` is arbitrary: never print "in order" from it; keep a vector of keys
  in input order, or sort, or use `map`.
- No built-in hash for `pair<int,int>`: use `map<pair<int,int>,int>`, or encode as one `long long`
  (`a * 2000000001LL + b`).
- Erasing during a range-for invalidates the iterator: use the `it = erase(it)` loop above.
- Value type `int` overflows for counts of pairs / subarrays (up to ~n²/2): use `long long`.
- `size()` is unsigned: compare with `(int)v.size()` or use `size_t` loop counters to avoid
  `-Wsign-compare` warnings.
- If the paper bans STL containers, everything above becomes a chained table of `Node {key, value,
  next}` (see the `sol_manual.cpp` files): `find` = walk the chain, `operator[]++` = find or insert at head.
