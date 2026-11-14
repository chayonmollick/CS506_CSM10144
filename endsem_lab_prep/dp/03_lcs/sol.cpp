// 03 Longest common subsequence: LCS-LENGTH + PRINT-LCS (iterative traceback)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string X, Y;
    cin >> X >> Y;
    int m = (int)X.size(), n = (int)Y.size();

    // c[i][j] = LCS length of X[1..i] and Y[1..j]; row 0 and column 0 stay 0 (base case)
    vector<vector<int> > c(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) c[i][j] = c[i - 1][j - 1] + 1;        // "diag"
            else c[i][j] = max(c[i - 1][j], c[i][j - 1]);                  // "up" / "left"
        }

    // PRINT-LCS: walk back from (m, n); ties between up and left go UP (c[i-1][j] >= c[i][j-1])
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) { lcs += X[i - 1]; i--; j--; }
        else if (c[i - 1][j] >= c[i][j - 1]) i--;
        else j--;
    }
    reverse(lcs.begin(), lcs.end());
    cout << c[m][n] << "\n" << lcs << "\n";
    return 0;
}
