// P6: LCS of three strings, c[i][j][k], O(|A||B||C|).
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string A, B, C;
    cin >> A >> B >> C;
    int p = A.size(), q = B.size(), r = C.size();
    vector<vector<vector<int> > > c(p + 1, vector<vector<int> >(q + 1, vector<int>(r + 1, 0)));
    for (int i = 1; i <= p; i++)
        for (int j = 1; j <= q; j++)
            for (int k = 1; k <= r; k++)
                if (A[i - 1] == B[j - 1] && B[j - 1] == C[k - 1]) c[i][j][k] = c[i - 1][j - 1][k - 1] + 1;
                else c[i][j][k] = max(c[i - 1][j][k], max(c[i][j - 1][k], c[i][j][k - 1]));
    cout << c[p][q][r] << '\n';
    return 0;
}
