// 02 Matrix-chain multiplication: MATRIX-CHAIN-ORDER + PRINT-OPTIMAL-PARENS
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<int> > s;  // s[i][j] = best split k for A_i..A_j

string parens(int i, int j) {  // PRINT-OPTIMAL-PARENS
    if (i == j) return "A" + to_string(i);
    return "(" + parens(i, s[i][j]) + parens(s[i][j] + 1, j) + ")";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> p(n + 1);  // A_i is p[i-1] x p[i]
    for (int i = 0; i <= n; i++) cin >> p[i];

    vector<vector<long long> > m(n + 1, vector<long long>(n + 1, 0));  // m[i][i] = 0 (base case)
    s.assign(n + 1, vector<int>(n + 1, 0));
    for (int l = 2; l <= n; l++) {          // chain length
        for (int i = 1; i + l - 1 <= n; i++) {
            int j = i + l - 1;
            m[i][j] = -1;
            for (int k = i; k < j; k++) {   // split (A_i..A_k)(A_k+1..A_j)
                long long q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (m[i][j] == -1 || q < m[i][j]) {  // strict '<': smallest k on ties
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    cout << m[1][n] << "\n" << parens(1, n) << "\n";
    return 0;
}
