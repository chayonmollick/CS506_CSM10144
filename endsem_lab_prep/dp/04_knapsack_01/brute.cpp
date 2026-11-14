// Brute force for 04: try all 2^n subsets (n <= 20). Among the optimal subsets keep the one
// FIND-ITEMS prints: it skips item i whenever possible, starting from i = n, which is the
// optimal subset with the smallest bitmask (bit i-1 = item i).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, W;
    cin >> n >> W;
    vector<long long> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    long long best = -1;
    int bestMask = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long tw = 0, tv = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) { tw += w[i]; tv += v[i]; }
        if (tw <= W && tv > best) { best = tv; bestMask = mask; }  // first = smallest mask
    }
    cout << best << "\n";
    bool first = true;
    for (int i = 0; i < n; i++)
        if (bestMask >> i & 1) { cout << (first ? "" : " ") << i + 1; first = false; }
    cout << "\n";
    return 0;
}
