// Brute force for 01: walks each probe sequence by repeated stepping (not the closed formula).
#include <iostream>
#include <string>
#include <vector>
using namespace std;

long long pmod(long long a, long long b) { long long r = a % b; return r < 0 ? r + b : r; }

int main() {
    int m, n;
    string w;
    long long c1 = 0, c2 = 0;
    cin >> m >> w;
    if (w == "QUADRATIC") cin >> c1 >> c2;
    cin >> n;
    vector<string> slot(m, "-");
    vector<int> pr;
    long long total = 0;
    for (int t = 0; t < n; t++) {
        long long k;
        cin >> k;
        long long pos = pmod(k, m), step = (m > 1) ? 1 + pmod(k, m - 1) : 1;
        int got = -1;
        for (long long i = 0; i < m; i++) {
            if (slot[pos] == "-") { slot[pos] = to_string(k); got = (int)i + 1; break; }
            if (w == "LINEAR") pos = pmod(pos + 1, m);
            else if (w == "DOUBLE") pos = pmod(pos + step, m);
            else pos = pmod(pos + c1 + c2 * (2 * i + 1), m);  // (i+1)-th minus i-th quadratic probe
        }
        pr.push_back(got);
        total += got == -1 ? m : got;
    }
    cout << "Table:";
    for (int j = 0; j < m; j++) cout << " " << slot[j];
    cout << "\nProbes:";
    for (int t = 0; t < n; t++) cout << " " << pr[t];
    cout << "\nTotal: " << total << "\n";
    return 0;
}
