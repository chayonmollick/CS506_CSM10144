// 04 0/1 knapsack: KNAPSACK(n, W) table + FIND-ITEMS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, W;
    cin >> n >> W;
    vector<int> wt(n + 1);
    vector<long long> val(n + 1);
    for (int i = 1; i <= n; i++) cin >> wt[i] >> val[i];

    // M[i][w] = best value using items 1..i with capacity w; row 0 is all 0 (base case)
    vector<vector<long long> > M(n + 1, vector<long long>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int w = 0; w <= W; w++) {
            M[i][w] = M[i - 1][w];                              // leave item i
            if (wt[i] <= w)
                M[i][w] = max(M[i][w], val[i] + M[i - 1][w - wt[i]]);  // take item i
        }

    // FIND-ITEMS: if the row changed, item i was taken
    vector<int> items;
    int w = W;
    for (int i = n; i >= 1; i--)
        if (M[i][w] != M[i - 1][w]) {
            items.push_back(i);
            w -= wt[i];
        }
    reverse(items.begin(), items.end());

    cout << M[n][W] << "\n";
    for (int k = 0; k < (int)items.size(); k++) cout << (k ? " " : "") << items[k];
    cout << "\n";
    return 0;
}
