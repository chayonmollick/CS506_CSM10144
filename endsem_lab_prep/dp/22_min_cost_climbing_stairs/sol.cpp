// 22. Min Cost Climbing Stairs: pay cost[i] when you leave step i; start on step 0 or 1; reach the top (step n)
#include <iostream>
#include <vector>
using namespace std;

long long minCostClimb(const vector<long long>& cost) {
    int n = cost.size();
    vector<long long> dp(n + 1, 0);              // dp[i] = min cost to stand on step i
    // base case: dp[0] = dp[1] = 0 (we may start on step 0 or step 1 for free)
    for (int i = 2; i <= n; i++)
        dp[i] = min(dp[i - 1] + cost[i - 1],     // came from i-1 with a 1-step
                    dp[i - 2] + cost[i - 2]);    // came from i-2 with a 2-step
    return dp[n];                                // step n = the top, just beyond the last stair
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> cost(n);
    for (int i = 0; i < n; i++) cin >> cost[i];
    cout << minCostClimb(cost) << "\n";
    return 0;
}
