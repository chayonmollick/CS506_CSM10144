// 29. Burst Balloons (LeetCode 312): interval DP, choose the LAST balloon burst in each open interval
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> v(n + 2, 1);                  // v[0] = v[n+1] = 1 (virtual balloons)
    for (int i = 1; i <= n; i++) cin >> v[i];

    // dp[i][j] = max coins from bursting every balloon strictly between i and j (i, j stay)
    vector<vector<long long> > dp(n + 2, vector<long long>(n + 2, 0));   // base: j = i+1 -> 0
    for (int gap = 2; gap <= n + 1; gap++) {         // gap = j - i, short intervals first
        for (int i = 0; i + gap <= n + 1; i++) {
            int j = i + gap;
            for (int k = i + 1; k < j; k++) {        // k = last balloon burst in (i, j)
                long long c = dp[i][k] + dp[k][j] + v[i] * v[k] * v[j];
                if (c > dp[i][j]) dp[i][j] = c;
            }
        }
    }
    cout << dp[0][n + 1] << "\n";
    return 0;
}
