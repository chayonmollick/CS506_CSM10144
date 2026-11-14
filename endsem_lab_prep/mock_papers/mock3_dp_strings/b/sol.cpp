// Mock 3 (b): shortest common supersequence from the LCS table.
// Length = m + n - LCS. Walk back like PRINT-LCS, but also output the characters the LCS skips.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ---- Common setup: LCS-LENGTH ----
vector<vector<int> > lcsLength(const string &X, const string &Y) {
    int m = X.size(), n = Y.size();
    vector<vector<int> > c(m + 1, vector<int>(n + 1, 0));
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
    string s;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) { s += X[i - 1]; i--; j--; }       // shared character, once
        else if (c[i - 1][j] >= c[i][j - 1]) { s += X[i - 1]; i--; }  // X[i] is not in the LCS
        else { s += Y[j - 1]; j--; }                                  // Y[j] is not in the LCS
    }
    while (i > 0) { s += X[i - 1]; i--; }                             // leftover prefix of X
    while (j > 0) { s += Y[j - 1]; j--; }                             // or of Y
    reverse(s.begin(), s.end());
    cout << s.size() << '\n' << s << '\n';
    return 0;
}
