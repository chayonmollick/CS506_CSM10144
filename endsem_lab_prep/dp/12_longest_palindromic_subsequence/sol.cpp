// 12 Longest palindromic subsequence: interval DP dp[i][j] + traceback
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size();

    // dp[i][j] = length of the longest palindromic subsequence of s[i..j]; 0 when i > j
    vector<vector<int> > dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = 1;            // base case: one character
    for (int len = 2; len <= n; len++) {                 // fill by interval length
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1] + 2;  // both ends used (len 2 reads a 0 cell)
            else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);    // drop one end
        }
    }

    // traceback: collect the left half, the middle character, then mirror
    string left, mid;
    int i = 0, j = n - 1;
    while (i <= j) {
        if (i == j) { mid = s[i]; break; }
        if (s[i] == s[j]) { left += s[i]; i++; j--; }
        else if (dp[i + 1][j] >= dp[i][j - 1]) i++;      // tie: drop the left end
        else j--;
    }
    string right = left;
    reverse(right.begin(), right.end());

    cout << dp[0][n - 1] << "\n";
    cout << left + mid + right << "\n";
    return 0;
}
