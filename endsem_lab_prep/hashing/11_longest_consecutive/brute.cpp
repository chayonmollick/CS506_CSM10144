// Brute force for 11: sort, drop duplicates, scan runs (smallest start wins ties).
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    long long bestStart = a[0], bestLen = 1, start = a[0], len = 1;
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i] == a[i - 1] + 1) len++;
        else { start = a[i]; len = 1; }
        if (len > bestLen) { bestLen = len; bestStart = start; }
    }
    cout << bestLen << "\n";
    for (long long v = bestStart; v < bestStart + bestLen; v++)
        cout << (v == bestStart ? "" : " ") << v;
    cout << "\n";
    return 0;
}
