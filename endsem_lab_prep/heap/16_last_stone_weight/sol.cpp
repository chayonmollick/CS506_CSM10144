// 16. Last stone weight (LeetCode 1046): repeatedly smash the two heaviest stones.
#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    priority_queue<long long> pq;          // max-heap
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        pq.push(x);
    }
    while (pq.size() > 1) {
        long long y = pq.top(); pq.pop();  // heaviest
        long long x = pq.top(); pq.pop();  // second heaviest, x <= y
        if (y != x) pq.push(y - x);        // equal stones both vanish
    }
    cout << (pq.empty() ? 0 : pq.top()) << '\n';
    return 0;
}
