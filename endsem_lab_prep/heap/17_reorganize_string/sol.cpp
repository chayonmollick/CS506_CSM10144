// 17. Reorganize string (LeetCode 767): no two equal adjacent letters.
// Greedy with a max-heap of (count, -letter): take the letter with the most copies left that
// differs from the previous one; ties -> alphabetically smaller letter.
#include <iostream>
#include <string>
#include <queue>
#include <utility>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int n = s.size(), cnt[26] = {0}, mx = 0;
    for (int i = 0; i < n; i++) cnt[s[i] - 'a']++;
    for (int c = 0; c < 26; c++) if (cnt[c] > mx) mx = cnt[c];
    if (mx > (n + 1) / 2) { cout << "IMPOSSIBLE\n"; return 0; }   // pigeonhole check
    priority_queue<pair<int, int> > pq;     // (count, -letter): more copies, then smaller letter
    for (int c = 0; c < 26; c++)
        if (cnt[c] > 0) pq.push(make_pair(cnt[c], -c));
    string res;
    while (!pq.empty()) {
        pair<int, int> a = pq.top(); pq.pop();
        if (!res.empty() && res[res.size() - 1] == 'a' - a.second) {   // same as previous letter
            pair<int, int> b = pq.top(); pq.pop();   // exists, because the check above passed
            res += (char)('a' - b.second);
            if (--b.first > 0) pq.push(b);
            pq.push(a);                              // a waits one step
        } else {
            res += (char)('a' - a.second);
            if (--a.first > 0) pq.push(a);
        }
    }
    cout << res << '\n';
    return 0;
}
