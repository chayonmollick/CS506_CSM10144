// P2: one LCS with ties going LEFT, plus its 1-indexed positions in X and in Y.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string X, Y;
    cin >> X >> Y;
    int m = X.size(), n = Y.size();
    vector<vector<int> > c(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (X[i - 1] == Y[j - 1]) c[i][j] = c[i - 1][j - 1] + 1;
            else c[i][j] = max(c[i - 1][j], c[i][j - 1]);

    string lcs;
    vector<int> px, py;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) { lcs += X[i - 1]; px.push_back(i); py.push_back(j); i--; j--; }
        else if (c[i][j - 1] >= c[i - 1][j]) j--;      // ties go LEFT
        else i--;
    }
    reverse(lcs.begin(), lcs.end());
    reverse(px.begin(), px.end());
    reverse(py.begin(), py.end());

    cout << c[m][n] << '\n';
    if (lcs.empty()) { cout << "-\n"; return 0; }
    cout << lcs << '\n';
    for (size_t k = 0; k < px.size(); k++) cout << px[k] << (k + 1 < px.size() ? ' ' : '\n');
    for (size_t k = 0; k < py.size(); k++) cout << py[k] << (k + 1 < py.size() ? ' ' : '\n');
    return 0;
}
