// P5: longest repeating subsequence = LCS(s, s) where a match needs i != j. Ties go UP.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int> > c(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (s[i - 1] == s[j - 1] && i != j) c[i][j] = c[i - 1][j - 1] + 1;
            else c[i][j] = max(c[i - 1][j], c[i][j - 1]);

    string t;
    int i = n, j = n;
    while (i > 0 && j > 0) {
        if (s[i - 1] == s[j - 1] && i != j) { t += s[i - 1]; i--; j--; }
        else if (c[i - 1][j] >= c[i][j - 1]) i--;
        else j--;
    }
    reverse(t.begin(), t.end());
    cout << c[n][n] << '\n' << (t.empty() ? "-" : t) << '\n';
    return 0;
}
