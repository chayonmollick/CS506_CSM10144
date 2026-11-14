// 01. Open addressing: build the table (linear / quadratic / double hashing)
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int m;
string method;
long long c1 = 0, c2 = 0;

long long md(long long a, long long b) { return ((a % b) + b) % b; }  // mod that is >= 0

// h(k, i): slot examined by the i-th probe (i = 0, 1, ...)
int probe(long long k, long long i) {
    long long h1 = md(k, m);
    if (method == "LINEAR") return (int)md(h1 + i, m);
    if (method == "QUADRATIC") return (int)md(h1 + c1 * i + c2 * i * i, m);
    long long h2 = (m > 1) ? 1 + md(k, m - 1) : 1;   // DOUBLE: h2(k) = 1 + (k mod (m-1))
    return (int)md(h1 + i * h2, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> m >> method;
    if (method == "QUADRATIC") cin >> c1 >> c2;
    int n;
    cin >> n;
    vector<long long> T(m);
    vector<bool> used(m, false);
    vector<int> probes(n);
    long long total = 0;
    for (int t = 0; t < n; t++) {
        long long k;
        cin >> k;
        probes[t] = -1;                      // stays -1 if all m probes hit used slots
        for (int i = 0; i < m; i++) {
            int j = probe(k, i);
            if (!used[j]) { used[j] = true; T[j] = k; probes[t] = i + 1; break; }
        }
        total += (probes[t] == -1) ? m : probes[t];
    }
    cout << "Table:";
    for (int j = 0; j < m; j++) {
        if (used[j]) cout << " " << T[j];
        else cout << " -";
    }
    cout << "\nProbes:";
    for (int t = 0; t < n; t++) cout << " " << probes[t];
    cout << "\nTotal: " << total << "\n";
    return 0;
}
