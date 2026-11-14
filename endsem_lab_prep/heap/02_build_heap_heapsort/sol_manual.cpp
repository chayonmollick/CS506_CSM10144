// 02. BUILD-MAX-HEAP and HEAPSORT with a plain array (no STL containers).
#include <iostream>
using namespace std;

const int MAXN = 100005;
long long A[MAXN];     // A[1..n]
int heapSize;

void maxHeapify(int i) {                       // recursive, as in the slides
    int l = 2 * i, r = 2 * i + 1, largest = i;
    if (l <= heapSize && A[l] > A[largest]) largest = l;
    if (r <= heapSize && A[r] > A[largest]) largest = r;
    if (largest != i) {
        long long t = A[i]; A[i] = A[largest]; A[largest] = t;
        maxHeapify(largest);
    }
}
void buildMaxHeap(int n) {
    heapSize = n;
    for (int i = n / 2; i >= 1; i--) maxHeapify(i);
}
void heapSort(int n) {
    buildMaxHeap(n);
    for (int i = n; i >= 2; i--) {
        long long t = A[1]; A[1] = A[i]; A[i] = t;
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
    for (int i = 1; i <= n; i++) cin >> A[i];
    buildMaxHeap(n);
    printLine("Max-heap:", n);
    heapSort(n);
    printLine("Sorted:", n);
    return 0;
}
