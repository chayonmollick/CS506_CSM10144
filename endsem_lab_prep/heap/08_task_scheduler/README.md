# 08. Task scheduler (cooldown)

Source: Practice Set 3 Q7 (Heaps), LeetCode 621 "Task Scheduler",
<https://leetcode.com/problems/task-scheduler/>. Exam-style variant with stdin/stdout.

## Problem

A CPU must run N tasks, each labelled with an uppercase letter. Each task takes one interval.
Two tasks with the **same** letter must be at least n intervals apart, so between them there are
at least n other intervals, either other tasks or idle. Tasks may run in any order. Find the
minimum number of intervals, idle ones included, needed to finish all tasks.

**Input.** Line 1: N and n (1 ≤ N ≤ 10^4, 0 ≤ n ≤ 100). Line 2: N uppercase letters separated
by spaces.

**Output.** One integer: the minimum number of intervals.

**Sample Input**
```
6 2
A A A B B B
```
**Sample Output**
```
8
```
(One optimal schedule: A B idle A B idle A B.)

## Idea

Greedy: the most frequent tasks are the bottleneck, so run them first. Work in **cycles** of
n + 1 slots. In a cycle, pop up to n + 1 tasks from a max-heap of remaining counts. Each runs
once, so no letter repeats within a cycle and the cooldown holds. Push back the ones that still
have work. A cycle costs n + 1 intervals (unused slots are idle), except the last cycle, which
costs only the tasks it ran.

**Formula (check / alternative):** with maxCount = the largest frequency and numMax = how many
letters have that frequency,
`answer = max(N, (maxCount − 1)·(n + 1) + numMax)`. That is maxCount − 1 full frames, plus a last
frame holding the numMax most frequent tasks. When there are enough distinct tasks there are no
idles and the answer is N.

## Pseudocode

```
function LEAST_INTERVAL(tasks[1..N], n):
    cnt[A..Z] = 0
    for t in tasks:
        cnt[t] = cnt[t] + 1
    H = empty max-heap
    for each letter c with cnt[c] > 0:
        INSERT(H, cnt[c])
    time = 0
    while H is not empty:
        used = []
        for slot = 1 to n + 1:
            if H is empty: break
            used.append(EXTRACT_MAX(H) - 1)
        for c in used:
            if c > 0: INSERT(H, c)
        if H is empty:
            time = time + length(used)      // last cycle: no trailing idles
        else:
            time = time + (n + 1)
    return time
```

## Complexity

The heap has at most 26 entries, so each heap operation is O(log 26) = O(1). There are at most
N cycles, so the simulation is O(N·(n + 1)) in the worst case. The formula is O(N + 26). Space
is O(26).

## Edge cases / traps

- n = 0: no cooldown, answer = N.
- Only one letter, `A A A` with n = 2: `A _ _ A _ _ A` = 7, which is (3 − 1)·3 + 1.
- Many distinct letters: no idles, answer = N. The formula needs the `max(N, …)` for this case.
- Push back **after** the cycle, not during it, or the same letter could run twice in one cycle.
- Read letters with `cin >> c` (char). That skips spaces, so input with or without spaces works.

## Variants they might ask

- **Print one schedule:** in each cycle print the popped letters in pop order (most remaining
  first, ties by smaller letter: use a heap of `(count, -letter)`), then `idle` for the unused
  slots unless it is the last cycle.
- **Tasks must run in the given order** (LeetCode 2365): no heap needed. Use a hash map
  letter → next allowed time.
- **Different cooldown per task:** simulate time with a min-heap of (ready time, task) plus a
  max-heap of ready tasks.

## Files

`sol.cpp` (max-heap cycle simulation), `brute.cpp` (closed-form formula). Random tests also
compared both against an exhaustive BFS over schedules for tiny inputs.
