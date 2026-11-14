// 09. Top-K frequent elements: hash map for counts + min-heap of size K.
// Order: higher frequency first; equal frequency -> smaller value first.
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <unordered_map>
#include <algorithm>
using namespace std;

typedef pair<int, long long> Item;   // (frequency, -value): the "worst" item is the smallest

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    unordered_map<long long, int> freq;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        freq[x]++;
    }
    // root = worst of the current top K (lowest freq; on ties the larger value)
    priority_queue<Item, vector<Item>, greater<Item> > pq;
    for (unordered_map<long long, int>::iterator it = freq.begin(); it != freq.end(); ++it) {
        pq.push(make_pair(it->second, -it->first));
        if ((int)pq.size() > k) pq.pop();                 // throw away the worst
    }
    vector<long long> res;
    while (!pq.empty()) { res.push_back(-pq.top().second); pq.pop(); }
    reverse(res.begin(), res.end());                      // popped worst-first
    for (size_t i = 0; i < res.size(); i++) cout << res[i] << (i + 1 < res.size() ? ' ' : '\n');
    return 0;
}
