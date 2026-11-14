// 35. Cricket Auction: at most one player per position, total cost <= X, maximise value (group knapsack)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, P, X;
    cin >> N >> P >> X;
    // prev[b] = best value using positions 1..i-1 with total cost <= b; base: 0 for every b (sign nobody)
    vector<long long> prev(X + 1, 0), cur(X + 1, 0);
    vector<int> c(P);
    vector<long long> v(P);
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < P; j++) cin >> c[j] >> v[j];
        for (int b = 0; b <= X; b++) {
            cur[b] = prev[b];                                    // leave position i empty
            for (int j = 0; j < P; j++)                          // or sign player j of position i
                if (c[j] <= b) cur[b] = max(cur[b], prev[b - c[j]] + v[j]);
        }
        prev.swap(cur);                                          // row i becomes the "previous" row
    }
    cout << prev[X] << "\n";
    return 0;
}
