# Rod cutting and jumping practice: 9 problems with a checker

```bash
cd sem1/CS506_DSA/labs/endsem_lab_prep/rod_jump_practice
./check.sh r1 my_r1.cpp        # builds as C++11 with warnings on and runs every test in r1_*/tests
```

The reference solutions are in `solutions/`. Each was checked against a brute force that
tries every way to cut or every path, on 300 random inputs. Prices and lengths are 1-indexed:
p[i] is the price of a piece of length i.

| # | Problem | Recurrence | Time |
|---|---|---|---|
| R1 | Rod cutting: revenue + pieces | r[j] = max over i of p[i] + r[j−i], keep s[j] | 8 min |
| R2 | Rod cutting, each cut costs c | r[j] = max(p[j], max over i<j of p[i] + r[j−i] − c) | 5 min |
| R3 | Max product of the piece lengths | d[j] = max over i of i · max(j−i, d[j−i]) | 5 min |
| R4 | Rod cutting into at most k pieces | f[t][j] = max over i of f[t−1][j−i] + p[i] | 10 min |
| J1 | Jump game: can you reach the end? | furthest reach (greedy) or DP | 3 min |
| J2 | Fewest jumps to the end | J[i] = 1 + min J[j] over i < j ≤ i+a[i] | 8 min |
| J3 | Frog, jumps of 1 or 2 | d[i] = min(d[i−1] + \|h_i−h_{i−1}\|, d[i−2] + \|h_i−h_{i−2}\|) | 5 min |
| J4 | Frog, jumps of 1..k | d[i] = min over j in [i−k, i−1] of d[j] + \|h_i−h_j\| | 5 min |
| J5 | Cheapest path with jumps of 1..k, print it | best[i] = c[i] + min best[j], filled from the end | 10 min |

The rod cutting from the slides is also in [`../dp/01_rod_cutting`](../dp/01_rod_cutting/). Related problems:
- Cut Ribbon, [`../dp/24`](../dp/24_cut_ribbon/): pieces of fixed lengths.
- Breaking a string, [`../dp/34`](../dp/34_breaking_a_string/): the cost of a cut is the length of the piece being cut.
- Climbing stairs, [`../dp/21`](../dp/21_climbing_stairs/) and [`../dp/22`](../dp/22_min_cost_climbing_stairs/): jumps of 1..k.

---

## R1. Rod cutting with the pieces
**Input:** line 1 n (1 ≤ n ≤ 1000). Line 2: p[1..n] (0 ≤ p[i] ≤ 10⁵).
**Output:** line 1 the maximum revenue. Line 2 the piece lengths, first piece first, where the
first piece of a rod of length j is the **smallest** i with p[i] + r[j−i] = r[j].

```
Input                    Output
8                        22
1 5 8 9 10 17 17 20      2 6
```

## R2. Every cut costs c
**Input:** line 1 n c (0 ≤ c ≤ 100). Line 2 p[1..n]. The revenue is the sum of the piece
prices minus c for each cut.
**Output:** the maximum revenue.

```
Input                    Output
8 2                      20
1 5 8 9 10 17 17 20
```

## R3. Maximum product
**Input:** n (2 ≤ n ≤ 60). Cut the rod into **at least two** pieces of integer length.
**Output:** the largest possible product of the piece lengths (use `long long`).

```
Input     Output
10        36
```
(3 + 3 + 4. Note n = 2 → 1 and n = 3 → 2: the rest of the rod may be kept whole, so take max(j−i, d[j−i]).)

## R4. At most k pieces
**Input:** line 1 n k (1 ≤ k ≤ n ≤ 300). Line 2 p[1..n].
**Output:** the maximum revenue using at most k pieces.

```
Input                    Output
8 2                      22
1 5 8 9 10 17 17 20
```

## J1. Can you reach the end?
**Input:** line 1 n (1 ≤ n ≤ 10⁵). Line 2 a[1..n] (a[i] ≥ 0). From index i you may jump to any
of i+1 … i+a[i]. You start at index 1.
**Output:** `YES` if index n can be reached, else `NO`.

```
Input          Output
5              YES
2 3 1 1 4
```

## J2. Fewest jumps
Same input as J1, with n ≤ 10⁴. **Output:** the fewest jumps from 1 to n, or `-1`.

```
Input          Output
5              2
2 3 1 1 4
```
(1 → 2 → 5.)

## J3. Frog, jumps of 1 or 2
**Input:** line 1 n (1 ≤ n ≤ 10⁵). Line 2 heights h[1..n]. The frog starts on stone 1 and jumps
to i+1 or i+2, paying |h[i] − h[j]| per jump.
**Output:** the least total cost to reach stone n.

```
Input          Output
4              30
10 30 40 20
```
(1 → 2 → 4: 20 + 10.)

## J4. Frog, jumps of 1..k
**Input:** line 1 n k (1 ≤ n ≤ 10⁴, 1 ≤ k ≤ 100). Line 2 h[1..n]. Jumps from i to any of i+1 … i+k.
**Output:** the least total cost.

```
Input              Output
5 3                30
10 30 40 50 20
```
(1 → 2 → 5: 20 + 10.)

## J5. Cheapest path, printed
**Input:** line 1 n k (1 ≤ n ≤ 2000). Line 2 c[1..n] (c[i] ≥ 1). Start on stone 1, jump 1..k
stones forward, finish on stone n. You pay c[i] for **every stone you stand on**, including 1 and n.
**Output:** line 1 the least cost. Line 2 the stones visited. If several paths are cheapest,
print the one that is smallest in dictionary order (at each step, the smallest next stone that
still allows the least cost).

```
Input                  Output
6 2                    4
1 100 1 1 100 1        1 3 4 6
```

---

## Hints
- **R1:** `if (p[i] + r[j-i] > r[j])`: the strict `>` keeps the smallest i. Print with
  `for (j = n; j > 0; j -= s[j]) print s[j]`.
- **R2:** "no cut at all" is p[j], so start from r[j] = p[j]; any split pays c once more.
- **R4:** start f[0][0] = 0 and everything else at −∞, so impossible states are never used.
- **J1:** `reach = max(reach, i + a[i])` while `i <= reach`.
- **J2:** fill from the end, J[n] = 0. Faster O(n) greedy: count how many times you have to
  extend the reach.
- **J5:** fill best[] from n down to 1, with `nxt[i]` = the smallest j that gives the minimum
  (strict `<` while j increases). Then follow `nxt` from 1.
