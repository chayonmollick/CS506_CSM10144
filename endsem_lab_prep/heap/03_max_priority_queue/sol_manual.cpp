// 03. Max-priority queue with a plain array (no STL containers), CLRS operations, 1-indexed.
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 200005;   // N + inserts
long long A[MAXN];
int heapSize = 0;

void swapAt(int i, int j) { long long t = A[i]; A[i] = A[j]; A[j] = t; }
void maxHeapify(int i) {
    int l = 2 * i, r = 2 * i + 1, largest = i;
    if (l <= heapSize && A[l] > A[largest]) largest = l;
    if (r <= heapSize && A[r] > A[largest]) largest = r;
    if (largest != i) { swapAt(i, largest); maxHeapify(largest); }
}
long long extractMax() {
    long long mx = A[1];
    A[1] = A[heapSize--];
    maxHeapify(1);
    return mx;
}
bool increaseKey(int i, long long key) {
    if (i < 1 || i > heapSize || key < A[i]) return false;   // "new key is smaller"
    A[i] = key;
    while (i > 1 && A[i / 2] < A[i]) { swapAt(i, i / 2); i /= 2; }
    return true;
}
void insertKey(long long key) {
    A[++heapSize] = key;
    increaseKey(heapSize, key);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    heapSize = n;
    for (int i = n / 2; i >= 1; i--) maxHeapify(i);
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
