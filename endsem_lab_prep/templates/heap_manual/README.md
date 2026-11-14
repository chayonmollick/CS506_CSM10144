# Hand-written binary heap (no STL)

Use this when the paper says "no built-in containers" or the common setup is "implement an
array-based binary heap". `sol.cpp` is a min-heap with a one-flag switch to a max-heap, plus
heapsort, driven by a command list so every operation can be tested.

## Common setup as the exam would state it

Implement an array-based binary min-heap (`struct Heap { long long A[MAXN]; int n; }`, 1-indexed)
with HEAPIFY-DOWN, HEAPIFY-UP, BUILD-HEAP, INSERT, GET-MIN, EXTRACT-MIN, DECREASE-KEY,
INCREASE-KEY and HEAPSORT. Do not use `priority_queue`, `make_heap`, `push_heap` or `pop_heap`.

**Input.** Line 1: N (0 ≤ N ≤ 10^5). Line 2: N integers, built into the heap with BUILD-HEAP
(bottom-up, O(N)). Line 3: Q (1 ≤ Q ≤ 10^5). Then Q commands, one per line:

| Command | Effect | Output |
|---|---|---|
| `insert x` | insert key x | nothing |
| `getMin` | read the minimum | the minimum, or `EMPTY` |
| `extractMin` | remove the minimum | the removed key, or `EMPTY` |
| `decreaseKey i v` | set A[i] = v, 1 ≤ i ≤ size, v ≤ A[i] | nothing, or `INVALID` if i or v is bad |
| `increaseKey i v` | set A[i] = v, 1 ≤ i ≤ size, v ≥ A[i] | nothing, or `INVALID` if i or v is bad |
| `size` | | number of keys |
| `print` | | heap array A[1..size] space-separated, or `EMPTY` |
| `sort` | heapsort a copy, heap unchanged | keys in ascending order, or `EMPTY` |

Keys are in [-10^9, 10^9]. Indices i are positions in the heap array (1 = root), as in the slides.

**Sample Input** (`tests/1.in`)
```
5
9 4 7 1 8
13
print
getMin
insert 3
print
decreaseKey 5 0
print
extractMin
print
increaseKey 1 10
print
decreaseKey 2 50
size
sort
```
**Sample Output**
```
1 4 7 9 8
1
1 4 3 9 8 7
0 1 3 9 4 7
0
1 4 3 9 7
3 4 10 9 7
INVALID
5
3 4 7 9 10
```

## Pseudocode (course style, CLRS max-heap, 1-indexed)

```
function PARENT(i):  return floor(i / 2)
function LEFT(i):    return 2i
function RIGHT(i):   return 2i + 1

function MAX_HEAPIFY(A, i):              // subtrees of i are already max-heaps
    l = LEFT(i)
    r = RIGHT(i)
    largest = i
    if l <= A.heap_size and A[l] > A[largest]:
        largest = l
    if r <= A.heap_size and A[r] > A[largest]:
        largest = r
    if largest != i:
        exchange A[i], A[largest]
        MAX_HEAPIFY(A, largest)

function BUILD_MAX_HEAP(A, n):           // O(n), not O(n log n)
    A.heap_size = n
    for i = floor(n / 2) downto 1:       // indices > n/2 are leaves
        MAX_HEAPIFY(A, i)

function HEAPSORT(A, n):                 // ascending, in place, not stable
    BUILD_MAX_HEAP(A, n)
    for i = n downto 2:
        exchange A[1], A[i]              // max goes to its final slot
        A.heap_size = A.heap_size - 1
        MAX_HEAPIFY(A, 1)

function HEAP_MAXIMUM(A):
    return A[1]

function HEAP_EXTRACT_MAX(A):
    if A.heap_size < 1:
        error "heap underflow"
    max = A[1]
    A[1] = A[A.heap_size]                // last leaf -> root
    A.heap_size = A.heap_size - 1
    MAX_HEAPIFY(A, 1)
    return max

function HEAP_INCREASE_KEY(A, i, key):
    if key < A[i]:
        error "new key is smaller than current key"
    A[i] = key
    while i > 1 and A[PARENT(i)] < A[i]: // bubble up
        exchange A[i], A[PARENT(i)]
        i = PARENT(i)

function MAX_HEAP_INSERT(A, key):
    A.heap_size = A.heap_size + 1
    A[A.heap_size] = -infinity
    HEAP_INCREASE_KEY(A, A.heap_size, key)
```

