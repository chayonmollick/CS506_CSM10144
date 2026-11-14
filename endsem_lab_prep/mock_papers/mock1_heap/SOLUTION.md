# Mock 1 — solution

Code: [`a/sol.cpp`](a/sol.cpp), [`b/sol.cpp`](b/sol.cpp). Tests: `../../test.sh mock_papers/mock1_heap`.

## Common setup
```
struct MinHeap:
    int a[1..MAX]          // a[0] unused
    int size

function MIN-HEAPIFY(H, i):
    l = 2i, r = 2i + 1, smallest = i
    if l <= H.size and H.a[l] < H.a[smallest]: smallest = l
    if r <= H.size and H.a[r] < H.a[smallest]: smallest = r
    if smallest != i:
        swap H.a[i], H.a[smallest]
        MIN-HEAPIFY(H, smallest)

function BUILD-MIN-HEAP(H):
    for i = floor(H.size / 2) downto 1:
        MIN-HEAPIFY(H, i)

function HEAP-INSERT(H, x):
    H.size = H.size + 1
    H.a[H.size] = x
    i = H.size
    while i > 1 and H.a[parent(i)] > H.a[i]:      // parent(i) = floor(i/2)
        swap H.a[i], H.a[parent(i)]
        i = parent(i)

function HEAP-EXTRACT-MIN(H):
    if H.size < 1: error "heap underflow"
    min = H.a[1]
    H.a[1] = H.a[H.size]
    H.size = H.size - 1
    MIN-HEAPIFY(H, 1)
    return min
```

## (a)
```
read N, H.a[1..N]; H.size = N
BUILD-MIN-HEAP(H)
print H.a[1..N]
read k
repeat k times: print HEAP-EXTRACT-MIN(H)
```
Time: O(N) to build + O(k log N). The array you print **must** come from bottom-up
BUILD-MIN-HEAP. N insertions give a valid heap, but a different array.

Hand trace of the sample (only i = 5 and i = 1 swap anything):
- i = 5: 16 > 7, so swap → `4 1 3 2 7 9 10 14 8 16`
- i = 1: 4 swaps with 1, then with 2 → `1 2 3 4 7 9 10 14 8 16`

## (b)
```
low  = empty min-heap storing -x    // max-heap of the smaller half
high = empty min-heap               // the larger half
for each x:
    if low.size == 0 or x <= -low.a[1]: HEAP-INSERT(low, -x)
    else: HEAP-INSERT(high, x)
    if low.size > high.size + 1: HEAP-INSERT(high, -HEAP-EXTRACT-MIN(low))
    else if high.size > low.size: HEAP-INSERT(low, -HEAP-EXTRACT-MIN(high))
    print -low.a[1]                 // lower median
```
**Invariant:** every element of `low` ≤ every element of `high`, and `low` has the same size as `high` or one more. So the top of `low` is element number ⌈count/2⌉ of the sorted order, which is the lower median.

Time: O(log N) per number.

**Variants:**
- Upper median: keep the extra element in `high` and print `high.a[1]`.
- Average of the two middles: print `(top(low) + top(high)) / 2.0` when the count is even.
