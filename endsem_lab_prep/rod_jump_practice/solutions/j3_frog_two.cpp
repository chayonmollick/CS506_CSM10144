// J3: frog on stones 1..n jumps to i+1 or i+2, paying |h[i] - h[j]|. Least total cost to reach n.
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<ll> h(n + 1);
    for (int i = 1; i <= n; i++) cin >> h[i];
    vector<ll> d(n + 1, 0);                              // d[i] = least cost to reach stone i
    for (int i = 2; i <= n; i++) {
        d[i] = d[i - 1] + llabs(h[i] - h[i - 1]);
        if (i >= 3) d[i] = min(d[i], d[i - 2] + llabs(h[i] - h[i - 2]));
    }
    cout << d[n] << '\n';
    return 0;
}
