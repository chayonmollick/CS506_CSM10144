// 39. Two Carts in a Mango Orchard: two right/down paths (1,1) -> (n,n), each cell's mangoes counted once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int NEG = -1000000000;                // "this pair of positions is unreachable"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<vector<int> > g(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> g[i][j];
    if (g[0][0] == -1 || g[n - 1][n - 1] == -1) { cout << -1 << "\n"; return 0; }

    // After t moves both carts are on the anti-diagonal i + j = t (0-based).
    // dp[r1][r2] = max mangoes with cart 1 at (r1, t - r1) and cart 2 at (r2, t - r2).
    vector<vector<int> > dp(n, vector<int>(n, NEG)), nd(n, vector<int>(n, NEG));
    dp[0][0] = g[0][0];                                      // base case: t = 0, both at the start
    for (int t = 1; t <= 2 * (n - 1); t++) {
        for (int r1 = 0; r1 < n; r1++) fill(nd[r1].begin(), nd[r1].end(), NEG);
        for (int r1 = max(0, t - n + 1); r1 <= min(n - 1, t); r1++)
            for (int r2 = max(0, t - n + 1); r2 <= min(n - 1, t); r2++) {
                int c1 = t - r1, c2 = t - r2;
                if (g[r1][c1] == -1 || g[r2][c2] == -1) continue;
                // each cart came from above (row - 1) or from the left (same row): 4 combinations
                int best = dp[r1][r2];
                if (r1 > 0) best = max(best, dp[r1 - 1][r2]);
                if (r2 > 0) best = max(best, dp[r1][r2 - 1]);
                if (r1 > 0 && r2 > 0) best = max(best, dp[r1 - 1][r2 - 1]);
                if (best == NEG) continue;
                int gain = g[r1][c1] + (r1 != r2 ? g[r2][c2] : 0);   // same cell -> count once
                nd[r1][r2] = best + gain;
            }
        dp.swap(nd);
    }
    cout << (dp[n - 1][n - 1] < 0 ? -1 : dp[n - 1][n - 1]) << "\n";
    return 0;
}
