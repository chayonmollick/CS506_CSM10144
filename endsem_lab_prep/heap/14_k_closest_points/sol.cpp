// 14. K closest points to the origin: max-heap of size K keyed by (dist^2, x, y).
// Order: smaller squared distance first; ties -> smaller x, then smaller y.
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<long long, pair<long long, long long> > Item;   // (x*x + y*y, (x, y))

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    priority_queue<Item> pq;              // max-heap: root = worst of the K kept points
    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        pq.push(make_pair(x * x + y * y, make_pair(x, y)));   // squared distance: no sqrt
        if ((int)pq.size() > k) pq.pop();                     // drop the farthest
    }
    vector<Item> res;
    while (!pq.empty()) { res.push_back(pq.top()); pq.pop(); }
    reverse(res.begin(), res.end());      // popped farthest-first
    for (size_t i = 0; i < res.size(); i++)
        cout << res[i].second.first << ' ' << res[i].second.second << '\n';
    return 0;
}
