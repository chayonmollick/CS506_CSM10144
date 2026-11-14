// 27. Boredom (CF 455A): pick value x -> gain x, all copies of x-1 and x+1 are deleted. Maximise points.
#include <iostream>
#include <vector>
using namespace std;

const int MAXV = 100000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> cnt(MAXV + 1, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    // f[x] = best points using only values 1..x
    vector<long long> f(MAXV + 1, 0);              // base case: f[0] = 0
    f[1] = cnt[1];
    for (int x = 2; x <= MAXV; x++)
        f[x] = max(f[x - 1],                       // skip value x
                   f[x - 2] + x * cnt[x]);         // take every copy of x, so x-1 is lost
    cout << f[MAXV] << "\n";
    return 0;
}
