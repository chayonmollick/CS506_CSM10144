// 15 Longest common substring (contiguous) via common-suffix DP
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string X, Y;
    cin >> X >> Y;
    int m = X.size(), n = Y.size();

    // dp[i][j] = length of the longest common SUFFIX of X[1..i] and Y[1..j]; row/column 0 = 0
    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
    int best = 0, endX = 0;              // best length and where it ends in X (1-based)
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;  // extend the diagonal run
            else dp[i][j] = 0;                                         // mismatch breaks contiguity
            if (dp[i][j] > best) { best = dp[i][j]; endX = i; }        // strict: first occurrence in X
        }
    }

    cout << best << "\n";
    cout << X.substr(endX - best, best) << "\n";
    return 0;
}
