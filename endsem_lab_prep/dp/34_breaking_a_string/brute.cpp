// Brute force for 34: try every order of the breaks (m! orders, m <= 8) and simulate the cost
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long n;
    int m;
    cin >> n >> m;
    vector<long long> L(m);
    for (int i = 0; i < m; i++) cin >> L[i];
    vector<int> perm(m);
    for (int i = 0; i < m; i++) perm[i] = i;
    long long best = -1;
    do {
        vector<long long> cuts;          // breaks done so far
        long long total = 0;
        for (int t = 0; t < m; t++) {
            long long p = L[perm[t]], lo = 0, hi = n;   // piece containing p is (lo, hi)
            for (size_t q = 0; q < cuts.size(); q++) {
                if (cuts[q] < p) lo = max(lo, cuts[q]);
                else hi = min(hi, cuts[q]);
            }
            total += hi - lo;
            cuts.push_back(p);
        }
        if (best < 0 || total < best) best = total;
    } while (next_permutation(perm.begin(), perm.end()));
    cout << best << "\n";
    return 0;
}
