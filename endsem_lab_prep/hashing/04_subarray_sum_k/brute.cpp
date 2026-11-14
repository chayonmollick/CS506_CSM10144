// Brute force for 04: sum of every subarray a[l..r], O(n^2).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long K;
    cin >> n >> K;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long ans = 0;
    for (int l = 0; l < n; l++) {
        long long s = 0;
        for (int r = l; r < n; r++) {
            s += a[r];
            if (s == K) ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
