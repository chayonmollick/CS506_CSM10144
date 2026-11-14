// 11. Longest consecutive sequence with a hand-written chained hash set (no STL containers)
#include <iostream>
using namespace std;

struct Node {
    long long key;
    Node* next;
};

const int M = 100003;     // prime number of slots
Node* T[M];               // global: all NULL

int h(long long k) { return (int)(((k % M) + M) % M); }   // negative values are allowed

bool contains(long long k) {
    for (Node* p = T[h(k)]; p != NULL; p = p->next)
        if (p->key == k) return true;
    return false;
}

bool insertKey(long long k) {             // returns false if k was already there
    if (contains(k)) return false;
    Node* x = new Node;
    x->key = k; x->next = T[h(k)];
    T[h(k)] = x;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    long long* vals = new long long[n];   // distinct values, so each run is walked once
    int d = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        if (insertKey(x)) vals[d++] = x;
    }
    long long bestStart = 0, bestLen = 0;
    for (int i = 0; i < d; i++) {
        long long x = vals[i];
        if (contains(x - 1)) continue;    // only start counting at the smallest element of a run
        long long y = x;
        while (contains(y + 1)) y++;
        long long len = y - x + 1;
        if (len > bestLen || (len == bestLen && x < bestStart)) { bestLen = len; bestStart = x; }
    }
    cout << bestLen << "\n";
    for (long long v = bestStart; v < bestStart + bestLen; v++)
        cout << (v == bestStart ? "" : " ") << v;
    cout << "\n";
    delete[] vals;
    return 0;
}
