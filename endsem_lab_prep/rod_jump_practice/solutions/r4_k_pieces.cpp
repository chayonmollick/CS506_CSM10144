// R4: rod cutting into at most k pieces. f[t][j] = best revenue for length j in exactly t pieces.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    int n, k;
    cin >> n >> k;
    vector<ll> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];
    const ll NEG = -(1LL << 60);
    vector<vector<ll> > f(k + 1, vector<ll>(n + 1, NEG));
    f[0][0] = 0;
    ll best = NEG;
    for (int t = 1; t <= k; t++) {
        for (int j = 1; j <= n; j++)
            for (int i = 1; i <= j; i++)                 // last piece has length i
                if (f[t - 1][j - i] != NEG) f[t][j] = max(f[t][j], f[t - 1][j - i] + p[i]);
        best = max(best, f[t][n]);
    }
    cout << best << '\n';
    return 0;
}
