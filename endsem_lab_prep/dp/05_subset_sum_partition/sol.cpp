// 05 Equal-sum partition via 1-D subset-sum table (inner loop downward)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int S = 0;
    for (int i = 1; i <= n; i++) { cin >> a[i]; S += a[i]; }
    if (S % 2 != 0) { cout << "NO\n"; return 0; }  // odd total can never split evenly
    int T = S / 2;

    // can[s] = some subset of the items seen so far sums to s; from[s] = item that first reached s
    vector<bool> can(T + 1, false);
    vector<int> from(T + 1, 0);
    can[0] = true;                                 // base case: empty subset
    for (int i = 1; i <= n; i++)
        for (int s = T; s >= a[i]; s--)            // DOWNWARD: each item used at most once
            if (!can[s] && can[s - a[i]]) {
                can[s] = true;
                from[s] = i;
            }

    if (!can[T]) { cout << "NO\n"; return 0; }
    // traceback: from[] indices strictly decrease, so every item is used once
    vector<int> group;
    for (int s = T; s > 0; s -= a[from[s]]) group.push_back(from[s]);
    reverse(group.begin(), group.end());
    cout << "YES\n";
    for (int k = 0; k < (int)group.size(); k++) cout << (k ? " " : "") << group[k];
    cout << "\n";
    return 0;
}
