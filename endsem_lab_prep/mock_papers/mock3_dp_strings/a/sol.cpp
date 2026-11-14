// Mock 3 (a): LCS length and one LCS (PRINT-LCS traceback, ties go UP).
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ---- Common setup: LCS-LENGTH, c[i][j] = LCS length of X[1..i] and Y[1..j] ----
vector<vector<int> > lcsLength(const string &X, const string &Y) {
    int m = X.size(), n = Y.size();
    vector<vector<int> > c(m + 1, vector<int>(n + 1, 0));     // row 0 / column 0 = 0
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (X[i - 1] == Y[j - 1]) c[i][j] = c[i - 1][j - 1] + 1;
            else c[i][j] = max(c[i - 1][j], c[i][j - 1]);
    return c;
}
// ---- end of common setup ----

int main() {
    string X, Y;
    cin >> X >> Y;
    vector<vector<int> > c = lcsLength(X, Y);
    int i = X.size(), j = Y.size();
    string lcs;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) { lcs += X[i - 1]; i--; j--; }   // diagonal: in the LCS
        else if (c[i - 1][j] >= c[i][j - 1]) i--;                    // up (ties go up)
        else j--;                                                    // left
    }
    reverse(lcs.begin(), lcs.end());
    cout << c[X.size()][Y.size()] << '\n' << (lcs.empty() ? "-" : lcs) << '\n';
    return 0;
}
