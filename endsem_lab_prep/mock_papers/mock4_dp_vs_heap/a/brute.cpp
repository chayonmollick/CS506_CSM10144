// Brute force for Mock 4 (a): enumerate every Right/Down path in lexicographic order (D before R),
// keep the first one with the minimum cost.
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int R, C; vector<vector<long long> > g; long long best = -1; string bestPath;
void go(int i, int j, long long cost, string p) {
    cost += g[i][j];
    if (i == R - 1 && j == C - 1) { if (best < 0 || cost < best) { best = cost; bestPath = p; } return; }
    if (i + 1 < R) go(i + 1, j, cost, p + 'D');
    if (j + 1 < C) go(i, j + 1, cost, p + 'R');
}
int main() {
    cin >> R >> C; g.assign(R, vector<long long>(C));
    for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) cin >> g[i][j];
    go(0, 0, 0, "");
    cout << best << '\n' << (bestPath.empty() ? "-" : bestPath) << '\n';
}
