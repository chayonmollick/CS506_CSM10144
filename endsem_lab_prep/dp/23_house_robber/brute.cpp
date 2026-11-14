// Brute force for 23: try every subset of houses, keep those with no two neighbours
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long bestLine = 0, bestCircle = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        long long sum = 0;
        for (int i = 0; i < n; i++)
            if (mask >> i & 1) {
                sum += a[i];
                if (i + 1 < n && (mask >> (i + 1) & 1)) ok = false;
            }
        if (!ok) continue;
        if (sum > bestLine) bestLine = sum;
        bool wrap = n >= 2 && (mask & 1) && (mask >> (n - 1) & 1);
        if (!wrap && sum > bestCircle) bestCircle = sum;
    }
    cout << bestLine << "\n" << bestCircle << "\n";
    return 0;
}
