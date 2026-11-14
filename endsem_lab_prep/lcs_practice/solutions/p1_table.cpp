// P1: print the whole LCS table c[0..m][0..n], then the length.
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
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            cout << c[i][j] << (j < n ? ' ' : '\n');
    cout << c[m][n] << '\n';
    return 0;
}
