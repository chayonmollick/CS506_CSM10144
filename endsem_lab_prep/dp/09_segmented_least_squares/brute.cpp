// Brute force for 09: try all 2^(n-1) ways to split points 1..n into consecutive segments.
// Prints the minimum cost (9 decimals) and one optimal split. Use only for n <= 16.
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int n;
double C;
vector<double> x, y;

// squared error of the least-squares line through points j..i (1-based, inclusive)
double lineError(int j, int i) {
    int N = i - j + 1;
    if (N == 1) return 0;
    double mx = 0, my = 0;
    for (int k = j; k <= i; k++) { mx += x[k]; my += y[k]; }
    mx /= N; my /= N;
    double num = 0, den = 0;
    for (int k = j; k <= i; k++) { num += (x[k] - mx) * (y[k] - my); den += (x[k] - mx) * (x[k] - mx); }
    double a = num / den, b = my - a * mx, err = 0;
    for (int k = j; k <= i; k++) { double d = y[k] - a * x[k] - b; err += d * d; }
    return err;
}

int main() {
    cin >> n >> C;
    x.assign(n + 1, 0); y.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    double best = 1e18;
    int bestMask = 0;
    for (int mask = 0; mask < (1 << (n - 1)); mask++) {   // bit k set: a segment ends after point k+1
        double cost = 0;
        int start = 1;
        for (int i = 1; i <= n; i++) {
            if (i == n || (mask >> (i - 1)) & 1) { cost += lineError(start, i) + C; start = i + 1; }
        }
        if (cost < best) { best = cost; bestMask = mask; }
    }
    cout << fixed << setprecision(9) << best << "\n";
    int start = 1, k = 0;
    vector<int> a, b;
    for (int i = 1; i <= n; i++)
        if (i == n || (bestMask >> (i - 1)) & 1) { a.push_back(start); b.push_back(i); start = i + 1; k++; }
    cout << k << "\n";
    for (int t = 0; t < k; t++) cout << a[t] << " " << b[t] << "\n";
    return 0;
}
