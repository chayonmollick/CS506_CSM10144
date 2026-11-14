// Mock 1 (a): BUILD-MIN-HEAP, print the heap array, then the k smallest by EXTRACT-MIN.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ---- Common setup: 1-indexed binary min-heap written by hand ----
struct MinHeap {
    vector<int> a;   // a[0] unused, a[1..size] is the heap
    int size;
    MinHeap() : a(1), size(0) {}
};

void minHeapify(MinHeap &h, int i) {          // float a[i] down
    while (true) {
        int l = 2 * i, r = 2 * i + 1, s = i;
        if (l <= h.size && h.a[l] < h.a[s]) s = l;
        if (r <= h.size && h.a[r] < h.a[s]) s = r;
        if (s == i) return;
        swap(h.a[i], h.a[s]);
        i = s;
    }
}

void buildMinHeap(MinHeap &h) {               // O(n), bottom-up
    for (int i = h.size / 2; i >= 1; i--) minHeapify(h, i);
}

void heapInsert(MinHeap &h, int x) {           // float the new key up
    h.a.push_back(x);
    int i = ++h.size;
    while (i > 1 && h.a[i / 2] > h.a[i]) { swap(h.a[i], h.a[i / 2]); i /= 2; }
}

int heapExtractMin(MinHeap &h) {               // caller checks size > 0
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
    MinHeap h;
    for (int i = 0; i < n; i++) { int x; cin >> x; h.a.push_back(x); }
    h.size = n;
    buildMinHeap(h);
    for (int i = 1; i <= n; i++) cout << h.a[i] << (i == n ? '\n' : ' ');
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) cout << heapExtractMin(h) << (i == k - 1 ? '\n' : ' ');
    return 0;
}
