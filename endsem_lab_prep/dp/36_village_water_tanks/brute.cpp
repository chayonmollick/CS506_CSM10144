// Brute force for 36: try every set of at most k house positions as tank locations (n <= 12);
// each house walks to its nearest tank. No contiguity or median argument is used.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    long long best = -1;
    for (int mask = 1; mask < (1 << n); mask++) {
        int used = 0;
        for (int t = 0; t < n; t++) used += mask >> t & 1;
        if (used > k) continue;
        long long total = 0;
        for (int h = 0; h < n; h++) {
            long long d = -1;
            for (int t = 0; t < n; t++)
                if (mask >> t & 1) {
                    long long dist = x[h] > x[t] ? x[h] - x[t] : x[t] - x[h];
                    if (d < 0 || dist < d) d = dist;
                }
            total += d;
        }
        if (best < 0 || total < best) best = total;
    }
    cout << best << "\n";
    return 0;
}
