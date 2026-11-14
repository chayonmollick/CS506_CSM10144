// P9: edit distance (insert, delete, replace, each cost 1).
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string X, Y;
    cin >> X >> Y;
    int m = X.size(), n = Y.size();
    vector<vector<int> > E(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= m; i++) E[i][0] = i;            // delete all of X[1..i]
    for (int j = 0; j <= n; j++) E[0][j] = j;            // insert all of Y[1..j]
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            E[i][j] = min(min(E[i - 1][j] + 1, E[i][j - 1] + 1),
                          E[i - 1][j - 1] + (X[i - 1] == Y[j - 1] ? 0 : 1));
    cout << E[m][n] << '\n';
    return 0;
}
