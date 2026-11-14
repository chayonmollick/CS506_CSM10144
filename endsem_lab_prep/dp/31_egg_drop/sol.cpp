// 31(b). Egg Drop, moves method: smallest m with g(k, m) >= N
// g(e, m) = max floors that can be resolved with e eggs and m drops
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int k;
    long long N;
    cin >> k >> N;
    vector<long long> g(k + 1, 0);           // g[e] for the current m; base: g(e, 0) = 0
    int m = 0;
    while (g[k] < N) {
        m++;
        for (int e = k; e >= 1; e--)          // downward, so g[e-1] is still the value for m-1
            g[e] = g[e - 1] + g[e] + 1;       // egg breaks: g(e-1, m-1) below; survives: g(e, m-1) above
    }
    cout << m << "\n";
    return 0;
}
