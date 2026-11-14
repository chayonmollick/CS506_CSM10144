// Brute force for 07: try all 2^n subsets (n <= 16), keep the most valuable one in which no two
// requests overlap ([s, f) half-open: touching is allowed). Prints value and one optimal set.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> s(n), f(n), v(n);
    for (int i = 0; i < n; i++) cin >> s[i] >> f[i] >> v[i];
    long long best = -1;
    int bestMask = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        long long tot = 0;
        for (int i = 0; i < n && ok; i++) {
            if (!(mask >> i & 1)) continue;
            tot += v[i];
            for (int j = i + 1; j < n; j++)
                if ((mask >> j & 1) && s[i] < f[j] && s[j] < f[i]) { ok = false; break; }
        }
        if (ok && tot > best) { best = tot; bestMask = mask; }
    }
    cout << best << "\n";
    bool first = true;
    for (int i = 0; i < n; i++)
        if (bestMask >> i & 1) { cout << (first ? "" : " ") << i + 1; first = false; }
    cout << "\n";
    return 0;
}
