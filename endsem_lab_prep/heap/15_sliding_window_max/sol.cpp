// 15. Sliding window maximum with a max-heap of (value, index) and lazy deletion:
// entries that slid out of the window are discarded only when they reach the top.
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    priority_queue<pair<long long, int> > pq;    // max-heap on value
    vector<long long> res;
    for (int i = 0; i < n; i++) {
        pq.push(make_pair(a[i], i));
        if (i >= k - 1) {                         // window is a[i-k+1 .. i]
            while (pq.top().second <= i - k) pq.pop();   // stale: left the window
            res.push_back(pq.top().first);
        }
    }
    for (size_t i = 0; i < res.size(); i++) cout << res[i] << (i + 1 < res.size() ? ' ' : '\n');
    return 0;
}
