// 40. Budget Allocation: split at most B crores among k districts, benefit g_i(x), maximise the total
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int k, B;
    cin >> k >> B;
    // f[b] = best total benefit of districts 1..i-1 using at most b crores; base f[b] = 0 (no districts)
    vector<long long> f(B + 1, 0), nf(B + 1);
    vector<long long> g(B + 1);
    for (int i = 1; i <= k; i++) {
        for (int x = 0; x <= B; x++) cin >> g[x];
        for (int b = 0; b <= B; b++) {
            nf[b] = 0;
            for (int x = 0; x <= b; x++)                   // give x crores to district i
                nf[b] = max(nf[b], f[b - x] + g[x]);
        }
        f.swap(nf);
    }
    cout << f[B] << "\n";
    return 0;
}
