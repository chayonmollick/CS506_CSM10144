// 25. Best Time to Buy and Sell Stock with Cooldown: 3-state machine (hold, sold, rest)
#include <iostream>
#include <vector>
using namespace std;

const long long NEG = -(1LL << 60);

long long maxProfitCooldown(const vector<long long>& p) {
    int n = p.size();
    // state after day i:
    //   hold = I own one unit;  sold = I sold today;  rest = I own nothing and did not sell today
    long long hold = -p[0], sold = NEG, rest = 0;   // base case: day 0 (buy, impossible, do nothing)
    for (int i = 1; i < n; i++) {
        long long h = max(hold, rest - p[i]);       // keep holding, or buy today (only from rest: cooldown)
        long long s = hold + p[i];                  // sell today what I was holding
        long long r = max(rest, sold);              // stay idle, or yesterday's sale finishes its cooldown
        hold = h; sold = s; rest = r;
    }
    return max(sold, rest);                         // never end while still holding
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    cout << maxProfitCooldown(p) << "\n";
    return 0;
}
