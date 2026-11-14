# Heap / priority queue: end-sem lab prep

Each folder has `README.md` (exam-style statement, idea, course-style pseudocode, complexity,
traps, variants), `sol.cpp` (C++11, stdin → stdout), `brute.cpp` (naive checker) and `tests/`
(`1.in` is the README sample). The `sol_manual.cpp` files use a hand-written heap with no STL
containers, in case the paper bans them. The full hand-written heap with every operation is in
[`../templates/heap_manual`](../templates/heap_manual).

Run all tests: `./test.sh heap templates/heap_manual` from `endsem_lab_prep/`.

## Index

| No. | Problem | Technique | Source |
|---|---|---|---|
| T | [Hand-written heap template](../templates/heap_manual) | array heap: heapify up/down, build O(n), insert, extract, decrease/increase-key, heapsort | Heap Sort slides |
| 01 | [Min-heap operations by command](01_heap_operations) | insert / getMin / removeMin (common setup) | exam-style, slides 28–30 |
| 02 | [BUILD-MAX-HEAP and HEAPSORT](02_build_heap_heapsort) | MAX-HEAPIFY bottom-up, in-place sort | Heap Sort slides (A = 4 1 3 2 16 9 10 14 8 7) |
| 03 | [Max-priority queue](03_max_priority_queue) | EXTRACT-MAX, INCREASE-KEY by index, MAX-HEAP-INSERT | Heap Sort slides 28–31 |
| 04 | [Fix a heap operation log](04_cf681c_fix_heap_log) | replay on a min-heap, greedy patching | Practice Set 3 Q6, Codeforces 681C |
| 05 | [K-th largest (array + stream)](05_kth_largest) | min-heap of size K | LeetCode 215 / 703 |
| 06 | [Merge K sorted arrays](06_merge_k_sorted) | k-way merge, heap of (value, list, index) | LeetCode 23 |
| 07 | [Running median](07_running_median) | two heaps (max-heap low half, min-heap high half) | Practice Set 3 Q14, LeetCode 295 |
| 08 | [Task scheduler](08_task_scheduler) | max-heap of counts, cycles of n+1, plus formula | Practice Set 3 Q7, LeetCode 621 |
| 09 | [Top-K frequent elements](09_top_k_frequent) | hash map + size-K min-heap | LeetCode 347 |
| 10 | [Dijkstra shortest paths](10_dijkstra) | min-heap + lazy deletion | slides (PQ applications), Fibonacci-heap slide |
| 11 | [Connect ropes, minimum cost](11_connect_ropes) | greedy: join the two smallest (Huffman) | classic / LeetCode 1167 |
| 12 | [Sort a K-sorted array](12_k_sorted_array) | min-heap of size K+1 | classic |
| 13 | [Check heap / convert min → max](13_check_convert_heap) | parent-child scan, BUILD-MAX-HEAP | classic, slides |
| 14 | [K closest points to origin](14_k_closest_points) | max-heap of size K on (d², x, y) | LeetCode 973 |
| 15 | [Sliding window maximum](15_sliding_window_max) | max-heap + lazy deletion (deque O(n) alt.) | LeetCode 239 |
| 16 | [Last stone weight](16_last_stone_weight) | max-heap simulation | LeetCode 1046 |
| 17 | [Reorganize string](17_reorganize_string) | max-heap greedy, hold back the previous letter | LeetCode 767 |

## How to recognise a heap problem

- **"K largest / K smallest / K most frequent / K closest"**: a heap of size K of the
  **opposite** type. Use a min-heap to keep the largest, so its root is the K-th largest
  (05, 09, 14).
- **"Repeatedly take the smallest (or largest) one or two, combine, put back"**: a greedy with a
  heap (11 ropes / Huffman, 16 stones, 08 scheduler, 17 reorganize).
- **"Merge K sorted lists/arrays/streams"**: k-way merge with a heap of K heads (06).
- **"Median / balance of a stream"**: two heaps whose sizes differ by at most 1 (07).
- **"Shortest path / cheapest cost with non-negative weights"**: Dijkstra with a min-heap of
  (dist, vertex) (10).
- **"Nearly sorted, each element at most K away"**: a sliding heap of size K+1 (12).
- **"Window max/min while elements expire"**: heap + lazy deletion, or a monotonic deque (15).
- **"Implement a priority queue with insert / extract / increase-key", "build a heap", "heap
  sort"**: hand-write it (template, 01–03, 13).
