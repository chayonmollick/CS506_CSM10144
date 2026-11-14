// P8: longest common substring (contiguous). s[i][j] = length of the common suffix of X[1..i] and Y[1..j].
// Reports the first maximum met scanning i, then j (strict >), i.e. the one ending earliest in X.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string X, Y;
    cin >> X >> Y;
    int m = X.size(), n = Y.size(), best = 0, endX = 0;
    vector<vector<int> > s(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (X[i - 1] == Y[j - 1]) {
                s[i][j] = s[i - 1][j - 1] + 1;
                if (s[i][j] > best) { best = s[i][j]; endX = i; }
            }                                            // mismatch: stays 0
    cout << best << '\n' << (best ? X.substr(endX - best, best) : "-") << '\n';
    return 0;
}
