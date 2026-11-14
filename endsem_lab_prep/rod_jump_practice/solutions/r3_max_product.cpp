// R3: cut a rod of length n into at least two pieces, maximising the product of the lengths.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<ll> d(n + 1, 0);                             // d[j] = best product, at least 2 pieces
    for (int j = 2; j <= n; j++)
        for (int i = 1; i < j; i++)                     // first piece i; the rest kept whole or cut further
            d[j] = max(d[j], (ll)i * max((ll)(j - i), d[j - i]));
    cout << d[n] << '\n';
    return 0;
}