Min-heap version, which is what `sol.cpp` runs by default: swap every `>` / `<` between keys,
so MAX_HEAPIFY becomes MIN_HEAPIFY (pick the smallest), HEAP_INCREASE_KEY becomes
HEAP_DECREASE_KEY (bubble up while `A[PARENT(i)] > A[i]`) and insert starts from +infinity.
Making a key larger in a min-heap means calling MIN_HEAPIFY(A, i), since the key can only sink.

## How the code maps to the pseudocode

| Pseudocode | `sol.cpp` (`struct Heap`) | Cost |
|---|---|---|
| PARENT / LEFT / RIGHT | `parent(i)`, `left(i)`, `right(i)` | O(1) |
| MAX/MIN-HEAPIFY | `heapifyDown(i)`, loop instead of recursion | O(log n) |
| bubble-up loop of INCREASE-KEY | `heapifyUp(i)` | O(log n) |
| BUILD-MAX/MIN-HEAP | `build(a, cnt)` | O(n) |
| INSERT | `push(key)`: put at A[n+1], heapifyUp | O(log n) |
| MAXIMUM / MINIMUM | `top()` | O(1) |
| EXTRACT-MAX/MIN | `pop()` | O(log n) |
| DECREASE-KEY / INCREASE-KEY | `changeKey(i, key)`: heapifyUp then heapifyDown, only one of them moves | O(log n) |
| HEAPSORT | `heapSort(a, cnt)`: a max-heap gives ascending order | O(n log n) |

## How to adapt it

- **Max-heap:** call `h.init(true)`. Only `higher()` reads the flag, so nothing else changes.
  If you only need one kind, hard-code `higher()` to `x < y` (min) or `x > y` (max).
- **Two heaps at once** (running median): declare `Heap lo, hi;` globally, then
  `lo.init(true); hi.init(false);`.
- **Pairs / records** (Dijkstra, merge k lists): change `long long A[MAXN]` to an array of a
  `struct Item { long long key; int id; }` and compare `.key` in `higher()`. Break ties on
  `.id` if the output depends on it.
- **0-indexed** arrays: parent `(i-1)/2`, children `2i+1`, `2i+2`, root at 0, internal nodes
  `n/2-1 downto 0`. Stay 1-indexed if the paper uses slide indices, as in `increaseKey i v`.
- **Descending heapsort:** run the same loop on a min-heap.
- **Without a struct (plain C):** keep `long long A[MAXN]; int n;` as globals and turn every
  member function into a free function.
- Declare big heaps as globals. A local `Heap` holds a 1.6 MB array and can overflow the stack.

## Complexities, including the Fibonacci heap from the slides

| Operation | Binary heap | Fibonacci heap (amortized) |
|---|---|---|
| INSERT | O(log n) | O(1) |
| MINIMUM | O(1) | O(1) |
| EXTRACT-MIN | O(log n) | O(log n) |
| DECREASE-KEY | O(log n) | O(1) |
| UNION (merge two heaps) | O(n), rebuild | O(1) |

Fibonacci heaps make DECREASE-KEY O(1) amortized, which drops Dijkstra and Prim from
O(E log V) to O(E + V log V). They are theory-only for this exam. Use a binary heap in code.

## Traps

- `extractMin` / `getMin` on an empty heap: check `n == 0` first.
- BUILD-HEAP must loop `i = n/2 downto 1`. Going upwards, or calling heapify on leaves only,
  gives a wrong heap.
- Heapsort is not stable. Ascending order needs a **max**-heap.
- With `int` keys, `-infinity` in MAX-HEAP-INSERT should be `LLONG_MIN` or `INT_MIN`. A magic
  number like `-1` breaks on negative keys. `push()` avoids this by bubbling up directly.

## Files

- `sol.cpp`: the template plus the command driver.
- `brute.cpp`: the slides written literally (recursive, `std::vector`, `std::sort` for `sort`).
  It was compared with `sol.cpp` on random command lists, and every `print` was also checked
  for the heap property.
- `tests/`: sample, empty-heap/`INVALID` cases, duplicates and negatives, and a large case.
