// 26. Stock trading with at most k buy-sell transactions (no cooldown), O(nk)
#include <iostream>
#include <vector>
using namespace std;

const long long NEG = -(1LL << 60);

long long maxProfitK(const vector<long long>& p, int k) {
    // buy[j]  = best profit so far while holding a unit bought in transaction j
    // sell[j] = best profit so far after completing j transactions (holding nothing)
    vector<long long> buy(k + 1, NEG), sell(k + 1, 0);   // base case: before day 1, profit 0, nothing held
    for (size_t i = 0; i < p.size(); i++)
        for (int j = 1; j <= k; j++) {
            buy[j] = max(buy[j], sell[j - 1] - p[i]);   // keep holding, or start transaction j today
            sell[j] = max(sell[j], buy[j] + p[i]);      // keep, or finish transaction j today
        }
    return sell[k];                                     // sell[] is non-decreasing in j
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<long long> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    cout << maxProfitK(p, k) << "\n";
    return 0;
}
