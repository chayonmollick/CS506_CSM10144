// 04. Codeforces 681C "Heap Operations": add the fewest operations so the log is valid.
// Replay the log on a real min-heap and patch it greedily just before each record.
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    priority_queue<long long, vector<long long>, greater<long long> > pq;   // min-heap
    vector<pair<int, long long> > out;   // 0 = insert x, 1 = getMin x, 2 = removeMin
    for (int k = 0; k < n; k++) {
        string op;
        cin >> op;
        if (op == "insert") {
            long long x; cin >> x;
            pq.push(x);
            out.push_back(make_pair(0, x));
        } else if (op == "removeMin") {
            if (pq.empty()) {                                // nothing to remove: add one
                pq.push(0);
                out.push_back(make_pair(0, 0LL));
            }
            pq.pop();
            out.push_back(make_pair(2, 0LL));
        } else {                                             // getMin x
            long long x; cin >> x;
            while (!pq.empty() && pq.top() < x) {            // smaller keys must go
                pq.pop();
                out.push_back(make_pair(2, 0LL));
            }
            if (pq.empty() || pq.top() > x) {                // x is missing: add it
                pq.push(x);
                out.push_back(make_pair(0, x));
            }
            out.push_back(make_pair(1, x));
        }
    }
    cout << out.size() << '\n';
    for (size_t i = 0; i < out.size(); i++) {
        if (out[i].first == 0) cout << "insert " << out[i].second << '\n';
        else if (out[i].first == 1) cout << "getMin " << out[i].second << '\n';
        else cout << "removeMin\n";
    }
    return 0;
}
