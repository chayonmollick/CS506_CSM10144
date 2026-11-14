// Mock 4 (a): cheapest path moving only Right/Down, plus the lexicographically smallest
// optimal path (D < R). DP from the END so the path can be read off greedily from the start.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    // ---- Common setup: read the grid ----
    int R, C;
    cin >> R >> C;
    vector<vector<long long> > g(R, vector<long long>(C));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) cin >> g[i][j];
    // ---- end of common setup ----

    // f[i][j] = cheapest cost from (i,j) to (R-1,C-1), both cells included
    vector<vector<long long> > f(R, vector<long long>(C));
    for (int i = R - 1; i >= 0; i--)
        for (int j = C - 1; j >= 0; j--) {
            if (i == R - 1 && j == C - 1) { f[i][j] = g[i][j]; continue; }
            long long best = -1;
            if (i + 1 < R) best = f[i + 1][j];
            if (j + 1 < C && (best < 0 || f[i][j + 1] < best)) best = f[i][j + 1];
            f[i][j] = g[i][j] + best;
        }

    string path;
    int i = 0, j = 0;
    while (i != R - 1 || j != C - 1) {
        // go Down whenever Down still lies on a cheapest path (D < R)
        if (i + 1 < R && f[i + 1][j] == f[i][j] - g[i][j]) { path += 'D'; i++; }
        else { path += 'R'; j++; }
    }
    cout << f[0][0] << '\n' << (path.empty() ? "-" : path) << '\n';
    return 0;
}
