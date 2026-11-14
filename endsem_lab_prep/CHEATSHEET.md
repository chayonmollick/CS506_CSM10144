# CS506 lab cheat sheet: DP, hashing, heaps (C++11)

## Program skeleton
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>       // sort, max, min, reverse, lower_bound
#include <queue>           // priority_queue
#include <unordered_map>   // unordered_map / unordered_set (<unordered_set>)
#include <map>
#include <climits>         // INT_MAX, LLONG_MAX
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // ...
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');   // no trailing space
    return 0;
}
```
- **Compile:**
  - lab Linux: `g++ -std=c++11 -O2 -Wall -o q1 "2025XXX1001 1.cpp"`
  - Mac: `g++-15 …` or `clang++ …`
- **Run on a saved input:** `./q1 < in.txt`
- **Compare with the expected output:** `./q1 < in.txt | diff - out.txt`
- `#include <bits/stdc++.h>` works on lab Linux (gcc) but **not** with Mac clang. Explicit headers work on both.

## Reading input
| Input looks like | Code |
|---|---|
| `n` then n numbers | `cin >> n; for (...) cin >> a[i];` |
| numbers until end of file | `while (cin >> x) v.push_back(x);` |
| numbers until the token `X` | `string t; while (cin >> t && t != "X") v.push_back(atoi(t.c_str()));` (`<cstdlib>`) |
| a whole line with spaces | `getline(cin, s);` (after `cin >> n`, call `cin.ignore()` or a `getline` first) |
| `[[1,3],[2,6]]` style | read the line, `replace` every `[ ] ,` with a space, then `istringstream` (`<sstream>`) |
| commands `I 5`, `getMin` | `string op; cin >> op; if (op == "insert") { cin >> x; ... }` |

## priority_queue (heap)
```cpp
priority_queue<int> mx;                                    // max-heap
priority_queue<int, vector<int>, greater<int> > mn;        // min-heap ("> >" with a space in C++03 style)
mx.push(x); mx.top(); mx.pop(); mx.size(); mx.empty();
typedef pair<ll,int> P;                                    // (key, id): compares key, then id
priority_queue<P, vector<P>, greater<P> > pq;              // min by key, ties by smaller id
struct Cmp { bool operator()(const T &a, const T &b) const { return a.key > b.key; } };  // min-heap on key
priority_queue<T, vector<T>, Cmp> q;
```
- **No decrease-key:** push the new (key, id) and skip stale pops with `if (d != dist[u]) continue;`.
- **Max-heap from a min-heap:** push `-x`.
- **k largest:** keep a min-heap of size k; after each push, pop if size > k. The top is the k-th largest.
- **Array helpers:** `make_heap(v.begin(), v.end())`, `push_heap`, `pop_heap` (moves the max to the back, then `pop_back`), `sort_heap`, `is_heap`.
- **1-indexed heap:**
  - parent(i) = i/2, left = 2i, right = 2i+1;
  - leaves are ⌊n/2⌋+1..n;
  - BUILD-HEAP loops i = ⌊n/2⌋ down to 1.
- **0-indexed heap:**
  - parent = (i−1)/2, left = 2i+1, right = 2i+2;
  - BUILD-HEAP loops i = n/2−1 down to 0.
- **Costs:**
  - BUILD-HEAP O(n); insert, extract and increase-key O(log n); heapsort O(n log n), in place, not stable.
  - Fibonacci heap (theory): insert, union and decrease-key O(1) amortised; extract-min O(log n) amortised.

## unordered_map / unordered_set (hashing)
```cpp
unordered_map<ll,int> first;           // key -> value
first.reserve(2 * n);                  // fewer rehashes
if (first.count(k)) ...                // present?  (0 or 1)
unordered_map<ll,int>::iterator it = first.find(k);
if (it != first.end()) use(it->second);
first[k]++;                            // operator[] INSERTS a 0 if absent: don't use it just to look
first.insert(make_pair(k, j));         // inserts only if k is absent: keeps the FIRST index
first.erase(k);
for (unordered_map<ll,int>::iterator it = m.begin(); it != m.end(); ++it) ...   // order is unspecified
map<ll,int> sorted;                    // ordered (a red-black tree): O(log n); iteration is in key order
unordered_set<int> s; s.insert(x); s.count(x); s.erase(x);
```
- Use `map` when the output must come out in sorted key order. Otherwise sort the result yourself.
- **Hand-written table:**
  - slot = `((k % m) + m) % m`, because `%` is negative for negative k in C/C++;
  - chaining: insert at the head;
  - open addressing: mark deleted slots with DELETED (tombstones), never with EMPTY.
- **Open addressing probes:**
  - linear `(h'(k)+i) % m`;
  - quadratic `(h'(k)+c1·i+c2·i²) % m`;
  - double `(h1(k)+i·h2(k)) % m` with h2(k) ≠ 0 (e.g. `1 + k % (m−1)`).
- **Expected probes** (α = n/m < 1): unsuccessful ≤ 1/(1−α); successful ≤ (1/α)·ln(1/(1−α)).
- **Chaining:** Θ(1+α) per operation.

