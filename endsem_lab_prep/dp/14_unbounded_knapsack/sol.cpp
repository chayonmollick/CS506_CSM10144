// 14 Unbounded knapsack (each item any number of times), with the copies of each item
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, W;
    cin >> n >> W;
    vector<int> w(n + 1);
    vector<long long> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];

    vector<long long> best(W + 1, 0);  // best[c] = max value with total weight <= c (best[0] = 0)
    vector<int> choice(W + 1, 0);      // choice[c] = item taken first for capacity c (0 = none fits)
    for (int c = 1; c <= W; c++) {     // capacity outer, like BOTTOM-UP-CUT-ROD
        for (int i = 1; i <= n; i++) {
            // best[c] = max(0, max over i of v[i] + best[c - w[i]]); strict '>' keeps the smallest i
            if (w[i] <= c && v[i] + best[c - w[i]] > best[c]) {
                best[c] = v[i] + best[c - w[i]];
                choice[c] = i;
            }
        }
    }

    // traceback: take choice[c], continue with capacity c - w[choice[c]]
    vector<int> cnt(n + 1, 0);
    for (int c = W; choice[c] != 0; c -= w[choice[c]]) cnt[choice[c]]++;

    cout << best[W] << "\n";
    for (int i = 1; i <= n; i++) cout << (i > 1 ? " " : "") << cnt[i];
    cout << "\n";
    return 0;
}
