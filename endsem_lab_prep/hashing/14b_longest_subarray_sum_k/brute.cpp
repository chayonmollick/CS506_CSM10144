// Brute force for 14b: every subarray, O(n^2).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long K;
    cin >> n >> K;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int best = 0;
    for (int l = 0; l < n; l++) {
        long long s = 0;
        for (int r = l; r < n; r++) {
            s += a[r];
            if (s == K && r - l + 1 > best) best = r - l + 1;
        }
    }
    cout << best << "\n";
    return 0;
}
