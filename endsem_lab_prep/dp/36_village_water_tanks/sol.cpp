// 36. Village Water Tanks: k tanks on a line, each house uses the nearest tank, minimise total distance
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = (long long)4e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<long long> x(n + 1), S(n + 1, 0);           // houses 1..n, S[i] = x[1] + ... + x[i]
    for (int i = 1; i <= n; i++) { cin >> x[i]; S[i] = S[i - 1] + x[i]; }

    // cost[i][j] = total distance when one tank at the median x[mid] serves houses i..j
    vector<vector<long long> > cost(n + 1, vector<long long>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) {
            int mid = (i + j) / 2;
            long long left  = x[mid] * (mid - i + 1) - (S[mid] - S[i - 1]);   // houses i..mid
            long long right = (S[j] - S[mid]) - x[mid] * (j - mid);           // houses mid+1..j
            cost[i][j] = left + right;
        }

    // f[t][j] = min total distance for houses 1..j using at most t tanks
    // base: f[t][0] = 0, f[0][j] = INF for j >= 1
    vector<vector<long long> > f(k + 1, vector<long long>(n + 1, INF));
    for (int t = 0; t <= k; t++) f[t][0] = 0;
    for (int t = 1; t <= k; t++)
        for (int j = 1; j <= n; j++)
            for (int i = 1; i <= j; i++)                    // last tank serves houses i..j
                if (f[t - 1][i - 1] < INF)
                    f[t][j] = min(f[t][j], f[t - 1][i - 1] + cost[i][j]);
    cout << f[k][n] << "\n";
    return 0;
}
