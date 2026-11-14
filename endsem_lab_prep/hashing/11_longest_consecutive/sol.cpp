// 11. Longest consecutive sequence in O(n) expected with a hash set
#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    unordered_set<long long> S;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        S.insert(x);                                   // duplicates collapse
    }
    long long bestStart = 0, bestLen = 0;
    for (unordered_set<long long>::iterator it = S.begin(); it != S.end(); ++it) {
        long long x = *it;
        if (S.count(x - 1)) continue;                  // x is not the start of a run
        long long y = x;
        while (S.count(y + 1)) y++;                    // walk the run x, x+1, ..., y
        long long len = y - x + 1;
        if (len > bestLen || (len == bestLen && x < bestStart)) { bestLen = len; bestStart = x; }
    }
    cout << bestLen << "\n";
    for (long long v = bestStart; v < bestStart + bestLen; v++)
        cout << (v == bestStart ? "" : " ") << v;
    cout << "\n";
    return 0;
}
