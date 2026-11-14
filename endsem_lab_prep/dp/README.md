# Dynamic programming: 36 solved problems

Every folder has the problem as the exam would state it, the idea (subproblem, recurrence, base
cases, fill order, reconstruction), course-style pseudocode, complexity, traps and variants.
Each also has `sol.cpp`, `brute.cpp` and `tests/`.

For every DP, the course asks you to state:
- (i) what a subproblem means;
- (ii) the recurrence with base cases;
- (iii) the evaluation order;
- (iv) how the solution, not only its value, is reconstructed.

## The lecture slides' algorithms (01–16)
| No. | Problem | Technique | Source |
|---|---|---|---|
| [01](01_rod_cutting/) | Rod cutting: max revenue + piece sizes | 1-D over lengths, s[j] = first piece | Slides (p = 1 5 8 9 10 17 17 20 → 22) |
| [02](02_matrix_chain/) | Matrix chain: min cost + parenthesization | Interval DP by chain length, split table, PRINT-OPTIMAL-PARENS | Slides (30 35 15 5 10 → 9375) |
| [03](03_lcs/) | LCS: length + one LCS | 2-D table, traceback "up on ties" | Slides (ABCBDAB / BDCABA → BCBA) |
| [04](04_knapsack_01/) | 0/1 knapsack: value + items | M[i][w] table + FIND-ITEMS | Slides, knapsack notes |
| [05](05_subset_sum_partition/) | Equal-sum partition: YES/NO + one group | 1-D subset sum, inner loop downwards | Tutorial 9 Q15 |
| [06](06_edit_distance_alignment/) | Sequence alignment / edit distance (δ, α from input) + alignment | ALIGNMENT + FIND-ALIGNMENT | Slides; Tutorial 9 Q7 (SUNDAY/SATURDAY → 3) |
| [07](07_weighted_interval_scheduling/) | Weighted interval scheduling: value + chosen requests | Sort by finish, p(j) by binary search, take/skip | Slides |
| [08](08_optimal_bst/) | Optimal BST: expected cost + tree | e/w/root tables | Slides (CLRS example → 2.75) |
| [09](09_segmented_least_squares/) | Segmented least squares | OPT(i) = min over j of (e[j,i] + C + OPT(j−1)) | Slides |
| [10](10_shortest_path_bellman_ford/) | Shortest path with negative edges / negative cycle | OPT(i,v), at most i edges | Slides |
| [11](11_lis/) | LIS: length + sequence | O(n log n) tails + parents (O(n²) in README) | Tutorial 9 Q4 |
| [12](12_longest_palindromic_subsequence/) | Longest palindromic subsequence | Interval DP + mirrored traceback | Tutorial 9 Q12 |
| [13](13_coin_change/) | Coin change: min coins / combinations / sequences | Loop order decides combinations vs sequences | Tutorial 9 Q13 ({1,2,5}, 5 → 1 / 4 / 9) |
| [14](14_unbounded_knapsack/) | Unbounded knapsack + copies per item | Upward loop (vs 0/1's downward) | Exam-style variant |
| [15](15_longest_common_substring/) | Longest common substring | Common-suffix DP, reset to 0 on a mismatch | Exam-style variant |
| [16](16_bitonic_tsp/) | Bitonic Euclidean TSP | b[i][j] table (CLRS 15-3) | Tutorial 9 Q9 |

## Practice Set 4 and Tutorial 9 (21–40)
| No. | Problem | Technique | Source |
|---|---|---|---|
| [21](21_climbing_stairs/) | Climbing stairs (1/2 steps, and 1..k steps) | 1-D on the last move | Practice Set 4 Q1 |
| [22](22_min_cost_climbing_stairs/) | Min cost climbing stairs | dp[i] = min(dp[i−1]+c[i−1], dp[i−2]+c[i−2]) | Practice Set 4 Q2 |
| [23](23_house_robber/) | House robber (line, and circle) | Take/skip | Practice Set 4 Q3 |
| [24](24_cut_ribbon/) | Cut Ribbon (−1 if impossible) | Unbounded, maximise the count, start at −∞ | Practice Set 4 Q4, CF 189A |
| [25](25_stock_cooldown/) | Stock with cooldown | 3-state machine hold/sold/rest (1 2 3 0 2 → 3) | Practice Set 4 Q8; Tutorial 9 Q16a |
| [26](26_stock_k_transactions/) | Stock, at most k transactions | buy[j] / sell[j], O(nk) | Tutorial 9 Q16b |
| [27](27_boredom/) | Boredom | House robber over values | Practice Set 4 Q9, CF 455A |
| [28](28_consecutive_subsequence/) | Consecutive subsequence + indices | Hash map len[v] = len[v−1]+1 | Practice Set 4 Q10, CF 977F |
| [29](29_burst_balloons/) | Burst balloons | Interval DP, choose the balloon burst **last** | Practice Set 4 Q11 |
| [30](30_regex_matching/) | Regex matching `.` `*` (YES/NO) | 2-D prefix DP | Practice Set 4 Q12; Tutorial 9 Q18 |
| [31](31_egg_drop/) | Egg drop (2 eggs, 100 floors → 14) | T(k,N) table (`sol_table.cpp`) and g(k,m) moves (`sol.cpp`) | Practice Set 4 Q13; Tutorial 9 Q17 |
| [32](32_word_break/) | Word break: YES/NO, count, one split | Suffix DP + hash-set dictionary | Tutorial 9 Q14 |
| [33](33_company_party/) | Company party (+ president must attend) | Tree DP attend/skip | Tutorial 9 Q5 |
| [34](34_breaking_a_string/) | Breaking a string: min cost + order (20; 2 8 10 → 38) | Interval DP, O(m³) | Tutorial 9 Q10 |
| [35](35_cricket_auction/) | Cricket auction | Group knapsack, O(NPX) | Tutorial 9 Q23 |
| [36](36_village_water_tanks/) | Village water tanks (k-median on a line) | Median block cost + f[t][j], O(kn²) | Tutorial 9 Q24 |
| [37](37_csr_projects/) | CSR projects (low/high effort) | OPT(i) = max(OPT(i−1)+ℓᵢ, OPT(i−2)+hᵢ) | Tutorial 9 Q19 |
| [38](38_grid_paths/) | Grid: min path sum + paths with obstacles | Right/down 2-D DP | Exam-style variant |
| [39](39_two_carts_mango/) | Two carts in a mango orchard | Both carts along anti-diagonals, O(n³) | Tutorial 9 Q25 |
| [40](40_budget_allocation/) | Budget allocation g_i(x) | Knapsack over the budget, O(kB²) | Tutorial 9 Q21 |

See also: [`../mock_papers/mock3_dp_strings`](../mock_papers/mock3_dp_strings/PAPER.md) (LCS + shortest common
supersequence) and [`../mock_papers/mock4_dp_vs_heap`](../mock_papers/mock4_dp_vs_heap/PAPER.md) (grid DP vs Dijkstra).

## How to recognise which DP pattern
- **"Choose where the last piece starts"** (rod, segments, coins, unbounded knapsack, stairs): 1-D over prefixes, OPT(i) = best over j of OPT(j) + cost(j..i). Keep a `choice[]` array for the reconstruction.
- **"Pick items, but not two neighbours"** (houses, adjacent values, parent and child, a high-effort week needing a free week before it): take/skip DP (23, 27, 33, 37).
- **"Today depends on yesterday's state"** (holding, cooldown, transactions left): a state machine, one variable per state, updated from the old values (25, 26).
- **"Best way to split or merge a range"** (matrix chain, OBST, palindromes, burst balloons, breaking a string): interval DP over [i, j], filled by increasing length, with a split table (02, 08, 12, 29, 34).
- **Two strings:** a 2-D table over prefixes.
  - LCS: a match extends the diagonal.
  - Alignment: costs are added.
  - Common substring: a mismatch resets to 0.
  - Regex: `*` means zero copies or one more copy.
- **One capacity, items:**
  - 0/1 → inner loop **downwards**; unlimited → **upwards**.
  - Counting: coins as the outer loop count combinations; amount as the outer loop counts sequences.
  - Groups (at most one per group) → loop over the group's options inside the budget loop.
- **Weighted requests on one resource:** sort by finish time, find p(j), take/skip.
- **Negative edges or "at most k edges":** Bellman–Ford, OPT(i, v).
- **Grids:** DP over cells. Two walkers → move them together along anti-diagonals. Moves in every direction → not a DP; use Dijkstra.

## Most likely exam questions (DP, lab format)
1. **0/1 knapsack with the chosen items** (common setup: read items; (a) value; (b) items, or the "exactly W" / count-ways variant): [04](04_knapsack_01/), [05](05_subset_sum_partition/), [13](13_coin_change/)
2. **LCS / edit distance with reconstruction** (common setup: the table; (a) length + string; (b) SCS / alignment / palindromic subsequence): [03](03_lcs/), [06](06_edit_distance_alignment/), [12](12_longest_palindromic_subsequence/), Mock 3
3. **Rod cutting / matrix chain with the solution printed:** [01](01_rod_cutting/), [02](02_matrix_chain/); plus LIS: [11](11_lis/)
4. From Practice Set 4: coin change, house robber, partition, stock with cooldown: [13](13_coin_change/), [23](23_house_robber/), [05](05_subset_sum_partition/), [25](25_stock_cooldown/)
