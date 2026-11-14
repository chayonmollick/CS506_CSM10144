// Brute force for 14a: check every pair, O(n^2).
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            long long d = a[i] - a[j];
            if (d == k || -d == k) ans++;
        }
    cout << ans << "\n";
    return 0;
}
