// Reference version written literally from the slides (recursive MIN-HEAPIFY,
// HEAP-DECREASE-KEY, MIN-HEAP-INSERT via +infinity) on a std::vector; "sort" uses std::sort.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> A(1);   // A[0] unused
int heapSize = 0;

void minHeapify(int i) {
    int l = 2 * i, r = 2 * i + 1, smallest = i;
    if (l <= heapSize && A[l] < A[smallest]) smallest = l;
    if (r <= heapSize && A[r] < A[smallest]) smallest = r;
    if (smallest != i) { swap(A[i], A[smallest]); minHeapify(smallest); }
}
void decreaseKey(int i, long long key) {
    A[i] = key;
    while (i > 1 && A[i / 2] > A[i]) { swap(A[i], A[i / 2]); i /= 2; }
}
void insertKey(long long key) {
    heapSize++;
    if ((int)A.size() <= heapSize) A.push_back(0);
    A[heapSize] = 4000000000000000000LL;   // +infinity
    decreaseKey(heapSize, key);
}

int main() {
    int n, q;
    cin >> n;
    A.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> A[i];
    heapSize = n;
    for (int i = n / 2; i >= 1; i--) minHeapify(i);
    cin >> q;
    while (q--) {
        string op; cin >> op;
        if (op == "insert") { long long x; cin >> x; insertKey(x); }
        else if (op == "getMin") { if (heapSize == 0) cout << "EMPTY\n"; else cout << A[1] << "\n"; }
        else if (op == "extractMin") {
            if (heapSize == 0) { cout << "EMPTY\n"; continue; }
            cout << A[1] << "\n";
            A[1] = A[heapSize]; heapSize--; minHeapify(1);
        } else if (op == "decreaseKey") {
            int i; long long v; cin >> i >> v;
            if (i < 1 || i > heapSize || v > A[i]) cout << "INVALID\n"; else decreaseKey(i, v);
        } else if (op == "increaseKey") {
            int i; long long v; cin >> i >> v;
            if (i < 1 || i > heapSize || v < A[i]) cout << "INVALID\n"; else { A[i] = v; minHeapify(i); }
        } else if (op == "size") cout << heapSize << "\n";
        else if (op == "print" || op == "sort") {
            vector<long long> b(A.begin() + 1, A.begin() + 1 + heapSize);
            if (op == "sort") sort(b.begin(), b.end());
            if (b.empty()) cout << "EMPTY\n";
            for (size_t i = 0; i < b.size(); i++) cout << b[i] << (i + 1 < b.size() ? " " : "\n");
        }
    }
    return 0;
}
