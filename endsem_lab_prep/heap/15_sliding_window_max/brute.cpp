// Brute: scan every window, O(N*K).
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n, k; cin >> n >> k; vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int s = 0; s + k <= n; s++) {
        long long m = a[s];
        for (int j = s; j < s + k; j++) if (a[j] > m) m = a[j];
        cout << m << (s + k < n ? " " : "\n");
    }
    return 0;
}
