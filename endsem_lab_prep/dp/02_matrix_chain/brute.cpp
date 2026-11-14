// Brute force for 02: RECURSIVE-MATRIX-CHAIN without any table (exponential, n <= 10).
// Tries every split, keeps the first (smallest k) minimum, returns cost and parenthesization.
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<long long> p;

long long solve(int i, int j, string &out) {
    if (i == j) { out = "A" + to_string(i); return 0; }
    long long best = -1;
    for (int k = i; k < j; k++) {
        string a, b;
        long long q = solve(i, k, a) + solve(k + 1, j, b) + p[i - 1] * p[k] * p[j];
        if (best == -1 || q < best) { best = q; out = "(" + a + b + ")"; }
    }
    return best;
}

int main() {
    int n;
    cin >> n;
    p.resize(n + 1);
    for (int i = 0; i <= n; i++) cin >> p[i];
    string out;
    long long c = solve(1, n, out);
    cout << c << "\n" << out << "\n";
    return 0;
}
