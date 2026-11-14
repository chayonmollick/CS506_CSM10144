// 11. Connect ropes with minimum cost (Huffman-like): always join the two shortest.
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    priority_queue<long long, vector<long long>, greater<long long> > pq;   // min-heap
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        pq.push(x);
    }
    long long cost = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        cost += a + b;          // pay for this join
        pq.push(a + b);         // the new rope goes back
    }
    cout << cost << '\n';
    return 0;
}
