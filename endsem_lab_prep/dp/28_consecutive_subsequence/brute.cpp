// Brute force for 28: try every subset (n <= 15), apply the tie rule directly
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> best;                         // chosen indices (0-based, increasing)
    for (int mask = 1; mask < (1 << n); mask++) {
        vector<int> idx;
        for (int i = 0; i < n; i++) if (mask >> i & 1) idx.push_back(i);
        bool ok = true;
        for (size_t j = 1; j < idx.size(); j++) if (a[idx[j]] != a[idx[j - 1]] + 1) ok = false;
        if (!ok) continue;
        // better: longer; same length -> earlier last index; then lexicographically smaller indices
        bool better = false;
        if (idx.size() != best.size()) better = idx.size() > best.size();
        else if (idx.back() != best.back()) better = idx.back() < best.back();
        else better = idx < best;
        if (better) best = idx;
    }
    cout << best.size() << "\n";
    for (size_t j = 0; j < best.size(); j++) cout << (j ? " " : "") << best[j] + 1;
    cout << "\n";
    return 0;
}
