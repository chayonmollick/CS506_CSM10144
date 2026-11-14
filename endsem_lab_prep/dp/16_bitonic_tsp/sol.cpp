// 16 Bitonic Euclidean TSP (CLRS 15-3): b[i][j] table, O(n^2)
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int n;
vector<pair<long long, long long> > p;  // points sorted by x, 1-based

double d(int i, int j) {
    double dx = p[i].first - p[j].first, dy = p[i].second - p[j].second;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    p.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i].first >> p[i].second;
    sort(p.begin() + 1, p.end());                           // left to right by x

    // b[i][j] (i < j) = shortest pair of disjoint paths from p1 to pi and from p1 to pj
    // that together visit p1..pj exactly once
    vector<vector<double> > b(n + 1, vector<double>(n + 1, 0.0));
    b[1][2] = d(1, 2);                                      // base case
    for (int j = 3; j <= n; j++) {
        for (int i = 1; i <= j - 2; i++)
            b[i][j] = b[i][j - 1] + d(j - 1, j);            // p(j-1) must sit on the path ending at pj
        b[j - 1][j] = 1e18;
        for (int k = 1; k <= j - 2; k++)                    // pj's predecessor is some pk, k < j-1
            b[j - 1][j] = min(b[j - 1][j], b[k][j - 1] + d(k, j));
    }
    double ans = b[n - 1][n] + d(n - 1, n);                 // close the tour

    cout << fixed << setprecision(2) << ans << "\n";
    return 0;
}
