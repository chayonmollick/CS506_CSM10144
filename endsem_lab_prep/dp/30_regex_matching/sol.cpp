// 30. Regular Expression Matching ('.' and '*'): dp[i][j] = s[0..i) matches p[0..j)
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isMatch(const string& s, const string& p) {
    int n = s.size(), m = p.size();
    vector<vector<bool> > dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;                                   // empty pattern matches empty string
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') {
                // x* used zero times: drop "x*"
                bool res = (j >= 2) && dp[i][j - 2];
                // x* used once more: s[i-1] must match x, and s[0..i-1) must still match p[0..j)
                if (!res && i > 0 && j >= 2 && (p[j - 2] == '.' || p[j - 2] == s[i - 1]))
                    res = dp[i - 1][j];
                dp[i][j] = res;
            } else if (i > 0 && (p[j - 1] == '.' || p[j - 1] == s[i - 1])) {
                dp[i][j] = dp[i - 1][j - 1];           // single character matches
            }
        }
    }
    return dp[n][m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string s, p;
    cin >> s >> p;
    cout << (isMatch(s, p) ? "YES" : "NO") << "\n";
    return 0;
}
