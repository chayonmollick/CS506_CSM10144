// Hand-written array-based binary heap: no std::priority_queue, no make_heap.
// 1-indexed like the slides: root = A[1], PARENT(i) = i/2, LEFT(i) = 2i, RIGHT(i) = 2i+1.
// Default is a MIN-heap. For a MAX-heap call init(true): only higher() changes.
// Reads N initial keys (BUILD-HEAP, O(N)), then Q commands; see README.md.
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 200005;            // capacity: most elements ever in one heap (+1 for index 0)

struct Heap {
    long long A[MAXN];              // A[1..n] holds the heap, A[0] unused
    int n;                          // heap-size
    bool isMax;                     // false = min-heap, true = max-heap

    void init(bool maxHeap) { n = 0; isMax = maxHeap; }
    // true if key x must sit ABOVE key y (min-heap: x < y, max-heap: x > y)
    bool higher(long long x, long long y) const { return isMax ? x > y : x < y; }
    int parent(int i) const { return i / 2; }
    int left(int i) const { return 2 * i; }
    int right(int i) const { return 2 * i + 1; }
    void swapAt(int i, int j) { long long t = A[i]; A[i] = A[j]; A[j] = t; }

    // MIN-HEAPIFY / MAX-HEAPIFY: let A[i] float down (both subtrees are already heaps)
    void heapifyDown(int i) {
        while (true) {
            int l = left(i), r = right(i), best = i;
            if (l <= n && higher(A[l], A[best])) best = l;
            if (r <= n && higher(A[r], A[best])) best = r;
            if (best == i) break;
            swapAt(i, best);
            i = best;
        }
    }
    // bubble A[i] up while it beats its parent
    void heapifyUp(int i) {
        while (i > 1 && higher(A[i], A[parent(i)])) {
            swapAt(i, parent(i));
            i = parent(i);
        }
    }
    // BUILD-HEAP: copy a[0..cnt-1], heapify internal nodes bottom-up -> O(cnt)
    void build(const long long a[], int cnt) {
        n = cnt;
        for (int i = 1; i <= n; i++) A[i] = a[i - 1];
        for (int i = n / 2; i >= 1; i--) heapifyDown(i);
    }
    bool empty() const { return n == 0; }
    long long top() const { return A[1]; }                 // caller checks empty()
    void push(long long key) { A[++n] = key; heapifyUp(n); }
    long long pop() {                                      // EXTRACT-MIN / EXTRACT-MAX
        long long best = A[1];
        A[1] = A[n--];                                     // last leaf -> root
        heapifyDown(1);
        return best;
    }
    // set A[i] = key and restore the heap: covers DECREASE-KEY and INCREASE-KEY
    void changeKey(int i, long long key) {
        A[i] = key;
        heapifyUp(i);                                      // moved towards the root?
        heapifyDown(i);                                    // or towards the leaves?
    }
};

Heap h, tmp;                         // global: the arrays are too big for the stack
long long buf[MAXN];

// HEAPSORT (ascending, in place on a[0..cnt-1]): build a MAX-heap, move the root to the end
void heapSort(long long a[], int cnt) {
    tmp.init(true);
    tmp.build(a, cnt);
    for (int i = cnt; i >= 2; i--) {
        tmp.swapAt(1, i);                                  // max -> its final slot
        tmp.n--;                                           // freeze that slot
        tmp.heapifyDown(1);
    }
    for (int i = 0; i < cnt; i++) a[i] = tmp.A[i + 1];
}

void printArray(const long long a[], int from, int to) {   // prints a[from..to] or EMPTY
    if (from > to) { cout << "EMPTY\n"; return; }
    for (int i = from; i <= to; i++) cout << a[i] << (i < to ? ' ' : '\n');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> buf[i];
    h.init(false);                                         // false = min-heap
    h.build(buf, n);
    cin >> q;
    while (q--) {
        string op;
        cin >> op;
        if (op == "insert") {
            long long x; cin >> x;
            h.push(x);
        } else if (op == "getMin") {
            if (h.empty()) cout << "EMPTY\n"; else cout << h.top() << '\n';
        } else if (op == "extractMin") {
            if (h.empty()) cout << "EMPTY\n"; else cout << h.pop() << '\n';
        } else if (op == "decreaseKey" || op == "increaseKey") {
            int i; long long v; cin >> i >> v;
            bool ok = (i >= 1 && i <= h.n) &&
                      (op == "decreaseKey" ? v <= h.A[i] : v >= h.A[i]);
            if (ok) h.changeKey(i, v); else cout << "INVALID\n";
        } else if (op == "size") {
            cout << h.n << '\n';
        } else if (op == "print") {
            printArray(h.A, 1, h.n);
        } else if (op == "sort") {                         // heap itself is unchanged
            for (int i = 0; i < h.n; i++) buf[i] = h.A[i + 1];
            heapSort(buf, h.n);
            printArray(buf, 0, h.n - 1);
        }
    }
    return 0;
}