- **"Process events in time order" / "always serve the most urgent job"**: a min-heap on time or
  a max-heap on priority.
- If you also need arbitrary deletion, predecessor/successor or ordered iteration, a heap is the
  wrong tool. Use `set`/`multiset`, or lazy deletion if only the top matters.

## The 3 most likely exam questions

The paper follows the mid-sem format: a common setup reused by parts (a) and (b).

1. **Common setup: an array-based binary min/max-heap** (struct + heapify-down/up, build, insert,
   extract). Part (a) is likely the priority-queue operations or heapsort on it: **01, 02, 03**,
   with the full set in `templates/heap_manual`. Expect the slide example
   `4 1 3 2 16 9 10 14 8 7` and printed heap arrays. That means CLRS layout, so do not use
   `make_heap`.
2. **A Practice Set 3 heap problem** done with the setup heap: **07 running median** (two heaps)
   or **04 Codeforces 681C heap operations log**. **08 task scheduler** is the third one from the
   set.
3. **Top-K style with the setup heap**: **05 K-th largest / stream**, **09 top-K frequent**
   (heap + hashing, both on the syllabus) or **06 merge K sorted arrays**.

## STL quick reference (C++11)

```cpp
#include <queue>        // priority_queue
#include <vector>
#include <functional>   // greater
#include <algorithm>    // make_heap, push_heap, pop_heap, sort_heap

priority_queue<int> mx;                                    // MAX-heap (default)
priority_queue<int, vector<int>, greater<int> > mn;        // MIN-heap
mx.push(5); mx.top(); mx.pop(); mx.empty(); mx.size();     // pop() returns void!

// pairs compare lexicographically: first, then second
typedef pair<long long, int> P;                            // (dist, vertex)
priority_queue<P, vector<P>, greater<P> > pq;              // smallest dist on top
pq.push(make_pair(0LL, s));                                // C++11: no {a, b} needed but allowed

// custom comparator struct: return true if a has LOWER priority than b (a sits below b)
struct Job { int pri; int id; };
struct Cmp {
    bool operator()(const Job& a, const Job& b) const {
        if (a.pri != b.pri) return a.pri < b.pri;          // larger pri on top
        return a.id > b.id;                                // tie: smaller id on top
    }
};
priority_queue<Job, vector<Job>, Cmp> jobs;

// heap algorithms on a vector (max-heap by default; pass the SAME comparator to every call)
vector<int> v(a, a + n);
make_heap(v.begin(), v.end());                             // O(n)
v.push_back(x); push_heap(v.begin(), v.end());             // insert
pop_heap(v.begin(), v.end()); int top = v.back(); v.pop_back();   // extract-max
sort_heap(v.begin(), v.end());                             // ascending (needs a valid max-heap)
make_heap(v.begin(), v.end(), greater<int>());             // min-heap version
```

**Pitfalls**

- The comparator is backwards from what you expect. `less` (default) gives a **max**-heap and
  `greater` gives a **min**-heap. In a custom struct, `return a.key > b.key` gives a min-heap on
  key.
- **No DECREASE-KEY / no arbitrary erase** in `priority_queue`. Push the new value and skip stale
  entries when they surface (**lazy deletion**: `if (d != dist[u]) continue;`). Or hand-write a
  heap with a position array, or use `set<pair<...> >` with erase plus insert.
- `top()` / `pop()` on an empty queue is undefined behaviour. Always check `empty()`.
- You cannot iterate a `priority_queue`. To print it, copy it and pop the copy. Popping gives
  sorted order, **not** the internal array layout.
- `make_heap` may give a different layout from CLRS BUILD-MAX-HEAP when keys repeat (libstdc++
  example: `0 1 0 2 3 3` → `3 3 0 2 1 0`, CLRS → `3 2 3 0 1 0`). When the heap array itself is
  printed, hand-write MAX-HEAPIFY.
- `pq.size()` is `size_t`. Compare as `(int)pq.size() > k` to avoid `-Wsign-compare` warnings.
- Sums of keys (ropes, Dijkstra, median of two middles) overflow `int`. Use `long long`.
- Write `> >` with a space in nested templates if the grader's compiler is old. C++11 accepts
  `>>`.
- C++11 has no generic lambdas. A lambda comparator needs
  `priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);`. The struct form is simpler.
