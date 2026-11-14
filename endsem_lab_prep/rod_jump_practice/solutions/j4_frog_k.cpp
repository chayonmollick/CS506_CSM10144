// J4: frog jumps from i to any of i+1 .. i+k, paying |h[i] - h[j]|. Least total cost to reach n. O(nk).
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    int n, k;
    cin >> n >> k;
    vector<ll> h(n + 1);
    for (int i = 1; i <= n; i++) cin >> h[i];
    const ll INF = (ll)4e18;
    vector<ll> d(n + 1, INF);
    d[1] = 0;
    for (int i = 2; i <= n; i++)
        for (int j = max(1, i - k); j < i; j++)
            d[i] = min(d[i], d[j] + llabs(h[i] - h[j]));
    cout << d[n] << '\n';
    return 0;
}
