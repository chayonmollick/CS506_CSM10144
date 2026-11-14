# CS506 end-semester lab exam: start here

**Sat 14 Nov 2026, 9:00–11:00 AM** (be seated by 8:50) · CS Labs, Ramanujan Block · TA evaluation 11:00–12:00

## What the exam is (from Classroom)
| | |
|---|---|
| Syllabus | **Dynamic Programming, Hashing, Heap (priority queue)** (plan posted 10 Oct) |
| Pattern | **2 questions**, "similar to the mid-semester lab exam pattern" |
| Language | C or C++. **STL is allowed** (latest announcement; the 10 Oct plan had said no STL) |
| Mid-sem format | A **Common setup** (5 marks: a struct plus core functions reused by both parts), then **(a)** (10) and **(b)** (15). Pseudocode/logic goes on paper **before** coding. Each program is evaluated as you finish. See [`../../../../classroom/courses/CS_506_Data_Structures_and_Algorithms/stream_files/CS506-Lab-mid-sem-qp (1).pdf`](<../../../../classroom/courses/CS_506_Data_Structures_and_Algorithms/stream_files/CS506-Lab-mid-sem-qp (1).pdf>) and the official [`CS506_Pseudocode.pdf`](../../../../classroom/courses/CS_506_Data_Structures_and_Algorithms/stream_files/CS506_Pseudocode.pdf) |
| Files | One source file per question: `ENTRYNUMBER QUESTIONNUMBER.cpp`, e.g. `2025CSM1044 1.cpp` |
| Output | **Exactly** as specified: no `Enter n:`, no labels unless the sample shows them |
| Machine | The lab instructions say to bring your own laptop. No internet, no phone |

Even with STL allowed, a question can still say *"implement the heap / hash table yourself"*,
as the mid-sem did for the BST. Be able to type a heap and a chained hash table from memory:
[`templates/`](templates/).

## What is in this folder
| Folder | What | Index |
|---|---|---|
| [`mock_papers/`](mock_papers/) | **4 full mock papers** in the mid-sem format, with solutions and pseudocode: heaps, hashing, DP on strings, DP vs Dijkstra | [`mock_papers/README.md`](mock_papers/README.md) |
| [`dp/`](dp/) | Dynamic-programming problems: the lecture slides' algorithms, Practice Set 4 and Tutorial 9 | [`dp/README.md`](dp/README.md) |
| [`hashing/`](hashing/) | Hashing problems: Tutorial 8, Practice Set 3, open addressing tables, prefix-sum maps, rolling hash | [`hashing/README.md`](hashing/README.md) |
| [`heap/`](heap/) | Heap / priority-queue problems: slides, Practice Set 3, top-k, k-way merge, median, Dijkstra | [`heap/README.md`](heap/README.md) |
| [`lcs_practice/`](lcs_practice/README.md) | **7 LCS drills** (table, tie rules, edits, palindrome, repeating, 3 strings, two rows) with `./check.sh p3 my.cpp` | [`lcs_practice/README.md`](lcs_practice/README.md) |
| [`templates/`](templates/) | Hand-written **min-heap**, **chained hash table** and **open addressing table** (linear/quadratic/double, tombstones) | each has a README |
| [`CHEATSHEET.md`](CHEATSHEET.md) | STL syntax (C++11), input-reading patterns, a DP recurrence table, hashing patterns, traps | |
| [`test.sh`](test.sh) | Builds every `sol*.cpp` with `-std=c++11 -Wall -Wextra` and checks it against its `tests/` | |

Every problem folder has:
- `README.md`: the problem as the exam would state it, the idea, course-style pseudocode, complexity, traps and likely variants;
- `sol.cpp`, and `sol_manual.cpp` (no STL containers) where an implement-it-yourself question is likely;
- `tests/*.in` / `*.out`;
- usually `brute.cpp`, a slow but obviously correct version for checking your own code on new inputs.

```bash
cd sem1/CS506_DSA/labs/endsem_lab_prep
./test.sh                     # everything
./test.sh heap/07_running_median mock_papers/mock2_hashing
```

## Tonight (in this order)
1. **Do one mock under exam conditions** (open only `PAPER.md`, 2 hours), then compare with `SOLUTION.md`. Mock 1 (heaps) and Mock 2 (hashing) are closest to the mid-sem style.
2. **Type the three templates from memory once:** heap (insert, extract, heapify, build), chained hash table (insert at head, search, delete with negative keys), and the 0/1 knapsack and LCS tables with reconstruction.
3. **Read the "how to recognise" section** of [`dp/README.md`](dp/README.md), [`hashing/README.md`](hashing/README.md) and [`heap/README.md`](heap/README.md), and each topic's "most likely questions".
4. **Skim the pseudocode** of the most likely problems: you must write it on paper first, in the course format (see [`CHEATSHEET.md`](CHEATSHEET.md#pseudocode-format-the-course-expects-from-the-mid-sem-solution)).
5. Sleep. Charge the laptop. Check that `g++` or `clang++` works on it, since there is no internet in the lab.

## In the exam (2 hours)
| Time | Do |
|---|---|
| 0:00–0:10 | Read both questions fully. Note the exact I/O format and the tie-break rules. Start with the one you are surer of |
| 0:10–0:20 | Pseudocode for Q1 on the sheet: subproblem, recurrence, base case, order, reconstruction (DP); or data structure plus operations (heap/hash) |
| 0:20–0:55 | Code Q1: the common setup first, then (a), then (b). Test with the sample, then n = 1, duplicates, negatives and "impossible" inputs. Get it evaluated |
| 0:55–1:05 | Pseudocode for Q2 |
| 1:05–1:45 | Code Q2, test it, get it evaluated |
| 1:45–2:00 | Check the file names and the output format again. Remove debug prints |

**Partial marks:**
- The common setup and (a) are 15 of 30.
- A correct brute force (exponential DP without memo, O(n²) instead of hashing) passes the samples and small tests. Write it first if you are stuck, then improve it.
- Print exactly the required format even for a wrong value.

**When the question is new:** classify it with the tables in [`CHEATSHEET.md`](CHEATSHEET.md), open the closest problem folder, read its README's *Variants* section, copy `sol.cpp` and adapt it.

## Caveat
These materials come from the Classroom copy synced on **14 Oct 2026**. Anything posted after that
(other than the exam notice you pasted) has not been included. Check the class stream for a newer
practice set or a changed rule.
