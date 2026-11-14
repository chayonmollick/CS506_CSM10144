// 08. Task scheduler (LeetCode 621): minimum intervals with cooldown n.
// Max-heap of remaining counts; fill one "cycle" of n+1 slots at a time.
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int total, n;
    cin >> total >> n;
    int cnt[26] = {0};
    for (int i = 0; i < total; i++) {
        char c;
        cin >> c;
        cnt[c - 'A']++;
    }
    priority_queue<int> pq;                      // max-heap of remaining counts
    for (int i = 0; i < 26; i++)
        if (cnt[i] > 0) pq.push(cnt[i]);
    long long time = 0;
    while (!pq.empty()) {
        vector<int> used;                        // tasks run in this cycle
        for (int slot = 0; slot <= n && !pq.empty(); slot++) {
            used.push_back(pq.top() - 1);        // run the most frequent remaining task
            pq.pop();
        }
        for (size_t i = 0; i < used.size(); i++)
            if (used[i] > 0) pq.push(used[i]);   // comes back after the cooldown
        // full cycle (with idles) unless this was the last one
        time += pq.empty() ? (long long)used.size() : (long long)(n + 1);
    }
    cout << time << '\n';
    return 0;
}
