// J2: fewest jumps from index 1 to index n (jump from i to any of i+1 .. i+a[i]), -1 if impossible.
// DP: J[i] = 1 + min J[j] over j in (i, i+a[i]], filled from the end. O(n * max a).
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    const int INF = 1 << 29;
    vector<int> J(n + 1, INF);
    J[n] = 0;
    for (int i = n - 1; i >= 1; i--)
        for (int j = i + 1; j <= min(n, i + a[i]); j++)
            J[i] = min(J[i], J[j] + 1);
    cout << (J[1] >= INF ? -1 : J[1]) << '\n';
    return 0;
}