### Hashing patterns
| Clue | Technique |
|---|---|
| "pair / two elements with sum/difference" | seen-set: for each x, check whether `target − x` was seen |
| "count subarrays with sum K" (negatives OK) | prefix sum P; `ans += cnt[P−K]`; `cnt[P]++` (start with `cnt[0]=1`) |
| "longest subarray with sum K / equal 0s and 1s" | map P → **first** index; answer `j − first[P−K]` (0s become −1, K = 0) |
| "longest subarray with more X than Y" | ±1 prefix; if P>0 the answer is j+1, else use `first[P−1]` |
| "distinct in each window / smallest window containing" | sliding window + count map |
| "longest consecutive run in an unsorted array" | set; start counting only at x with x−1 absent |
| "substring equality / repeated substring / pattern search" | Rabin–Karp rolling hash; on a hash match, compare the strings |
| "frequency / top-k / majority > n/k" | count map (+ heap); Misra–Gries keeps k−1 counters |

## DP patterns (state the subproblem, recurrence, base, order, reconstruction)
| Problem | Subproblem / recurrence |
|---|---|
| Rod cutting | r[j] = max over i≤j of (p[i] + r[j−i]); r[0] = 0; also store the first cut s[j] |
| 0/1 knapsack | K[i][w] = max(K[i−1][w], v_i + K[i−1][w−w_i]); 1-D version: loop w **downwards** |
| Unbounded knapsack / coin change (min) | D[a] = min over coins c of (D[a−c] + 1), D[0] = 0; loop a **upwards** |
| Coin change: number of ways | combinations: `for coin { for a = c..A: W[a] += W[a−c] }`; sequences: swap the two loops |
| Subset sum / partition | S[s] \|= S[s−a_i], with s **downwards**; partition possible iff the total is even and S[total/2] |
| LCS | c[i][j] = c[i−1][j−1]+1 on a match, else max(c[i−1][j], c[i][j−1]) |
| Edit distance | E[i][j] = min(E[i−1][j]+δ, E[i][j−1]+δ, E[i−1][j−1]+α(x_i,y_j)); E[i][0] = iδ, E[0][j] = jδ |
| LIS | O(n²): L[i] = 1 + max L[j] (j<i, a[j]<a[i]); O(n log n): tails + lower_bound |
| Matrix chain | m[i][j] = min over i≤k<j of (m[i][k] + m[k+1][j] + p[i−1]p[k]p[j]); fill by chain length |
| Interval DP (burst balloons, breaking a string) | over [i,j] by increasing length; try each split k |
| Weighted interval scheduling | sort by finish time; OPT(j) = max(v_j + OPT(p(j)), OPT(j−1)), p(j) by binary search |
| Optimal BST | e[i][j] = min over r of (e[i][r−1] + e[r+1][j]) + w(i,j) |
| Palindromic subsequence | P[i][j] = P[i+1][j−1]+2 if s_i = s_j, else max(P[i+1][j], P[i][j−1]) |
| House robber / no two adjacent | H[i] = max(H[i−1], H[i−2] + a_i) |
| Stock with cooldown | hold = max(hold, rest − p); sold = hold + p; rest = max(rest, sold_prev) |
| Grid paths | G[i][j] = g[i][j] + min(G[i−1][j], G[i][j−1]) (count: sum; obstacle → 0) |
| Egg drop | T(k,n) = 1 + min over x of max(T(k−1,x−1), T(k,n−x)); or g(k,m) = g(k−1,m−1) + g(k,m−1) + 1 |
| Tree DP (company party) | in[v] = c(v) + Σ out[child]; out[v] = Σ max(in[child], out[child]) |
| Shortest path with ≤ i edges (Bellman–Ford) | OPT(i,v) = min(OPT(i−1,v), min over edges (v,w) of (c_vw + OPT(i−1,w))) |

- **Memoised (top-down):** recursion + table filled with a "not computed" mark such as −1.
- **Bottom-up:** loops in an order where every entry a cell reads is already filled.
- **Reconstruction:**
  - keep a choice table (s[], b[][]), or recompute which choice achieved the optimum while walking back;
  - say how ties are broken.
- **Infinity:** `const ll INF = (ll)4e18;` or `INT_MAX / 2`, so that INF + cost cannot overflow. Check "unreachable" before you add.

## Pseudocode format the course expects (from the mid-sem solution)
```
function NAME(args):
    if <base case>: return ...
    for i = 1 to n:
        ...
    return ...
Main driver:
    read n, A[1..n]
    result = NAME(A, n)
    print result
```
Use one numbered or indented step per line, never a whole function in one sentence. Name the data
structures and give the complexity at the end.

## Traps
- `int` overflow: sums of 10⁵ values up to 10⁹ need `long long`; so do products like `p[i−1]*p[k]*p[j]`.
- `%` of a negative number is negative.
- 1-indexed formulas on a 0-indexed vector.
- Output: exact separators, no `Enter n:`, no trailing debug lines, newline at the end. Empty answers need the stated marker (`-1`, `0`, `-`, an empty line).
- Every loop that may run zero times: n = 0, k = 0, an empty heap (`top()` on an empty `priority_queue` is undefined behaviour).
- Recursion depth: a memoised DP with depth over 10⁵ can overflow the stack. Use bottom-up.
- `vector<vector<int> > c(m+1, vector<int>(n+1))` with m = n = 10⁴ is 400 MB: too big. Use two rows.
