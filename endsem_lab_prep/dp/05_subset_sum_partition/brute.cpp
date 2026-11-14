// Brute force for 05: try all 2^n subsets (n <= 20); the first subset (smallest bitmask,
// bit i-1 = item i) with sum S/2 is the one the 1-D table reconstructs.
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    long long S = 0;
    for (int i = 0; i < n; i++) { cin >> a[i]; S += a[i]; }
    for (int mask = 0; mask < (1 << n) && S % 2 == 0; mask++) {
        long long t = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) t += a[i];
        if (2 * t == S) {
            cout << "YES\n";
            bool first = true;
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) { cout << (first ? "" : " ") << i + 1; first = false; }
            cout << "\n";
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}
