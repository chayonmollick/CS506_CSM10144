// Brute force for 11 (n <= 16): try every subset of indices, keep the strictly increasing ones.
// Tie-break from the statement: compare index sequences from the back, larger index wins.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> best;  // stored reversed (last index first)
    for (int mask = 1; mask < (1 << n); mask++) {
        vector<int> idx;
        for (int i = 0; i < n; i++) if ((mask >> i) & 1) idx.push_back(i);
        bool inc = true;
        for (size_t k = 1; k < idx.size(); k++) if (a[idx[k - 1]] >= a[idx[k]]) inc = false;
        if (!inc) continue;
        reverse(idx.begin(), idx.end());
        if (idx.size() > best.size() || (idx.size() == best.size() && idx > best)) best = idx;
    }
    reverse(best.begin(), best.end());
    cout << best.size() << "\n";
    for (size_t k = 0; k < best.size(); k++) cout << (k ? " " : "") << a[best[k]];
    cout << "\n";
    return 0;
}
