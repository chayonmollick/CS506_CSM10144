// 02. BUILD-MAX-HEAP and HEAPSORT exactly as in the slides (1-indexed, vector storage).
// std::make_heap is NOT used: it may place elements differently than CLRS MAX-HEAPIFY.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> A;   // A[1..n], A[0] unused
int heapSize;

void maxHeapify(int i) {                       // float A[i] down
    while (true) {
        int l = 2 * i, r = 2 * i + 1, largest = i;
        if (l <= heapSize && A[l] > A[largest]) largest = l;
        if (r <= heapSize && A[r] > A[largest]) largest = r;
        if (largest == i) return;
        swap(A[i], A[largest]);
        i = largest;
    }
}
void buildMaxHeap(int n) {
    heapSize = n;
    for (int i = n / 2; i >= 1; i--) maxHeapify(i);   // leaves (> n/2) are already heaps
}
void heapSort(int n) {
    buildMaxHeap(n);
    for (int i = n; i >= 2; i--) {
        swap(A[1], A[i]);                      // max -> final slot
        heapSize--;
        maxHeapify(1);
    }
}
void printLine(const char* label, int n) {
    cout << label;
    for (int i = 1; i <= n; i++) cout << ' ' << A[i];
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    A.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> A[i];
    buildMaxHeap(n);
    printLine("Max-heap:", n);
    heapSort(n);                               // rebuilding an existing heap changes nothing
    printLine("Sorted:", n);
    return 0;
}
