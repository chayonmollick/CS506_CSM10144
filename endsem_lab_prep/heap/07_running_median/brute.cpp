// Brute: sort each prefix and take the middle (or the average of the two middles).
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n; cin >> n; vector<long long> a;
    cout << fixed << setprecision(1);
    for (int i = 0; i < n; i++) {
        long long x; cin >> x; a.push_back(x);
        vector<long long> b = a; sort(b.begin(), b.end());
        int m = b.size();
        double med = (m % 2) ? (double)b[m / 2] : (b[m / 2 - 1] + b[m / 2]) / 2.0;
        cout << med << (i + 1 < n ? " " : "\n");
    }
    return 0;
}
