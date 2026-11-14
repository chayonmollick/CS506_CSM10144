# CS 506 — End-semester Lab Exam, Mock 4 (DP and priority queue)

Time allotted: 2 hours | Max. marks 30 | C/C++ | STL allowed

**Instructions**
1. For parts (a) and (b), write the pseudocode/logic first.
2. One source file per part. Print only what is asked.

## Common setup (applies to both parts) [5 marks]
Read a grid: R and C (1 ≤ R, C ≤ 300), then R lines of C integers, each in [0, 1000]. A path
starts at the top-left cell (1,1) and ends at the bottom-right cell (R,C). Its **cost** is the
sum of the values of all cells it visits, including the first and the last.

## (a) Right and down moves only [10 marks]
From (i,j) you may move only to (i+1,j) (`D`) or to (i,j+1) (`R`). Print the minimum cost on the
first line. On the second line print the moves of a cheapest path as a string of `D` and `R`.
If several paths are cheapest, print the alphabetically smallest string (`D` < `R`).
If R = C = 1, print `-` on the second line. Required: O(R·C).

Sample Input
```
5 5
1 1 1 1 1
50 50 50 50 1
1 1 1 1 1
1 50 50 50 50
1 1 1 1 1
```
Sample Output
```
58
DDDDRRRR
```

## (b) All four moves [15 marks]
Now you may also move up and left: to any of the 4 neighbouring cells that lie inside the grid.
Print the minimum cost. Required: O(R·C·log(R·C)).

Sample Input: same as (a). Sample Output
```
17
```
(The cheapest route snakes: right along row 1, down, left along row 3, down, right along row 5.)
