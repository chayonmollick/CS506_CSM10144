// Mock 2 (b): longest subarray with sum exactly K (negatives allowed), using the
// common-setup hash table as a map  prefix sum -> FIRST index where it occurred.
#include <iostream>
#include <vector>
using namespace std;

// ---- Common setup: chained hash table written by hand ----
struct Node {
    long long key;
    int value;
    Node *next;
    Node(long long k, int v, Node *n) : key(k), value(v), next(n) {}
};

struct HashTable {
    int m;
    vector<Node *> slot;
    HashTable(int m_) : m(m_), slot(m_, (Node *)0) {}
};

int hashOf(const HashTable &T, long long k) {
    return (int)(((k % T.m) + T.m) % T.m);
}

Node *hashSearch(HashTable &T, long long k) {
    for (Node *x = T.slot[hashOf(T, k)]; x; x = x->next)
        if (x->key == k) return x;
    return 0;
}

void hashInsert(HashTable &T, long long k, int v) {
    Node *x = hashSearch(T, k);
    if (x) { x->value = v; return; }
    int s = hashOf(T, k);
    T.slot[s] = new Node(k, v, T.slot[s]);
}
// ---- end of common setup ----

int main() {
    ios::sync_with_stdio(false);
    int n;
    long long K;
    cin >> n >> K;
    HashTable T(100003);                       // prime size, load factor <= 1
    hashInsert(T, 0, 0);                       // empty prefix: sum 0 at index 0
    long long s = 0;
    int best = 0, bestL = 0, bestR = 0;
    for (int j = 1; j <= n; j++) {
        long long a;
        cin >> a;
        s += a;                                // s = P[j]
        Node *x = hashSearch(T, s - K);        // P[i] = P[j] - K  =>  a[i+1..j] sums to K
        if (x && j - x->value > best) {        // strictly longer: keeps the leftmost on ties
            best = j - x->value;
            bestL = x->value + 1;
            bestR = j;
        }
        if (!hashSearch(T, s)) hashInsert(T, s, j);   // keep only the FIRST occurrence
    }
    if (best == 0) cout << 0 << '\n';
    else cout << best << ' ' << bestL << ' ' << bestR << '\n';
    return 0;
}
