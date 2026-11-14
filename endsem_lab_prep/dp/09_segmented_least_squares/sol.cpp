// 09 Segmented least squares: SEGMENTED-LEAST-SQUARES + FIND-SEGMENTS
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    double C;
    cin >> n >> C;
    vector<double> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];

    // stage 1: e[j][i] = squared error of the best single line through points j..i
    vector<vector<double> > e(n + 1, vector<double>(n + 1, 0.0));
    for (int j = 1; j <= n; j++) {
        double sx = 0, sy = 0, sxx = 0, sxy = 0;
        for (int i = j; i <= n; i++) {
            sx += x[i]; sy += y[i]; sxx += x[i] * x[i]; sxy += x[i] * y[i];
            double N = i - j + 1;
            double a = 0;                                    // one point: any line, error 0
            if (i > j) a = (N * sxy - sx * sy) / (N * sxx - sx * sx);
            double b = (sy - a * sx) / N;
            double err = 0;
            for (int k = j; k <= i; k++) {
                double d = y[k] - a * x[k] - b;
                err += d * d;
            }
            e[j][i] = err;
        }
    }

    // stage 2: M[i] = min cost for points 1..i, first[i] = start of the last segment
    vector<double> M(n + 1, 0.0);
    vector<int> first(n + 1, 0);
    M[0] = 0;                                                // base case: no points, no cost
    for (int i = 1; i <= n; i++) {
        M[i] = 1e18;
        for (int j = 1; j <= i; j++) {
            double t = e[j][i] + C + M[j - 1];               // last segment is j..i
            if (t < M[i] - 1e-9) { M[i] = t; first[i] = j; }  // keep the smallest j on ties
        }
    }

    // FIND-SEGMENTS: jump from i to first[i]-1, collect segments, then reverse
    vector<pair<int, int> > seg;
    for (int i = n; i > 0; i = first[i] - 1) seg.push_back(make_pair(first[i], i));
    reverse(seg.begin(), seg.end());

    cout << fixed << setprecision(2) << M[n] << "\n";
    cout << seg.size() << "\n";
    for (int k = 0; k < (int)seg.size(); k++) cout << seg[k].first << " " << seg[k].second << "\n";
    return 0;
}
