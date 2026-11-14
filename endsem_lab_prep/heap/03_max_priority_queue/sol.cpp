// 03. Max-priority queue on a binary max-heap: BUILD-MAX-HEAP, HEAP-MAXIMUM, HEAP-EXTRACT-MAX,
// HEAP-INCREASE-KEY, MAX-HEAP-INSERT. 1-indexed like the slides. std::priority_queue has no
// increase-key by position, so the heap is written by hand (vector storage).
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> A(1);   // A[1..heapSize], A[0] unused
int heapSize = 0;

void maxHeapify(int i) {
    while (true) {
        int l = 2 * i, r = 2 * i + 1, largest = i;
        if (l <= heapSize && A[l] > A[largest]) largest = l;
        if (r <= heapSize && A[r] > A[largest]) largest = r;
        if (largest == i) return;
        swap(A[i], A[largest]);
        i = largest;
    }
}
long long extractMax() {                       // caller checks heapSize >= 1
    long long mx = A[1];
    A[1] = A[heapSize];                        // last leaf -> root
    heapSize--;
    maxHeapify(1);
    return mx;
}
bool increaseKey(int i, long long key) {       // false = error
    if (i < 1 || i > heapSize || key < A[i]) return false;
    A[i] = key;
    while (i > 1 && A[i / 2] < A[i]) {         // bubble up
        swap(A[i], A[i / 2]);
        i /= 2;
    }
    return true;
}
void insertKey(long long key) {
    heapSize++;
    if ((int)A.size() <= heapSize) A.push_back(0);
    A[heapSize] = key;                         // same as -inf then INCREASE-KEY
    increaseKey(heapSize, key);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n;
    A.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> A[i];
    heapSize = n;
    for (int i = n / 2; i >= 1; i--) maxHeapify(i);   // BUILD-MAX-HEAP
    cin >> q;
    while (q--) {
        string op;
        cin >> op;
        if (op == "maximum") {
            if (heapSize == 0) cout << "EMPTY\n"; else cout << A[1] << '\n';
        } else if (op == "extractMax") {
            if (heapSize == 0) cout << "EMPTY\n"; else cout << extractMax() << '\n';
        } else if (op == "insert") {
            long long k; cin >> k;
            insertKey(k);
        } else if (op == "increaseKey") {
            int i; long long k; cin >> i >> k;
            if (!increaseKey(i, k)) cout << "ERROR\n";
        } else if (op == "print") {
            if (heapSize == 0) cout << "EMPTY\n";
            for (int i = 1; i <= heapSize; i++) cout << A[i] << (i < heapSize ? ' ' : '\n');
        }
    }
    return 0;
}
