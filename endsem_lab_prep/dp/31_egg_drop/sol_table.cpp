// 31(a). Egg Drop, O(k N^2) table: T[e][n] = min worst-case drops with e eggs and n floors
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int k, N;
    cin >> k >> N;
    vector<vector<int> > T(k + 1, vector<int>(N + 1, 0));   // base: T[e][0] = 0
    for (int n = 1; n <= N; n++) T[1][n] = n;                 // base: one egg -> try floors 1, 2, ..., n
    for (int e = 2; e <= k; e++) {
        for (int n = 1; n <= N; n++) {
            int best = n;
            for (int x = 1; x <= n; x++) {   // first drop from floor x
                // breaks: x-1 floors below with e-1 eggs; survives: n-x floors above with e eggs
                int worst = 1 + max(T[e - 1][x - 1], T[e][n - x]);
                best = min(best, worst);
            }
            T[e][n] = best;
        }
    }
    cout << T[k][N] << "\n";
    return 0;
}
