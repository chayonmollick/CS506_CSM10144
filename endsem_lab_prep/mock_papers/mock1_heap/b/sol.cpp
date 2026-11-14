// Mock 1 (b): running (lower) median with two heaps built from the common-setup min-heap.
// low  = max-heap of the smaller half (stored as -x in a min-heap)
// high = min-heap of the larger half; invariant: low.size == high.size or low.size == high.size + 1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ---- Common setup: 1-indexed binary min-heap written by hand ----
struct MinHeap {
    vector<int> a;
    int size;
    MinHeap() : a(1), size(0) {}
};

void minHeapify(MinHeap &h, int i) {
    while (true) {
        int l = 2 * i, r = 2 * i + 1, s = i;
        if (l <= h.size && h.a[l] < h.a[s]) s = l;
        if (r <= h.size && h.a[r] < h.a[s]) s = r;
        if (s == i) return;
        swap(h.a[i], h.a[s]);
        i = s;
    }
}

void heapInsert(MinHeap &h, int x) {
    h.a.push_back(x);
    int i = ++h.size;
    while (i > 1 && h.a[i / 2] > h.a[i]) { swap(h.a[i], h.a[i / 2]); i /= 2; }
}

int heapExtractMin(MinHeap &h) {
    int m = h.a[1];
    h.a[1] = h.a[h.size];
    h.a.pop_back();
    h.size--;
    minHeapify(h, 1);
    return m;
}
// ---- end of common setup ----

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    MinHeap low, high;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (low.size == 0 || x <= -low.a[1]) heapInsert(low, -x);
        else heapInsert(high, x);
        // rebalance so that low has the extra element when the count is odd
        if (low.size > high.size + 1) heapInsert(high, -heapExtractMin(low));
        else if (high.size > low.size) heapInsert(low, -heapExtractMin(high));
        cout << -low.a[1] << (i == n - 1 ? '\n' : ' ');
    }
    return 0;
}
