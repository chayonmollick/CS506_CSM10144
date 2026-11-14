// J5: start on stone 1, jump 1..k stones forward, pay c[j] for every stone you stand on (stone 1 too).
// Least cost to reach n, and the path: best[i] filled from the end; walk forward taking the
// smallest next stone that keeps the optimum.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    int n, k;
    cin >> n >> k;
    vector<ll> c(n + 1);
    for (int i = 1; i <= n; i++) cin >> c[i];
    const ll INF = (ll)4e18;
    vector<ll> best(n + 1, INF);                         // best[i] = least cost from stone i to n, c[i] included
    vector<int> nxt(n + 1, 0);
    best[n] = c[n];
    for (int i = n - 1; i >= 1; i--)
        for (int j = i + 1; j <= min(n, i + k); j++)
            if (best[j] < INF && c[i] + best[j] < best[i]) { best[i] = c[i] + best[j]; nxt[i] = j; }   // strict <: smallest j
    cout << best[1] << '\n';
    for (int i = 1; i != 0; i = nxt[i]) cout << i << (i != n ? ' ' : '\n');
    return 0;
}
