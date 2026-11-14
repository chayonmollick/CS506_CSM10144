// 05. K-th largest element: min-heap holding the K largest keys seen so far.
// Its root is the K-th largest. The stream answer is printed after each element from the K-th on.
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
    priority_queue<long long, vector<long long>, greater<long long> > pq;   // min-heap, size <= k
    vector<long long> stream;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();          // drop the smallest: keep the k largest
        if ((int)pq.size() == k) stream.push_back(pq.top());
    }
    cout << pq.top() << '\n';                       // k-th largest of the whole array
    for (size_t i = 0; i < stream.size(); i++)
        cout << stream[i] << (i + 1 < stream.size() ? ' ' : '\n');
    return 0;
}
