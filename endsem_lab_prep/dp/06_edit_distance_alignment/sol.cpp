// 06 Sequence alignment / edit distance: ALIGNMENT(X, Y) + FIND-ALIGNMENT (iterative)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string X, Y;
    int delta, alpha;  // gap cost, mismatch cost
    cin >> X >> Y >> delta >> alpha;
    int m = (int)X.size(), n = (int)Y.size();

    // A[i][j] = min cost to align X[1..i] with Y[1..j]
    vector<vector<int> > A(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= m; i++) A[i][0] = i * delta;  // base: X[1..i] against gaps
    for (int j = 0; j <= n; j++) A[0][j] = j * delta;  // base: Y[1..j] against gaps
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            int a = (X[i - 1] == Y[j - 1] ? 0 : alpha);
            A[i][j] = min(a + A[i - 1][j - 1],                       // pair x_i with y_j
                          min(delta + A[i - 1][j], delta + A[i][j - 1]));  // x_i or y_j vs gap
        }

    // FIND-ALIGNMENT: walk back from (m, n); priority diag, then (x_i, -), then (-, y_j)
    string top, bot;
    int i = m, j = n;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[i][j] == (X[i - 1] == Y[j - 1] ? 0 : alpha) + A[i - 1][j - 1]) {
            top += X[i - 1]; bot += Y[j - 1]; i--; j--;
        } else if (i > 0 && A[i][j] == delta + A[i - 1][j]) {
            top += X[i - 1]; bot += '-'; i--;
        } else {
            top += '-'; bot += Y[j - 1]; j--;
        }
    }
    reverse(top.begin(), top.end());
    reverse(bot.begin(), bot.end());
    cout << A[m][n] << "\n" << top << "\n" << bot << "\n";
    return 0;
}
