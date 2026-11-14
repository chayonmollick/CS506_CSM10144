# 04. Fix a heap operation log (Codeforces 681C "Heap Operations")

Source: Practice Set 3 Q6 (Heaps), <https://codeforces.com/problemset/problem/681/C>.
Exam-style variant with one deterministic answer.

## Problem

A min-heap log has three kinds of records:

- `insert x`: put x into the heap.
- `getMin x`: the minimum of the heap at this moment **is x**.
- `removeMin`: remove one copy of the minimum.

Some records were lost, so the log may be impossible: `getMin x` may disagree with the heap, or
`removeMin` / `getMin` may run on an empty heap. Add the **minimum number** of records anywhere
so that the log is valid and the given records stay in their original order as a subsequence.

Codeforces accepts any minimal answer. For exact checking, records are only added immediately
before the record that needs them, using these rules:

- Before `removeMin` on an empty heap, add `insert 0`.
- Before `getMin x`, add one `removeMin` for each key smaller than x. Then, if the heap is empty
  or its minimum is greater than x, add `insert x`.

**Input.** Line 1: n (1 ≤ n ≤ 10^5). Next n lines: one record each, |x| ≤ 10^9.

**Output.** Line 1: m, the number of records in the corrected log. Next m lines: the
corrected log in the same format.

**Sample Input**
```
2
insert 3
getMin 4
```
**Sample Output**
```
4
insert 3
removeMin
insert 4
getMin 4
```

## Idea

Replay the log on a real min-heap and fix each record at the last moment.

- `getMin x`: every key smaller than x would make the minimum wrong, and inserts cannot hide
  it, so it has to be removed. If after that x is not the minimum (heap empty, or minimum > x),
  x must be inserted. Each added record is forced, so the count is minimal.
- `removeMin` on an empty heap is forced to need one insert. The value does not matter, so the
  rule uses 0.

## Pseudocode

```
function FIX_LOG(records[1..n]):
    H = empty min-heap
    out = []
    for rec in records:
        if rec.op == "insert":
            INSERT(H, rec.x);  out.append("insert x")
        else if rec.op == "removeMin":
            if H is empty:
                INSERT(H, 0);  out.append("insert 0")
            EXTRACT_MIN(H);    out.append("removeMin")
        else:                                  // getMin x
            while H not empty and MIN(H) < rec.x:
                EXTRACT_MIN(H);  out.append("removeMin")
            if H is empty or MIN(H) > rec.x:
                INSERT(H, rec.x);  out.append("insert x")
            out.append("getMin x")
    print len(out), then every line of out
```

## Complexity

Each original record adds at most one insert, and every removeMin pops something that was
inserted, so the output has at most 3n records. Time is O(n log n) and space is O(n).

## Edge cases / traps

- `getMin x` when the minimum is already x: add nothing. Duplicates of x stay.
- `getMin` on an empty heap: just `insert x`.
- Collect the output first (vector) or count first. The count m is printed **before** the log.
- Output is large (up to 3·10^5 lines). Use `'\n'`, not `endl`, with `sync_with_stdio(false)`.
- The same value inserted several times: each copy needs its own `removeMin`.

## Variants they might ask

- **Max-heap log** (`getMax`, `removeMax`): use a max-heap and flip `<` / `>` in the getMin
  rule.
- **Only print the count:** skip storing `out` and just count.
- **Validate only:** print `YES` if the log is already consistent (no record would be added),
  otherwise `NO`.

## Files

`sol.cpp` (STL `priority_queue`), `brute.cpp` (same rules on a sorted vector, O(n^2)).
Random tests also simulated the output log to confirm it is valid and keeps the original
records in order.
