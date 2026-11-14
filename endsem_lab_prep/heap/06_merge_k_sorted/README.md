# 06. Merge K sorted arrays

Source: exam-style variant of LeetCode 23 "Merge k Sorted Lists"
(<https://leetcode.com/problems/merge-k-sorted-lists/>), the k-way merge pattern.

## Problem

You are given K arrays, each sorted in non-decreasing order. Merge them into one sorted array
using a min-heap. Do not concatenate and sort.

**Input.** Line 1: K (1 ≤ K ≤ 10^4). Next K lines: m_i (0 ≤ m_i ≤ 10^5) followed by the m_i
sorted values of array i. Σ m_i ≤ 10^5 and Σ m_i ≥ 1. Values are in [-10^9, 10^9].

**Output.** One line with all Σ m_i values in non-decreasing order, space-separated.

**Sample Input**
```
3
3 1 4 7
4 2 3 8 10
2 0 9
```
**Sample Output**
```
0 1 2 3 4 7 8 9 10
```

## Idea

The next output is always the smallest of the K current heads. Keep the heads in a min-heap of
triples (value, list id, index). Pop the smallest, output it, and push the next element of the
same list. The heap never holds more than K items.

## Pseudocode

```
function MERGE_K_SORTED(L[1..K]):
    H = empty min-heap of (value, list, index)
    for i = 1 to K:
        if L[i] is not empty:
            INSERT(H, (L[i][1], i, 1))
    out = []
    while H is not empty:
        (v, i, j) = EXTRACT_MIN(H)
        out.append(v)
        if j + 1 <= length(L[i]):
            INSERT(H, (L[i][j + 1], i, j + 1))
    return out
```

## Complexity

Let N = Σ m_i. Every element is pushed and popped once, so time is O(N log K). The heap uses
O(K) extra space, plus O(N) for the output. Concatenate-and-sort would be O(N log N).

## Edge cases / traps

- Empty arrays (m_i = 0): do not push a head for them, and do not read `lists[i][0]`.
- K = 1: the output is the input array.
- Duplicates across lists are kept, not deduplicated.
- STL min-heap of pairs: `priority_queue<Item, vector<Item>, greater<Item> >`. Put a space
  between `> >` for C++03-safe parsing (C++11 accepts `>>`).

## Variants they might ask

- **Linked lists:** store `(value, node pointer)`, or use a struct with a comparator that compares
  `node->val`. Push `node->next`.
- **K-th smallest element across K sorted arrays:** pop K times, and the K-th pop is the answer.
- **Smallest range covering one element from each list** (LeetCode 632): also track the current
  max. The range is [heap min, current max]. Stop when a list runs out.
- **Merge into descending order:** max-heap, with arrays given in descending order.

## Files

`sol.cpp` (STL min-heap of pairs), `brute.cpp` (concatenate and sort).
