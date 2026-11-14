# 02. Matrix-Chain Multiplication (cost + parenthesization)

Source: DP slides, "Matrix-Chain Multiplication" (MATRIX-CHAIN-ORDER, PRINT-OPTIMAL-PARENS,
worked example p = [30, 35, 15, 5, 10]); Tutorial 9 Q2.

## Problem

A chain of n matrices A1 A2 ... An is given, where Ai has dimensions p_{i-1} × p_i. Multiplying a
p × q matrix by a q × r matrix costs p·q·r scalar multiplications. Find the minimum number of
scalar multiplications needed to compute the product, and print an optimal full parenthesization.

Print the parenthesization in PRINT-OPTIMAL-PARENS form: a single matrix is `Ai`; a product of two
groups is `(` left right `)` with no spaces. If several splits give the minimum, use the smallest
split point k (for every sub-chain).

**Input**
- Line 1: n (number of matrices)
- Line 2: n + 1 integers p_0 p_1 ... p_n

**Output**
- Line 1: the minimum number of scalar multiplications
- Line 2: the optimal parenthesization

**Constraints**: 1 ≤ n ≤ 200, 1 ≤ p_i ≤ 1000 (costs need `long long`).

**Sample Input**
```
4
30 35 15 5 10
```

**Sample Output**
```
9375
((A1(A2A3))A4)
```

## Idea

- Subproblem: m[i][j] = minimum cost to compute A_i ... A_j (1 ≤ i ≤ j ≤ n).
- Recurrence: m[i][i] = 0; m[i][j] = min over i ≤ k < j of
  m[i][k] + m[k+1][j] + p_{i-1} · p_k · p_j (the last multiplication joins the two groups).
- Fill order: by chain length l = 2..n (diagonal by diagonal); every entry reads shorter chains.
- Reconstruction: s[i][j] = the k that gave the minimum. PRINT-OPTIMAL-PARENS(1, n) recurses
  on (i, s[i][j]) and (s[i][j] + 1, j).

## Pseudocode

```
function MATRIX-CHAIN-ORDER(p, n):
    for i = 1 to n:
        m[i][i] = 0
    for l = 2 to n:                      // chain length
        for i = 1 to n - l + 1:
            j = i + l - 1
            m[i][j] = infinity
            for k = i to j - 1:
                q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j]
                if q < m[i][j]:
                    m[i][j] = q
                    s[i][j] = k          // remember the split
    return m, s

function PRINT-OPTIMAL-PARENS(s, i, j):
    if i == j:
        print "A" i
    else:
        print "("
        PRINT-OPTIMAL-PARENS(s, i, s[i][j])
        PRINT-OPTIMAL-PARENS(s, s[i][j] + 1, j)
        print ")"
```

## Complexity

Θ(n^3) time, Θ(n^2) space; printing is O(n). Brute force is Catalan(n−1) (exponential);
the plain recursion RECURSIVE-MATRIX-CHAIN is also exponential.

## Edge cases / traps

- n = 1: cost 0, output `A1` (no parentheses).
- Read n + 1 dimensions, not n. A_i is p[i−1] × p[i]; using p[i]·p[k]·p[j] is the classic bug.
- The loop must go by chain length; looping i = 1..n, j = i..n reads m[k+1][j] before it is filled.
- p[i−1]·p[k]·p[j] can reach 10^9 per term and the sum more: use `long long` for m.
- Initialise m[i][j] to "infinity" (or a flag such as −1) before the k loop, not to 0.

## Variants they might ask

- Print the cost table m or s: add a loop after filling (print m[i][j] for j ≥ i).
- Top-down: MEMOIZED-MATRIX-CHAIN with m[i][j] = −1 meaning "not solved".
- Maximum cost instead of minimum: flip the comparison (and initialise to −1).
- Same interval-DP shape: polygon triangulation, breaking a string (Tutorial Q10), burst balloons —
  only the cost term changes.
