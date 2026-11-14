// R2: rod cutting where every cut costs c: r[j] = max(p[j], max over i<j of p[i] + r[j-i] - c).
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main() {
    int n;
    ll c;
    cin >> n >> c;
    vector<ll> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];
    vector<ll> r(n + 1, 0);
    for (int j = 1; j <= n; j++) {
        r[j] = p[j];                                    // no cut
        for (int i = 1; i < j; i++)
            r[j] = max(r[j], p[i] + r[j - i] - c);      // first piece i, then one cut
    }
    cout << r[n] << '\n';
    return 0;
}
