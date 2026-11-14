// P10: number of ways X occurs as a subsequence of Y, mod 1e9+7.
// W[i][j] = ways X[1..i] occurs in Y[1..j] = W[i][j-1] (skip Y[j]) + W[i-1][j-1] if X[i] = Y[j].
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;

int main() {
    string X, Y;
    cin >> X >> Y;
    const ll MOD = 1000000007LL;
    int m = X.size(), n = Y.size();
    vector<vector<ll> > W(m + 1, vector<ll>(n + 1, 0));
    for (int j = 0; j <= n; j++) W[0][j] = 1;            // the empty X occurs once
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            W[i][j] = W[i][j - 1];
            if (X[i - 1] == Y[j - 1]) W[i][j] = (W[i][j] + W[i - 1][j - 1]) % MOD;
        }
    cout << W[m][n] << '\n';
    return 0;
}
