// 01. Min-heap operations by command (STL priority_queue version).
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    priority_queue<long long, vector<long long>, greater<long long> > pq;   // min-heap
    int q;
    cin >> q;
    while (q--) {
        string op;
        cin >> op;
        if (op == "insert") {
            long long x; cin >> x;
            pq.push(x);
        } else if (op == "getMin") {
            if (pq.empty()) cout << "EMPTY\n"; else cout << pq.top() << '\n';
        } else if (op == "removeMin") {
            if (pq.empty()) cout << "EMPTY\n";
            else { cout << pq.top() << '\n'; pq.pop(); }
        } else if (op == "size") {
            cout << pq.size() << '\n';
        }
    }
    // drain: repeated extract-min gives ascending order
    if (pq.empty()) cout << "EMPTY\n";
    while (!pq.empty()) {
        cout << pq.top();
        pq.pop();
        cout << (pq.empty() ? '\n' : ' ');
    }
    return 0;
}
