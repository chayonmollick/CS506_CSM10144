// 12. Sort a K-sorted array: the next smallest is always among the next K+1 unplaced elements,
// so a min-heap of size K+1 is enough.
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    priority_queue<long long, vector<long long>, greater<long long> > pq;   // min-heap
    int out = 0;                                  // next position to fill (in place)
    for (int i = 0; i < n; i++) {
        pq.push(a[i]);
        if ((int)pq.size() > k) {                 // window of K+1: its min is final
            a[out++] = pq.top();
            pq.pop();
        }
    }
    while (!pq.empty()) { a[out++] = pq.top(); pq.pop(); }
    for (int i = 0; i < n; i++) cout << a[i] << (i + 1 < n ? ' ' : '\n');
    return 0;
}
