// Brute force for Mock 2 (b): try every subarray, longest wins, smaller start on ties.
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n; long long K; cin >> n >> K;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    int best = 0, L = 0, R = 0;
    for (int l = 1; l <= n; l++) {
        long long s = 0;
        for (int r = l; r <= n; r++) {
            s += a[r];
            if (s == K && r - l + 1 > best) { best = r - l + 1; L = l; R = r; }
        }
    }
    if (best == 0) cout << 0 << '\n'; else cout << best << ' ' << L << ' ' << R << '\n';
}
