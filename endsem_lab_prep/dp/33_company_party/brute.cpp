// Brute force for 33: try every guest subset (n <= 16)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> c(n);
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < n; i++) { cin >> p[i]; p[i]--; }   // -1 for the president
    long long best = 0, bestPres = -1000000000000LL;
    int root = 0;
    for (int i = 0; i < n; i++) if (p[i] < 0) root = i;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (!(mask >> i & 1)) continue;
            sum += c[i];
            if (p[i] >= 0 && (mask >> p[i] & 1)) ok = false;
        }
        if (!ok) continue;
        if (sum > best) best = sum;
        if ((mask >> root & 1) && sum > bestPres) bestPres = sum;
    }
    cout << best << "\n" << bestPres << "\n";
    return 0;
}
