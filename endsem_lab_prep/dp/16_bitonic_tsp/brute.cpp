// Brute force for 16 (n <= 18): every bitonic tour = each middle point goes on the upper or the
// lower left-to-right path. Try all 2^(n-2) assignments. Prints 9 decimals.
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<long long, long long> > p(n);
    for (int i = 0; i < n; i++) cin >> p[i].first >> p[i].second;
    sort(p.begin(), p.end());
    double best = 1e18;
    for (int mask = 0; mask < (1 << (n - 2)); mask++) {
        int lastUp = 0, lastDown = 0;
        double len = 0;
        for (int i = 1; i < n; i++) {
            bool up = (i == n - 1) || ((mask >> (i - 1)) & 1);   // last point ends both paths
            bool down = (i == n - 1) || !up;
            if (up) { len += hypot(double(p[i].first - p[lastUp].first), double(p[i].second - p[lastUp].second)); lastUp = i; }
            if (down) { len += hypot(double(p[i].first - p[lastDown].first), double(p[i].second - p[lastDown].second)); lastDown = i; }
        }
        best = min(best, len);
    }
    cout << fixed << setprecision(9) << best << "\n";
    return 0;
}
