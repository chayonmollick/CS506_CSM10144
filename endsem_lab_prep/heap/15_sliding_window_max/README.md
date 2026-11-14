# 15. Sliding window maximum

Source: exam-style variant of LeetCode 239 "Sliding Window Maximum",
<https://leetcode.com/problems/sliding-window-maximum/>.

## Problem

Given N integers and a window size K, print the maximum of every window of K consecutive
elements, from left to right.

**Input.** Line 1: N and K (1 ≤ K ≤ N ≤ 10^5). Line 2: N integers in [-10^9, 10^9].

**Output.** One line with N − K + 1 maxima, space-separated.

**Sample Input**
```
8 3
1 3 -1 -3 5 3 6 7
```
**Sample Output**
```
3 3 5 5 6 7
```

## Idea

Push `(value, index)` into a max-heap. A binary heap cannot delete an arbitrary element cheaply,
so do not remove elements when they leave the window. Instead, before reading the top, pop while
the top's index is outside the window (`index ≤ i − K`). This is **lazy deletion**. Stale entries
deep in the heap do no harm, because only the top is ever read.

**Deque alternative (O(N)):** keep a deque of indices whose values are decreasing. For each i,
pop from the back while `a[back] ≤ a[i]`, push i, pop the front if it is `≤ i − K`, and the
front is the maximum. Mention it as the optimal method. The heap version is what this topic
tests.

## Pseudocode

```
function SLIDING_MAX(a[0..N-1], K):
    H = empty max-heap of (value, index)
    res = []
    for i = 0 to N - 1:
        INSERT(H, (a[i], i))
        if i >= K - 1:
            while MAX(H).index <= i - K:    // left the window
                EXTRACT_MAX(H)
            res.append(MAX(H).value)
    return res
```

## Complexity

Each element is pushed once and popped at most once: O(N log N) time, O(N) space (the heap can
hold stale entries). The deque method is O(N) time and O(K) space.

## Edge cases / traps

- K = 1: the output is the array itself. K = N: one value, the global maximum.
- The window check is `index <= i − K`, not `< i − K`. With i = K, index 0 has just left.
- The heap is never empty when you read it, because a[i] was just pushed and is in the window.
- Duplicates: equal values with different indices are separate entries, which is fine.

## Variants they might ask

- **Sliding window minimum:** min-heap `priority_queue<pair<long long,int>, vector<...>,
  greater<...> >`.
- **Sliding window median:** two heaps with lazy deletion (hash map of pending deletions), or two
  multisets.
- **Sum of window maxima, or the max of window minima:** the same loop with a different
  aggregate.

## Files

`sol.cpp` (STL max-heap with lazy deletion), `brute.cpp` (scans every window).
