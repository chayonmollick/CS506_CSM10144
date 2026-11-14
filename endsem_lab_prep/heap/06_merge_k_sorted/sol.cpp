// 06. Merge K sorted arrays with a min-heap of (value, (list, index)).
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
using namespace std;

typedef pair<long long, pair<int, int> > Item;   // (value, (which list, position in it))

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int k;
    cin >> k;
    vector<vector<long long> > lists(k);
    for (int i = 0; i < k; i++) {
        int m;
        cin >> m;
        lists[i].resize(m);
        for (int j = 0; j < m; j++) cin >> lists[i][j];
    }
    priority_queue<Item, vector<Item>, greater<Item> > pq;   // min-heap
    for (int i = 0; i < k; i++)
        if (!lists[i].empty()) pq.push(make_pair(lists[i][0], make_pair(i, 0)));   // heads
    vector<long long> merged;
    while (!pq.empty()) {
        Item it = pq.top();
        pq.pop();
        merged.push_back(it.first);
        int li = it.second.first, pos = it.second.second + 1;
        if (pos < (int)lists[li].size())                     // next element of the same list
            pq.push(make_pair(lists[li][pos], make_pair(li, pos)));
    }
    for (size_t i = 0; i < merged.size(); i++)
        cout << merged[i] << (i + 1 < merged.size() ? ' ' : '\n');
    return 0;
}
