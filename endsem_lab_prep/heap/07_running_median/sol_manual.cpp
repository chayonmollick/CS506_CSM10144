// 07. Running median with two hand-written heaps (no STL containers).
#include <iostream>
#include <iomanip>
using namespace std;

const int MAXN = 100005;

struct Heap {
    long long A[MAXN];
    int n;
    bool isMax;                     // true = max-heap, false = min-heap
    void init(bool m) { n = 0; isMax = m; }
    bool higher(long long x, long long y) const { return isMax ? x > y : x < y; }
    void swapAt(int i, int j) { long long t = A[i]; A[i] = A[j]; A[j] = t; }
    void push(long long x) {
        A[++n] = x;
        int i = n;
        while (i > 1 && higher(A[i], A[i / 2])) { swapAt(i, i / 2); i /= 2; }
    }
    long long pop() {
        long long top = A[1];
        A[1] = A[n--];
        int i = 1;
        while (true) {
            int l = 2 * i, r = 2 * i + 1, b = i;
            if (l <= n && higher(A[l], A[b])) b = l;
            if (r <= n && higher(A[r], A[b])) b = r;
            if (b == i) break;
            swapAt(i, b);
            i = b;
        }
        return top;
    }
};

Heap lo, hi;   // global: big arrays

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    lo.init(true);    // smaller half, max on top
    hi.init(false);   // larger half, min on top
    cout << fixed << setprecision(1);
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        if (lo.n == 0 || x <= lo.A[1]) lo.push(x); else hi.push(x);
        if (lo.n > hi.n + 1) hi.push(lo.pop());
        else if (hi.n > lo.n) lo.push(hi.pop());
        long long twice = (lo.n > hi.n) ? 2 * lo.A[1] : lo.A[1] + hi.A[1];
        cout << twice / 2.0 << (i + 1 < n ? ' ' : '\n');
    }
    return 0;
}
