// 38. Grid Paths: min path sum and number of paths (right/down moves, -1 = blocked cell)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long MOD = 1000000007LL;
const long long INF = (long long)4e18;     // "cell not reachable"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<vector<int> > a(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> a[i][j];

    // best[i][j] = min sum of a path (1,1) -> (i,j); ways[i][j] = number of such paths mod MOD
    vector<vector<long long> > best(n, vector<long long>(m, INF)), ways(n, vector<long long>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (a[i][j] == -1) continue;                    // blocked: INF and 0 ways
            if (i == 0 && j == 0) { best[0][0] = a[0][0]; ways[0][0] = 1; continue; }   // base case
            long long fromBest = INF, w = 0;
            if (i > 0) { fromBest = min(fromBest, best[i - 1][j]); w += ways[i - 1][j]; }   // came from above
            if (j > 0) { fromBest = min(fromBest, best[i][j - 1]); w += ways[i][j - 1]; }   // came from left
            if (fromBest < INF) best[i][j] = fromBest + a[i][j];
            ways[i][j] = w % MOD;
        }
    cout << (best[n - 1][m - 1] < INF ? best[n - 1][m - 1] : -1) << "\n";
    cout << ways[n - 1][m - 1] << "\n";
    return 0;
}
