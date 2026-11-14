// 07. Running median with two heaps: lo = max-heap (smaller half), hi = min-heap (larger half).
// Invariant: lo.size() == hi.size() or lo.size() == hi.size() + 1, and lo.top() <= hi.top().
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    priority_queue<long long> lo;                                          // max-heap
    priority_queue<long long, vector<long long>, greater<long long> > hi;  // min-heap
    cout << fixed << setprecision(1);
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        if (lo.empty() || x <= lo.top()) lo.push(x); else hi.push(x);
        // rebalance sizes
        if (lo.size() > hi.size() + 1) { hi.push(lo.top()); lo.pop(); }
        else if (hi.size() > lo.size()) { lo.push(hi.top()); hi.pop(); }
        long long twice = (lo.size() > hi.size()) ? 2 * lo.top() : lo.top() + hi.top();
        cout << twice / 2.0 << (i + 1 < n ? ' ' : '\n');                   // exact: x.0 or x.5
    }
    return 0;
}
