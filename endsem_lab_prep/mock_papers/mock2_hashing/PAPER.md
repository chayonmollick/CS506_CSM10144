# CS 506 — End-semester Lab Exam, Mock 2 (Hashing)

Time allotted: 2 hours | Max. marks 30 | C/C++

**Instructions**
1. For parts (a) and (b), write the pseudocode/logic first (not needed for the common setup).
2. One source file per part. Print only what is asked.
3. Build the hash table yourself: no `std::map`, `std::unordered_map`, `std::set` or `std::unordered_set` in this mock.

## Common setup (applies to both parts) [5 marks]
Implement a hash table with **separate chaining**:
`Node = { long long key; int value; Node* next; }` and a table of m chain heads.
Use the division method `h(k) = k mod m`, giving a slot in 0..m−1 **also for negative k**.
Implement:
- `HASH-SEARCH(T, k)`;
- `HASH-INSERT(T, k, v)`: a new key goes to the **head** of its chain; an existing key only gets its value updated;
- `HASH-DELETE(T, k)`.

## (a) Operations on the table [10 marks]
Read m and Q (1 ≤ m ≤ 1000, 1 ≤ Q ≤ 10⁵), then Q lines, each one of:
- `I k`: insert key k (do nothing if k is already present);
- `D k`: delete key k (do nothing if absent);
- `S k`: print `YES` if k is present, else `NO`, on its own line.

Keys are in [−10⁹, 10⁹]. After all operations, print the table, one line per slot:
`i:` followed by the keys of chain i from head to tail, each preceded by one space.

Sample Input
```
7 12
I 10
I 3
I 17
I 8
I -4
I 21
S 17
S 4
D 3
I 31
S 3
D 99
```
Sample Output
```
YES
NO
NO
0: 21
1: 8
2:
3: 31 -4 17 10
4:
5:
6:
```

## (b) Longest subarray with sum K [15 marks]
Read n and K (1 ≤ n ≤ 10⁵, |K| ≤ 10⁹), then n integers a₁..aₙ with |aᵢ| ≤ 10⁴. Negative values are allowed.
Find the **longest** contiguous subarray whose sum is exactly K. Print its length, start index and
end index (1-based), separated by spaces. If several subarrays have the maximum length, print the
one that starts first. If none exists, print `0`. Expected O(n) time, using your common-setup table.

Sample Input
```
8 5
2 -1 3 1 -2 4 0 1
```
Sample Output
```
6 2 7
```
