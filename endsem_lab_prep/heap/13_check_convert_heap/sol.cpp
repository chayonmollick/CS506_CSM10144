// 13. Is the array a max-heap / min-heap? Then convert it to a max-heap with BUILD-MAX-HEAP.
// 1-indexed: the parent of i is i/2, so only the N-1 parent-child pairs need checking.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> A;   // A[1..n]
int n;

bool isMaxHeap() {
    for (int i = 2; i <= n; i++)
        if (A[i / 2] < A[i]) return false;     // a child is bigger than its parent
    return true;
}
bool isMinHeap() {
    for (int i = 2; i <= n; i++)
        if (A[i / 2] > A[i]) return false;
    return true;
}
void maxHeapify(int i) {
    while (true) {
        int l = 2 * i, r = 2 * i + 1, largest = i;
        if (l <= n && A[l] > A[largest]) largest = l;
        if (r <= n && A[r] > A[largest]) largest = r;
        if (largest == i) return;
        swap(A[i], A[largest]);
        i = largest;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    A.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> A[i];
    cout << "Max-heap: " << (isMaxHeap() ? "YES" : "NO") << '\n';
    cout << "Min-heap: " << (isMinHeap() ? "YES" : "NO") << '\n';
    for (int i = n / 2; i >= 1; i--) maxHeapify(i);   // BUILD-MAX-HEAP, O(n)
    cout << "Converted:";
    for (int i = 1; i <= n; i++) cout << ' ' << A[i];
    cout << '\n';
    return 0;
}
